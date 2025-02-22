#include "demo_layer.hpp"

#include "sampo/input/input.hpp"
#include "sampo/input/keyboard.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

#if SAMPO_PLATFORM_WINDOWS
	#include "platform/opengl/opengl_shader.hpp"
#endif 

DemoLayer::DemoLayer()
	: Sampo::Layer("DemoLayer")
	, m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
	, m_Keyboard(nullptr)
{
}

void DemoLayer::OnAttach()
{
	Sampo::Application& application = Sampo::Application::GetInstance();
	Sampo::Input& input = application.GetPlatform()->GetInput();
	if (const unsigned int index = input.GetFirstInputDeviceIndexByType(Sampo::InputType::kKeyboard) != -1)
		m_Keyboard = static_cast<const Sampo::Keyboard*>(input.GetInputDevice(index));

	m_VertexArray.reset(Sampo::VertexArray::Create());

	float vertices[3 * 7] = {
		-0.5f, -0.5f, 0.0f, 0.75f, 0.25f, 0.75f, 1.0f,
		 0.5f, -0.5f, 0.0f, 0.25f, 0.3f, 0.75f, 1.0f,
		 0.0f,  0.5f, 0.0f, 0.75f, 0.75f, 0.25f, 1.0f,
	};

	std::shared_ptr<Sampo::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Sampo::VertexBuffer::Create(vertices, sizeof(vertices)));

	Sampo::BufferLayout layout = {
		{ Sampo::ShaderDataType::Float3, "aPosition"},
		{ Sampo::ShaderDataType::Float4, "aColor" }
	};

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);

	uint32 indices[3] = { 0, 1, 2 };

	std::shared_ptr<Sampo::IndexBuffer> indexBuffer;
	indexBuffer.reset(Sampo::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32)));
	m_VertexArray->SetIndexBuffer(indexBuffer);

	const std::string vertexSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;
			layout(location = 1) in vec4 aColor;

			uniform mat4 uViewProjection;
			uniform mat4 uTransform;

			out vec3 vPosition;
			out vec4 vColor;

			void main()
			{
				vPosition = aPosition;
				vColor = aColor;
				gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
			}
		)";

	const std::string fragmentSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 colorOut;

			in vec3 vPosition;
			in vec4 vColor;

			void main()
			{
				colorOut = vec4((vPosition * 0.5) + 0.5, 1.0);
				colorOut = vColor;
			}
		)";

	m_Shader.reset(Sampo::Shader::Create(vertexSource, fragmentSource));

	m_SquareVA.reset(Sampo::VertexArray::Create());

	float squareVertices[3 * 4] = {
		-0.75f, -0.75f, 0.0f,
		 0.75f, -0.75f, 0.0f,
		 0.75f,  0.75f, 0.0f,
		 -0.75f,  0.75f, 0.0f
	};

	std::shared_ptr<Sampo::VertexBuffer> squareVB;
	squareVB.reset(Sampo::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({ { Sampo::ShaderDataType::Float3, "aPosition" } });
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32 squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	std::shared_ptr<Sampo::IndexBuffer> squareIB;
	squareIB.reset(Sampo::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32)));
	m_SquareVA->SetIndexBuffer(squareIB);

	const std::string vertexSquareSource = R"(
			#version 330 core
			
			layout(location = 0) in vec3 aPosition;

			uniform mat4 uViewProjection;
			uniform mat4 uTransform;

			out vec3 vPosition;

			void main()
			{
				vPosition = aPosition;
				gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
			}
		)";

	const std::string fragmentSquareSource = R"(
			#version 330 core
			
			layout(location = 0) out vec4 colorOut;

			in vec3 vPosition;

			uniform vec3 uColor;

			void main()
			{
				colorOut = vec4(uColor, 1.0);
			}
		)";

	m_SquareShader.reset(Sampo::Shader::Create(vertexSquareSource, fragmentSquareSource));
}

void DemoLayer::OnUpdate(Sampo::Timestep aDeltaTime)
{
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kLEFT))
		m_CameraPosition.x -= m_CameraMoveSpeed * aDeltaTime;
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kRIGHT))
		m_CameraPosition.x += m_CameraMoveSpeed * aDeltaTime;
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kDOWN))
		m_CameraPosition.y -= m_CameraMoveSpeed * aDeltaTime;
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kUP))
		m_CameraPosition.y += m_CameraMoveSpeed * aDeltaTime;

	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kA))
		m_CameraRotation += m_CameraRotationSpeed * aDeltaTime;
	if (m_Keyboard->GetIsButtonPressed(Sampo::KeyboardButton::kD))
		m_CameraRotation -= m_CameraRotationSpeed * aDeltaTime;

	m_Camera.SetPosition(m_CameraPosition);
	m_Camera.SetRotation(m_CameraRotation);

	Sampo::RenderCommand::Clear();

	Sampo::Renderer::BeginScene(m_Camera);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	glm::vec4 redColor(0.75f, 0.25f, 0.35f, 1.0f);
	glm::vec4 blueColor(0.25f, 0.35f, 0.75f, 1.0f);

	std::shared_ptr<Sampo::OpenGLShader> squareShader = std::dynamic_pointer_cast<Sampo::OpenGLShader>(m_SquareShader);
	squareShader->Bind();
	squareShader->UploadUniformFloat3("uColor", m_SquareColor);

	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 position(x * 0.175f, y * 0.175f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * scale;
			Sampo::Renderer::Submit(m_SquareShader, m_SquareVA, transform);
		}
	}

	Sampo::Renderer::Submit(m_Shader, m_VertexArray);

	Sampo::Renderer::EndScene();
}

void DemoLayer::OnImGuiRender()
{
	ImGui::Begin("DemoSettings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}
