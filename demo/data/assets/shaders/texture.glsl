// Basic Texture Shader

#type vertex
#version 330 core

layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec2 aTextureCoord;

uniform mat4 uViewProjection;
uniform mat4 uTransform;

out vec2 vTextureCoord;

void main()
{
	vTextureCoord = aTextureCoord;
	gl_Position = uViewProjection * uTransform * vec4(aPosition, 1.0);
}

#type fragment
#version 330 core

layout(location = 0) out vec4 colorOut;

in vec2 vTextureCoord;

uniform vec4 uColor;
uniform float uTilingScale;
uniform sampler2D uTexture;

void main()
{
	colorOut = texture(uTexture, vTextureCoord * uTilingScale) * uColor;
}