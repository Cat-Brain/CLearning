#pragma once

#include "Shader.h"


#pragma region basicMeshs

Vertex quadVert[] = {
	{{-1.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, { 0.0f, 0.0f, 1.0f }},
	{{-1.0f,-1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, { 0.0f, 0.0f, 1.0f }},
	{{ 1.0f,-1.0f, 0.0f}, {1.0f, 0.0f, 1.0f}, { 0.0f, 0.0f, 1.0f }},
	{{ 1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, { 0.0f, 0.0f, 1.0f }}
};

Tri quadIndex[] = {
	{ 0, 1, 2 },
	{ 0, 2, 3 }
};


Vertex cubeVert[] = {
	{{ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,-1.0f }},
	{{ 1.0f,-1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f }, { 0.0f, 0.0f,-1.0f }},
	{{-1.0f,-1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f,-1.0f }},
	{{-1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 0.0f,-1.0f }},

	{{-1.0f, 1.0f,-1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }},
	{{-1.0f,-1.0f,-1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }},
	{{ 1.0f,-1.0f,-1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }},
	{{ 1.0f, 1.0f,-1.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, 1.0f }},

	{{-1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, {-1.0f, 0.0f, 0.0f }},
	{{-1.0f,-1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, {-1.0f, 0.0f, 0.0f }},
	{{-1.0f,-1.0f,-1.0f }, { 0.0f, 0.0f, 0.0f }, {-1.0f, 0.0f, 0.0f }},
	{{-1.0f, 1.0f,-1.0f }, { 0.0f, 1.0f, 0.0f }, {-1.0f, 0.0f, 0.0f }},

	{{ 1.0f, 1.0f,-1.0f }, { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }},
	{{ 1.0f,-1.0f,-1.0f }, { 1.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }},
	{{ 1.0f,-1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }},
	{{ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f, 0.0f }},

	{{ 1.0f,-1.0f, 1.0f }, { 1.0f, 0.0f, 1.0f }, { 0.0f,-1.0f, 0.0f }},
	{{ 1.0f,-1.0f,-1.0f }, { 1.0f, 0.0f, 0.0f }, { 0.0f,-1.0f, 0.0f }},
	{{-1.0f,-1.0f,-1.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f,-1.0f, 0.0f }},
	{{-1.0f,-1.0f, 1.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f,-1.0f, 0.0f }},

	{{-1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }},
	{{-1.0f, 1.0f,-1.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }},
	{{ 1.0f, 1.0f,-1.0f }, { 1.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }},
	{{ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f, 0.0f }}
};

Tri cubeIndex[] = {
	{0, 1, 2},
	{0, 2, 3},

	{4, 5, 6},
	{4, 6, 7},

	{8, 9, 10},
	{8, 10, 11},

	{12, 13, 14},
	{12, 14, 15},

	{16, 17, 18},
	{16, 18, 19},

	{20, 21, 22},
	{20, 22, 23}
};


float quadVert2D[] = {
	// position	texCoords
	  -1.0f, 1.0f, 0.0f, 1.0f,
	  -1.0f,-1.0f, 0.0f, 0.0f,
	   1.0f,-1.0f, 1.0f, 0.0f,
	   1.0f, 1.0f, 1.0f, 1.0f
};

Tri quad2DIndex[] = {
	{ 0, 1, 2},
	{ 0, 2, 3}
};

#pragma endregion

Mesh CreateMesh(Vertex* model, unsigned int vertSize, Tri* indices, unsigned int indexSize, unsigned int drawMode)
{
	Mesh result;

	result.vertexCount = indexSize / sizeof(unsigned int);

	glGenVertexArrays(1, &result.vao);
	glGenBuffers(1, &result.vbo);
	glGenBuffers(1, &result.ebo);

	glBindVertexArray(result.vao);
	glBindBuffer(GL_ARRAY_BUFFER, result.vbo);
	glBufferData(GL_ARRAY_BUFFER, vertSize, model, drawMode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, indices, drawMode);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	return result;
}

Mesh CreateMeshFromUMesh(UMesh mesh, unsigned int drawMode)
{
	Mesh result;

	result.vertexCount = mesh.tri.count * 3;

	glGenVertexArrays(1, &result.vao);
	glGenBuffers(1, &result.vbo);
	glGenBuffers(1, &result.ebo);

	glBindVertexArray(result.vao);
	glBindBuffer(GL_ARRAY_BUFFER, result.vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh.verts.count * sizeof(Vertex), mesh.verts.l, drawMode);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, result.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.tri.count * sizeof(Tri), mesh.tri.l, drawMode);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	return result;
}

Mesh2 CreateMesh2(Vertex* model, unsigned int vertSize, unsigned int drawMode)
{
	Mesh2 result;

	result.vertexCount = vertSize / sizeof(Vertex);

	glGenVertexArrays(1, &result.vao);
	glGenBuffers(1, &result.vbo);

	glBindVertexArray(result.vao);
	glBindBuffer(GL_ARRAY_BUFFER, result.vbo);
	glBufferData(GL_ARRAY_BUFFER, vertSize, model, drawMode);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	return result;
}


void DestroyMesh2(Mesh2 mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
}

void DestroyMesh(Mesh mesh)
{
	glDeleteVertexArrays(1, &mesh.vao);
	glDeleteBuffers(1, &mesh.vbo);
	glDeleteBuffers(1, &mesh.ebo);
}

Mesh  quad;
Mesh  cube;
VAO	quad2DVAO;
VBO quad2DVBO;
EBO quad2DEBO;

void CreateBasicMeshes()
{
	#pragma region quad2D

	glGenVertexArrays(1, &quad2DVAO);
	glGenBuffers(1, &quad2DVBO);
	glGenBuffers(1, &quad2DEBO);

	glBindVertexArray(quad2DVAO);
	glBindBuffer(GL_ARRAY_BUFFER, quad2DVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVert2D), &quadVert2D, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quad2DEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad2DIndex), quad2DIndex, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (void*)(sizeof(float) * 2));

	#pragma endregion

	quad = CreateMesh(quadVert, sizeof(quadVert), quadIndex, sizeof(quadIndex), GL_STATIC_DRAW);
	cube = CreateMesh(cubeVert, sizeof(cubeVert), cubeIndex, sizeof(cubeIndex), GL_STATIC_DRAW);
}

void DeleteBasicMeshes()
{
	glDeleteVertexArrays(1, &quad2DVAO);
	glDeleteBuffers(1, &quad2DVBO);
	glDeleteBuffers(1, &quad2DEBO);

	DestroyMesh(quad);
	DestroyMesh(cube);
}