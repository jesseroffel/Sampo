// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTextureCoord;
layout(location = 3) in float aTextureIndex;
layout(location = 4) in float aTilingScale;

uniform mat4 uViewProjection;

out vec4 vColor;
out vec2 vTextureCoord;
out float vTextureIndex;
out float vTilingScale;

void main()
{
	vColor = aColor;
	vTextureCoord = aTextureCoord;
	vTextureIndex = aTextureIndex;
	vTilingScale = aTilingScale;
	gl_Position = uViewProjection  * vec4(aPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec4 vColor;
in vec2 vTextureCoord;
in float vTextureIndex;
in float vTilingScale;

uniform sampler2D uTexture[32];

void main()
{
	color = texture(uTexture[int(vTextureIndex)], vTextureCoord * vTilingScale) * vColor;
}