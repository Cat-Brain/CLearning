#pragma once

#include "Camera.h"
//#include "File.h"


Shader CreateShader2(const char vert[], const char frag[])
{
	unsigned int vertShader, fragShader, shader;
	vertShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShader, 1, &vert, NULL);
	glCompileShader(vertShader);

	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShader, 1, &frag, NULL);
	glCompileShader(fragShader);


	int success;
	char infoLog[1024];
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertShader, 1024, NULL, infoLog);
		printf("\nERROR::SHADER::VERTEX::COMPILATION_FAILED\n");
		printf(infoLog);
		printf("\n");
	}
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragShader, 1024, NULL, infoLog);
		printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n");
		printf(infoLog);
		printf("\n\n");
	}

	shader = glCreateProgram();
	glAttachShader(shader, vertShader);
	glAttachShader(shader, fragShader);
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		printf("\nERROR::SHADER::PROGRAM::COMPILATION_FAILED\n");
		printf(infoLog);
		printf("\n\n");
	}


	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return shader;
}


#pragma region Shaders

const char BASIC_VERT_SHADER[] =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec3 aNormal;\n"
"\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"\n"
"out vec3 color;\n"
"\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);\n"
"	color = aColor;\n"
"}\0";

const char BASIC_FRAG_SHADER[] =
"#version 330 core\n"
"in vec3 color;\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"   FragColor = vec4(color, 1.0);\n"
"}\0";


const char BASIC_TEX_VERT_SHADER[] =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec3 aNormal;\n"
"\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"\n"
"out vec2 uv;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos.xyz, 1.0);\n"
"	uv = aColor.xy;\n"
"}\0";

const char BASIC_TEX_FRAG_SHADER[] =
"#version 330 core\n"
"in vec2 uv;\n"
"uniform sampler2D tex;\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = texture(tex, uv);\n"
"}\0";


const char FBO_VERT_SHADER[] =
"#version 330 core\n"
"layout(location = 0) in vec2 aPos;\n"
"layout(location = 1) in vec2 aUV;\n"
"\n"
"out vec2 uv;\n"
"\n"
"void main()\n"
"{\n"
"	uv = aUV;\n"
"	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"}\0";

const char FBO_FRAG_SHADER[] =
"#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"in vec2 uv;\n"
"\n"
"uniform sampler2D tex;\n"
"\n"
"void main()\n"
"{\n"
"	vec3 col = texture(tex, uv).rgb;\n"
"	FragColor = vec4(col.rgb, 1.0);\n"
"}\0";


const char POST_VERT_SHADER[] =
"#version 330 core\n"
"layout(location = 0) in vec2 aPos;\n"
"layout(location = 1) in vec2 aUV;\n"
"\n"
"out vec2 uv;\n"
"\n"
"void main()\n"
"{\n"
"	uv = aUV;\n"
"	gl_Position = vec4(aPos, 0.0, 1.0);\n"
"}\0";

const char POST_FRAG_SHADER[] =
"#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"in vec2 uv;\n"
"\n"
"uniform sampler2D tex;\n"
"uniform float intensity;\n"
"uniform float outlineWidth;\n"
"uniform vec2 screenDimensions;\n"
"\n"
"void main()\n"
"{\n"
"	const float gamma = 2.2;\n"
"	vec4 render = texture(tex, uv);\n"
"	vec3 col = render.rgb;\n"
"\n"
"	col *= intensity;\n"
"\n"
"	// reinhard tone mapping\n"
"	col = col / (col + vec3(1.0));\n"
"\n"
"	float halfScaleFloor = floor(outlineWidth * 0.5);\n"
"float halfScaleCeil = ceil(outlineWidth * 0.5);\n"
"\n"
"	vec2 bottomLeftUV = uv - vec2(screenDimensions.x, screenDimensions.y) * halfScaleFloor;\n"
"	vec2 topRightUV = uv + vec2(screenDimensions.x, screenDimensions.y) * halfScaleCeil;\n"
"	vec2 bottomRightUV = uv + vec2(screenDimensions.x * halfScaleCeil, -screenDimensions.y * halfScaleFloor);\n"
"	vec2 topLeftUV = uv + vec2(-screenDimensions.x * halfScaleFloor, screenDimensions.y * halfScaleCeil);\n"
"\n"
"	vec3 cBottomLeft = texture(tex, bottomLeftUV).rgb;\n"
"	//col = cBottomLeft;\n"
"\n"
"	// gamma correction\n"
"	col = pow(col, vec3(1.0 / gamma));\n"
"\n"
"\n"
"	FragColor = vec4(col.rgb, 1.0);\n"
"}\0";


const char SKYBOX_VERT_SHADER[] =
"#version 330 core\n"
"layout(location = 0) in vec2 aPos;\n"
"layout(location = 1) in vec2 aUV;\n"
"\n"
"\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"}\0";

const char SKYBOX_FRAG_SHADER[] =
"#version 330 core\n"
"uniform vec3 viewDir;\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{\n"
"   FragColor = vec4(viewDir, 1.0);\n"
"}\0";


const char DEFAULT_DIFF_VERT[] =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec3 aNormal;\n"
"\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"uniform mat3 normalMat;\n"
"\n"
"out vec3 color;\n"
"out vec3 fragPos;\n"
"out vec3 normal;\n"
"\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos.x,-aPos.y, aPos.z, 1.0);\n"
"	fragPos = vec3(model * vec4(aPos, 1.0));\n"
"	color = aColor;\n"
"	normal = normalMat * aNormal;\n"
"}\0";


