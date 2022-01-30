#pragma once
#include "Physics.h"

void CreatePlayer(Player* player)
{
	CreateCamera(&player->camera);
	player->data.moveSpeed = 0.05f;
	player->data.slowDown = 1.0f - 0.75f;
	player->data.jumpForce = 0.05f;
	player->data.jumpDelay = 0.1f;
	player->data.jumpGroundOffset = 0.3f;
	player->data.gravity = 0.05f;
	player->data.grappleDist = 100.0f;
	player->data.grappleStrength = 0.25f;
	player->data.grappleMoveMul = 0.25f;

	player->data.legRange = 0.5f;

	player->collider.radius = 0.5f;
	player->collider.bounciness = 0.25f;
}

void MovePlayer(Player* player, vec3 input)
{
	player->collider.velocity[0] += (input[2] * player->camera.forward[0] + input[1] * player->camera.up[0] + input[0] * player->camera.right[0]) * player->data.moveSpeed;
	player->collider.velocity[1] += (input[2] * player->camera.forward[1] + input[1] * player->camera.up[1]) * player->data.moveSpeed;
	player->collider.velocity[2] += (input[2] * player->camera.forward[2] + input[1] * player->camera.up[2] + input[0] * player->camera.right[2]) * player->data.moveSpeed;
}

void UpdatePlayer(Player* player, World world)
{
	// Do some basic player updating.
	glm_vec3_add(player->collider.velocity, player->collider.pos, player->collider.pos);




	// Update the collision of the player.
	ivec3 minPos, maxPos;

	minPos[0] = roundf((player->collider.pos[0] - player->collider.radius) / chunkWidth);
	minPos[1] = roundf((player->collider.pos[1] - player->collider.radius) / chunkWidth);
	minPos[2] = roundf((player->collider.pos[2] - player->collider.radius) / chunkWidth);

	maxPos[0] = roundf((player->collider.pos[0] + player->collider.radius) / chunkWidth);
	maxPos[1] = roundf((player->collider.pos[1] + player->collider.radius) / chunkWidth);
	maxPos[2] = roundf((player->collider.pos[2] + player->collider.radius) / chunkWidth);


	player->data.grounded = false;
	player->data.nearWall = false;
	for (int x = minPos[0]; x <= maxPos[0]; x++)
		for (int y = minPos[1]; y <= maxPos[1]; y++)
			for (int z = minPos[2]; z <= maxPos[2]; z++)
			{
				int16_t chunkIndex = -1;
				for (int i = 0; i < world.chunks.count; i++)
					chunkIndex = (glm_vec3_eqv((vec3) { x, y, z }, (vec3) { world.chunks.l[i].pos[0], world.chunks.l[i].pos[1], world.chunks.l[i].pos[2] }) ? i : chunkIndex);
				if (chunkIndex == -1)
				{
					printf("(%i, %i, %i) : (%f, %f, %f), ", x, y, z, player->collider.pos[0], player->collider.pos[1], player->collider.pos[2]);
				}
				else
				{
					for (uint16_t i = 0; i * 3 < world.chunks.l[chunkIndex].verts.count; i++)
					{
						SphereTriangleCollision(&player->collider, &world.chunks.l[chunkIndex].verts.l[i * 3]);

						/*vec3 offset;
						glm_vec3_scale(player->camera.forward, player->data.jumpGroundOffset, offset);
						glm_vec3_sub(player->collider.pos, offset, player->collider.pos);
						player->data.grounded = max(player->data.grounded, SphereTriangleColliding(&player->collider, &world.chunks.l[chunkIndex].verts.l[i * 3]));
						glm_vec3_add(player->collider.pos, offset, player->collider.pos);*/

						player->collider.radius += player->data.legRange;
						player->data.nearWall = max(player->data.nearWall, SphereTriangleColliding(&player->collider, &world.chunks.l[chunkIndex].verts.l[i * 3]));
						player->collider.radius -= player->data.legRange;
					}
				}
			}

	// Set the position of the player's camera equal to the player's position in the collider.
	glm_vec3_copy(player->collider.pos, player->camera.pos);
	glm_vec3_copy(player->collider.pos, player->collider.lastPos);
}