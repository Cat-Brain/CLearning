#pragma once
#include "Multithread.h"

Texture LoadTexture(char* location, unsigned int stringLength, GLint linearity, GLint uvStretching)
{
	Texture texture;
	glGenTextures(1, &texture);
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uvStretching);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, uvStretching);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearity);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearity);

	int width, height, nrChannels;
	unsigned char* data = stbi_load(location, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture =[\n");
	}
	stbi_image_free(data);

	return texture;
}

Texture CreateTexture(void* pixels, GLint internalFormat, GLint format, unsigned int width, unsigned int height, GLint linearity, GLint uvStretching)
{
	Texture texture;
	glGenTextures(1, &texture);
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uvStretching);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, uvStretching);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearity);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearity);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	return texture;
}

Texture CreateTexture2(void* pixels, GLint internalFormat, GLint format, unsigned int width, unsigned int height, GLint linearity, GLint uvStretching)
{
	Texture texture;
	glGenTextures(1, &texture);
	glActiveTexture(texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, uvStretching);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, uvStretching);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, linearity);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, linearity);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);

	return texture;
}

/*kernel* void GenerateChunkMesh(/*global *Chunk* chunks, Vertex* retVerts, global unsigned int* offsets)
{
	int id/* = get_global_id(0)*;
	Chunk* chunk = chunks[id];
	int activeVert = offsets[id];

	float currentValues[8];
	vec3 currentColors[8];
	vec3 currentPos;

	HelperCube cubes[chunkWidth][chunkWidth][chunkWidth];

	for (int x = 0; x < chunkWidth; x++)
	{
		currentPos[0] = x + chunk->pos[0] * chunkWidth - (chunkWidth / 2.0f);

		for (int y = 0; y < chunkWidth; y++)
		{
			currentPos[1] = y + chunk->pos[1] * chunkWidth - (chunkWidth / 2.0f);

			for (int z = 0; z < chunkWidth; z++)
			{
				currentPos[2] = z + chunk->pos[2] * chunkWidth - (chunkWidth / 2.0f);

				currentValues[0] = chunk->tiles[x][y][z];
				glm_vec3_copy(chunk->colors[x][y][z], currentColors[0]);

				currentValues[1] = chunk->tiles[x + 1][y][z];
				glm_vec3_copy(chunk->colors[x + 1][y][z], currentColors[1]);

				currentValues[2] = chunk->tiles[x + 1][y][z + 1];
				glm_vec3_copy(chunk->colors[x + 1][y][z + 1], currentColors[2]);

				currentValues[3] = chunk->tiles[x][y][z + 1];
				glm_vec3_copy(chunk->colors[x][y][z + 1], currentColors[3]);

				currentValues[4] = chunk->tiles[x][y + 1][z];
				glm_vec3_copy(chunk->colors[x][y + 1][z], currentColors[4]);

				currentValues[5] = chunk->tiles[x + 1][y + 1][z];
				glm_vec3_copy(chunk->colors[x + 1][y + 1][z], currentColors[5]);

				currentValues[6] = chunk->tiles[x + 1][y + 1][z + 1];
				glm_vec3_copy(chunk->colors[x + 1][y + 1][z + 1], currentColors[6]);

				currentValues[7] = chunk->tiles[x][y + 1][z + 1];
				glm_vec3_copy(chunk->colors[x][y + 1][z + 1], currentColors[7]);



				//#pragma region Find vertices

				cubes[x][y][z].verts[0] = VertInterp(currentPos, currentValues[0], currentColors[0], (vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] }, currentValues[1], currentColors[1]);
				cubes[x][y][z].verts[1] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] }, currentValues[1], currentColors[1], (vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] + 1 }, currentValues[2], currentColors[2]);
				cubes[x][y][z].verts[2] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] + 1 }, currentValues[2], currentColors[2], (vec3) { currentPos[0], currentPos[1], currentPos[2] + 1 }, currentValues[3], currentColors[3]);
				cubes[x][y][z].verts[3] = VertInterp((vec3) { currentPos[0], currentPos[1], currentPos[2] + 1 }, currentValues[3], currentColors[3], currentPos, currentValues[0], currentColors[0]);

				cubes[x][y][z].verts[4] = VertInterp((vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] }, currentValues[4], currentColors[4], (vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] }, currentValues[5], currentColors[5]);
				cubes[x][y][z].verts[5] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] }, currentValues[5], currentColors[5], (vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] + 1 }, currentValues[6], currentColors[6]);
				cubes[x][y][z].verts[6] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] + 1 }, currentValues[6], currentColors[6], (vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] + 1 }, currentValues[7], currentColors[7]);
				cubes[x][y][z].verts[7] = VertInterp((vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] + 1 }, currentValues[7], currentColors[7], (vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] }, currentValues[4], currentColors[4]);

				cubes[x][y][z].verts[8] = VertInterp(currentPos, currentValues[0], currentColors[0], (vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] }, currentValues[4], currentColors[4]);
				cubes[x][y][z].verts[9] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] }, currentValues[1], currentColors[1], (vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] }, currentValues[5], currentColors[5]);
				cubes[x][y][z].verts[10] = VertInterp((vec3) { currentPos[0] + 1, currentPos[1], currentPos[2] + 1 }, currentValues[2], currentColors[2], (vec3) { currentPos[0] + 1, currentPos[1] + 1, currentPos[2] + 1 }, currentValues[6], currentColors[6]);
				cubes[x][y][z].verts[11] = VertInterp((vec3) { currentPos[0], currentPos[1], currentPos[2] + 1 }, currentValues[3], currentColors[3], (vec3) { currentPos[0], currentPos[1] + 1, currentPos[2] + 1 }, currentValues[7], currentColors[7]);

				//#pragma endregion

				Tri value;
				for (char i = 0; i < triTable[cubes[x][y][z].index][15] * 3; i += 3)
				{
					//printf("%i : ", cubes[x][y][z].index);
					value.a = triTable[cubes[x][y][z].index][i];
					value.b = triTable[cubes[x][y][z].index][i + 1];
					value.c = triTable[cubes[x][y][z].index][i + 2];


					vec3 tempVecs[3];

					glm_vec3_sub(cubes[x][y][z].verts[value.b].pos, cubes[x][y][z].verts[value.a].pos, tempVecs[0]);
					glm_vec3_sub(cubes[x][y][z].verts[value.c].pos, cubes[x][y][z].verts[value.a].pos, tempVecs[1]);

					glm_cross(tempVecs[0], tempVecs[1], tempVecs[2]);
					//glm_vec3_normalize(tempVecs[2]);


					glm_vec3_copy(tempVecs[2], cubes[x][y][z].verts[value.a].normal);
					glm_vec3_copy(tempVecs[2], cubes[x][y][z].verts[value.b].normal);
					glm_vec3_copy(tempVecs[2], cubes[x][y][z].verts[value.c].normal);


					retVerts[activeVert] = cubes[x][y][z].verts[value.a];
					retVerts[activeVert + 1] = cubes[x][y][z].verts[value.b];
					retVerts[activeVert + 2] = cubes[x][y][z].verts[value.c];

					activeVert += 3;
				}
			}
		}
	}

	Vertex VertInterp(vec3 aPos, float aVal, vec3 aCol, vec3 bPos, float bVal, vec3 bCol)
	{
		Vertex result;

		if (bVal - aVal == 0)
		{
			result.pos[0] = (aPos[0] + bPos[0]) * 0.5f;
			result.pos[1] = (aPos[1] + bPos[1]) * 0.5f;
			result.pos[2] = (aPos[2] + bPos[2]) * 0.5f;
		}
		else
		{
			float mu = (isoLevel - aVal) / (bVal - aVal);


			result.pos[0] = aPos[0] + mu * (bPos[0] - aPos[0]);
			result.pos[1] = aPos[1] + mu * (bPos[1] - aPos[1]);
			result.pos[2] = aPos[2] + mu * (bPos[2] - aPos[2]);

			result.color[0] = aCol[0] + mu * (bCol[0] - aCol[0]);
			result.color[1] = aCol[1] + mu * (bCol[1] - aCol[1]) + 0.5f;
			result.color[2] = aCol[2] + mu * (bCol[2] - aCol[2]);
		}
		return result;
	}*/