#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

uniform mat4 u_mvp;

out float zCoord;

void main() {
	zCoord = position.z;
	gl_Position = u_mvp * position;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

in float zCoord;

void main() {
	color = vec4(u_Color.xyz * ((zCoord / 2.0f) + 0.5f),u_Color.w);
};