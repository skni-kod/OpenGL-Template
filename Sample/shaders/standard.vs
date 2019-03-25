#version 330 core
layout (location = 0) in vec3 position;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uvs;
layout (location = 4) in vec3 tangent;

out vec3 fragPos;
out vec3 norm;
out vec4 lightSpacePos;
out vec2 uv;
out mat3 TBN;

uniform mat4 model;
uniform mat4 MVP;
uniform mat3 normalModel;
uniform mat4 lightSpaceMatrix;

void main()
{
	vec3 T = normalize(vec3(model * vec4(tangent, 0.0)));
	vec3 N = normalize(vec3(model * vec4(normal, 0.0)));

	vec3 bitangent = cross(T, N);
	vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
	TBN = mat3(T,B,N);

	uv = uvs;
	fragPos = vec3( model * vec4(position, 1.0f));
    gl_Position = MVP * vec4(position, 1.0f);
	norm = normalModel * normal;
	lightSpacePos = lightSpaceMatrix * vec4(fragPos, 1);
}