const char DIFF2_VERT[] =
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec3 aNormal;\n"
"\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"\n"
"out vec3 color;\n"
"out vec3 fragPos;\n"
"out vec3 normal;\n"
"\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * vec4(aPos.x, -aPos.y, aPos.z, 1.0);\n"
"	fragPos = aPos;\n"
"	color = aColor;\n"
"	normal = aNormal;\n"
"}\0";

const char DEFAULT_DIFF_FRAG[] =
"#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"in vec3 color;\n"
"in vec3 fragPos;\n"
"in vec3 normal;\n"
"\n"
"struct Light {\n"
"	vec3 pos;\n"
"	vec3 color;\n"
"};\n"
"const int NR_LIGHTS = 1;\n"
"uniform Light lights[NR_LIGHTS];\n"
"uniform vec3 viewPos;\n"
"uniform float ambient, diff, spec, quadraticAttenuation;"
"\n"
"void main()\n"
"{\n"
"\n"
"	// Calculate lighting.\n"
"	vec3 norm = normalize(normal);\n"
"	vec3 lighting = color * ambient; // hard-coded ambient component\n"
"	vec3 viewDir = normalize(viewPos - fragPos);\n"
"	for (int i = 0; i < NR_LIGHTS; i++)\n"
"	{\n"
"		// diffuse\n"
"		vec3 lightDir = fragPos - lights[i].pos;\n"
"		float attenuation = 1.0 / dot(lightDir, lightDir) * quadraticAttenuation * quadraticAttenuation;\n"
"		lightDir = normalize(lightDir);\n"
"		vec3 diffuse = max(dot(norm, lightDir), 0.0) * color * diff * attenuation;\n"
"		lighting += diffuse;\n"
"	}\n"
"\n"
"	FragColor = vec4(lighting, 1.0);\n"
"}\0";


#pragma endregion

Shader DEFAULT_SHADER;
Shader DEFAULT_TEX_SHADER;
Shader GRID_SHADER;
Shader DEFAULT_DIFFUSE_SHADER;
Shader DIFF2_SHADER;
Shader TEXTURE_DIFFUSE_SHADER;

Shader FBO_SHADER;
Shader POST_PROCESSING_SHADER;
Shader SKYBOX_SHADER;

void CreateBasicShaders()
{
	DEFAULT_SHADER = CreateShader2(BASIC_VERT_SHADER, BASIC_FRAG_SHADER);
	DEFAULT_TEX_SHADER = CreateShader2(BASIC_TEX_VERT_SHADER, BASIC_TEX_FRAG_SHADER);
	GRID_SHADER = CreateShader2(BASIC_VERT_SHADER, BASIC_FRAG_SHADER);
	DEFAULT_DIFFUSE_SHADER = CreateShader2(DEFAULT_DIFF_VERT, DEFAULT_DIFF_FRAG);
	DIFF2_SHADER = CreateShader2(DIFF2_VERT, DEFAULT_DIFF_FRAG);
	//TEXTURE_DIFFUSE_SHADER = CreateShader2(DEFAULT_DIFF_VERT, TEXTURE_DIFF_FRAG);

	FBO_SHADER = CreateShader2(FBO_VERT_SHADER, FBO_FRAG_SHADER);
	POST_PROCESSING_SHADER = CreateShader2(POST_VERT_SHADER, POST_FRAG_SHADER);
	SKYBOX_SHADER = CreateShader2(SKYBOX_VERT_SHADER, SKYBOX_FRAG_SHADER);
}

void SetBasicUniforms(Camera camera, float quadraticAttenuation)
{
	glUseProgram(DIFF2_SHADER);
	glUniform3f(glGetUniformLocation(DIFF2_SHADER, "lights[0].pos"), camera.pos[0], camera.pos[1], camera.pos[2]);
	glUniform3f(glGetUniformLocation(DIFF2_SHADER, "viewPos"), camera.pos[0], camera.pos[1], camera.pos[2]);

	glUniform1f(glGetUniformLocation(DIFF2_SHADER, "ambient"), 0.0f);
	glUniform1f(glGetUniformLocation(DIFF2_SHADER, "diff"), 1.0f);
	glUniform1f(glGetUniformLocation(DIFF2_SHADER, "spec"), 0.25f);

	glUniform1f(glGetUniformLocation(DIFF2_SHADER, "quadraticAttenuation"), quadraticAttenuation);

	glUseProgram(POST_PROCESSING_SHADER);
	glUniform1f(glGetUniformLocation(POST_PROCESSING_SHADER, "intensity"), 0.5f);
	glUniform1f(glGetUniformLocation(POST_PROCESSING_SHADER, "outlineWidth"), 10.0f);
	glUniform2f(glGetUniformLocation(POST_PROCESSING_SHADER, "screenDimensions"), (float)BUFF_WIDTH, (float)BUFF_HEIGHT);
}

void DestroyShader(Shader shader)
{
	glDeleteProgram(shader);
}

void DeleteBasicShaders()
{
	glDeleteProgram(DEFAULT_SHADER);
	glDeleteProgram(DEFAULT_TEX_SHADER);
	glDeleteProgram(GRID_SHADER);
	glDeleteProgram(DEFAULT_DIFFUSE_SHADER);
	glDeleteProgram(FBO_SHADER);
	glDeleteProgram(POST_PROCESSING_SHADER);
	glDeleteProgram(SKYBOX_SHADER);
}