#pragma once

#include "Texture.h"

void CreateCamera(Camera* c)
{
	c->FOV = 80.0f;
	c->up[1] = 1.0f;
	c->forward[2] = 1.0f;
	c->right[0] = 1.0f;
	glm_perspective(c->FOV, 1.0f, 0.1f, 100.0f, c->projection);
}

void CamToMat(Camera c, mat4* result)
{
	glm_mat4_identity(result);

	glm_lookat((vec3) { c.pos[0], -c.pos[1], c.pos[2]}, (vec3) { c.forward[0] + c.pos[0], -c.forward[1] + -c.pos[1], c.forward[2] + c.pos[2]}, (vec3) { 0.0f, 1.0f, 0.0f }, result);
	//glm_mat4_identity(result);
}