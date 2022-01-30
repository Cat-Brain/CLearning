#pragma once
#include "Mesh.h"

Object CreateObject11(Mesh mesh, Shader shader)
{
	Object object;

	object.mesh = mesh;
	glm_mat4_identity((vec4*)&object.transform);

	object.shader = shader;

	return object;
}

Object CreateObject12(Vertex* vertices, unsigned int vertSize, Tri* indices, unsigned int indexSize, unsigned int drawMode, char vert[], char frag[])
{
	Object object;

	object.mesh = CreateMesh(vertices, vertSize, indices, indexSize, drawMode);
	glm_mat4_identity(object.transform);

	object.shader = CreateShader2(vert, frag);

	return object;
}

Object CreateObject13(Vertex* vertices, unsigned int vertSize, Tri* indices, unsigned int indexSize, unsigned int drawMode, Shader shader)
{
	Object object;

	object.mesh = CreateMesh(vertices, vertSize, indices, indexSize, drawMode);
	glm_mat4_identity(object.transform);

	object.shader = shader;

	return object;
}


Object2 CreateObject21(Mesh2 mesh, Shader shader)
{
	Object2 object;

	object.mesh = mesh;
	glm_mat4_identity(object.transform);

	object.shader = shader;

	return object;
}

Object2 CreateObject22(Vertex* vertices, unsigned int vertSize, unsigned int drawMode, char vert[], char frag[])
{
	Object2 object;

	object.mesh = CreateMesh2(vertices, vertSize, drawMode);
	glm_mat4_identity(object.transform);

	object.shader = CreateShader2(vert, frag);

	return object;
}

Object2 CreateObject23(Vertex* vertices, unsigned int vertSize, unsigned int drawMode, Shader shader)
{
	Object2 object;

	object.mesh = CreateMesh2(vertices, vertSize, drawMode);
	glm_mat4_identity(object.transform);

	object.shader = shader;

	return object;
}


Sprite CreateSpritet1(Shader shader, vec2 scale)
{
	Sprite sprite;

	glm_mat4_identity(sprite.transform);
	glm_scale(sprite.transform, (vec3) { scale[0], 1.0f, scale[1] });

	sprite.shader = shader;

	return sprite;
}

Sprite CreateSprite2(char vert[], char frag[], vec2 scale)
{
	Sprite sprite;

	glm_mat4_identity(sprite.transform);
	glm_scale(sprite.transform, (vec3) { scale[0], 1.0f, scale[1] });

	sprite.shader = CreateShader2(vert, frag);

	return sprite;
}




void DrawObject1(Object object, Camera camera)
{
	glUseProgram(object.shader);
	glBindVertexArray(object.mesh.vao);
	glUniformMatrix4fv(glGetUniformLocation(object.shader, "model"), 1, GL_FALSE, object.transform[0]);
	mat4 camViewMat;
	CamToMat(camera, &camViewMat);
	glUniformMatrix4fv(glGetUniformLocation(object.shader, "view"), 1, GL_FALSE, camViewMat[0]);
	glUniformMatrix4fv(glGetUniformLocation(object.shader, "projection"), 1, GL_FALSE, camera.projection[0]);

	mat4 normalMat4;
	mat3 normalMat3;

	glm_mat4_inv(object.transform, normalMat4);
	glm_mat4_transpose(normalMat4);

	#pragma region normalMat 3 to 4

	normalMat3[0][0] = normalMat4[0][0];
	normalMat3[1][0] = normalMat4[1][0];
	normalMat3[2][0] = normalMat4[2][0];

	normalMat3[0][1] = normalMat4[0][1];
	normalMat3[1][1] = normalMat4[1][1];
	normalMat3[2][1] = normalMat4[2][1];

	normalMat3[0][2] = normalMat4[0][2];
	normalMat3[1][2] = normalMat4[1][2];
	normalMat3[2][2] = normalMat4[2][2];

	#pragma endregion
	glUniformMatrix3fv(glGetUniformLocation(object.shader, "normalMat"), 1, GL_FALSE, normalMat3[0]);

	glDrawElements(GL_TRIANGLES, object.mesh.vertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DrawObject2(Object2 object, Camera camera)
{
	glUseProgram(object.shader);
	glBindVertexArray(object.mesh.vao);
	glUniformMatrix4fv(glGetUniformLocation(object.shader, "model"), 1, GL_FALSE, object.transform[0]);
	mat4 camViewMat;
	CamToMat(camera, &camViewMat);
	glUniformMatrix4fv(glGetUniformLocation(object.shader, "view"), 1, GL_FALSE, camViewMat[0]);
	glUniformMatrix4fv(glGetUniformLocation(object.shader, "projection"), 1, GL_FALSE, camera.projection[0]);

	mat4 normalMat4;
	mat3 normalMat3;

	glm_mat4_inv(object.transform, normalMat4);
	glm_mat4_transpose(normalMat4);

	#pragma region normalMat 3 to 4

	normalMat3[0][0] = normalMat4[0][0];
	normalMat3[1][0] = normalMat4[1][0];
	normalMat3[2][0] = normalMat4[2][0];

	normalMat3[0][1] = normalMat4[0][1];
	normalMat3[1][1] = normalMat4[1][1];
	normalMat3[2][1] = normalMat4[2][1];

	normalMat3[0][2] = normalMat4[0][2];
	normalMat3[1][2] = normalMat4[1][2];
	normalMat3[2][2] = normalMat4[2][2];

	#pragma endregion
	glUniformMatrix3fv(glGetUniformLocation(object.shader, "normalMat"), 1, GL_FALSE, normalMat3[0]);

	glDrawArrays(GL_TRIANGLES, 0, object.mesh.vertexCount);
	glBindVertexArray(0);
}

void DrawSprite(Sprite sprite)
{
	glUseProgram(sprite.shader);
	glBindVertexArray(quad2DVAO);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DrawMesh11(Mesh mesh, Camera camera, Shader shader)
{
	glUseProgram(shader);
	glBindVertexArray(mesh.vao);
	mat4 identity4;
	glm_mat4_identity(identity4);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float*)identity4);
	mat4 camViewMat;
	CamToMat(camera, &camViewMat);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, camViewMat[0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, camera.projection[0]);

	mat3 identity3;
	glm_mat3_identity(identity3);
	glUniformMatrix3fv(glGetUniformLocation(shader, "normalMat"), 1, GL_FALSE, (float*)identity3);

	glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DrawMesh12(Mesh mesh, Camera camera, Shader shader)
{
	glUseProgram(shader);
	glBindVertexArray(mesh.vao);
	mat4 camViewMat;
	CamToMat(camera, &camViewMat);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, camViewMat[0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, camera.projection[0]);

	glDrawElements(GL_TRIANGLES, mesh.vertexCount, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void DrawMesh21(Mesh2 mesh, Camera camera, Shader shader)
{
	glUseProgram(shader);
	glBindVertexArray(mesh.vao);
	mat4 identity4;
	glm_mat4_identity(identity4);
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, (float*)identity4);
	mat4 camViewMat;
	CamToMat(camera, &camViewMat);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, camViewMat[0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, camera.projection[0]);

	mat3 identity3;
	glm_mat3_identity(identity3);
	glUniformMatrix3fv(glGetUniformLocation(shader, "normalMat"), 1, GL_FALSE, (float*)identity3);

	glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
	glBindVertexArray(0);
}

void DrawMesh22(Mesh2 mesh, Camera camera, Shader shader)
{
	glUseProgram(shader);
	glBindVertexArray(mesh.vao);
	mat4 camViewMat;
	CamToMat(camera, &camViewMat);
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, GL_FALSE, camViewMat[0]);
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, GL_FALSE, camera.projection[0]);

	glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
	glBindVertexArray(0);
}

void DestroyObject(Object object)
{
	DestroyMesh(object.mesh);
}

void DestroyObject2(Object2 object)
{
	DestroyMesh2(object.mesh);
}