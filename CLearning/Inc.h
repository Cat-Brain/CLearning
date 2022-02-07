#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CL_TARGET_OPENCL_VERSION 120
#include <CL/opencl.h>
#define FNL_IMPL
#include <FastNoiseLite/FastNoiseLite.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_Image.h"


// You can put things that you'll want everywhere in here =]

#define isoLevel 0.5f
#define chunkWidth 8

#define SHIFTINGSPEEDMULTIPLIER 2.5f


unsigned int SCR_WIDTH = 768, SCR_HEIGHT = 692;

#define BUFF_WIDTH 256
#define BUFF_HEIGHT 224

bool wireframe = false;


typedef uint8_t byte;


typedef struct Vec3
{
	float x, y, z;
} Vec3;


typedef struct
{
	void* p;
	unsigned short varSize;
} var;


typedef struct List
{
	void* l;
	unsigned int varSize;
	unsigned int count;
} List;

typedef struct VoidList
{
	void** l;
	unsigned int count;
} VoidList;


typedef unsigned int Texture;


typedef struct Camera
{
	vec3 pos, forward, up, right;
	float yaw, pitch, FOV;
	mat4 projection;
} Camera;


typedef unsigned int Shader;


typedef struct Vertex
{
	vec3 pos;
	vec3 color;
	vec3 normal;
} Vertex;

typedef struct Tri
{
	unsigned int a, b, c;
} Tri;

typedef unsigned int VBO, VAO, EBO;

typedef struct Mesh2
{
	VBO vbo;
	VAO vao;
	unsigned int vertexCount;
} Mesh2;

typedef struct Mesh
{
	VBO vbo;
	VAO vao;
	EBO ebo;
	unsigned int vertexCount;
} Mesh;


typedef struct Object
{
	Mesh mesh;
	mat4 transform;
	Shader shader;
} Object;

typedef struct Object2
{
	Mesh2 mesh;
	mat4 transform;
	Shader shader;
} Object2;

typedef struct Sprite
{
	mat4 transform;
	Shader shader;
} Sprite;


typedef struct framebuffer
{
	unsigned int FBO, TCB, RBO;
} framebuffer;

typedef struct framebuffer2
{
	unsigned int FBO, RBO, gPosition, gNormal, gAlbedoSpec;
} framebuffer2;


typedef struct CaveNoise
{
	fnl_state noise;
	float degredation;
} CaveNoise;


typedef struct HelperVec
{
	float value;
	vec3 color;
	Vec3 pos;
} HelperVec;

typedef struct HelperCube
{
	Vertex verts[12];
} HelperCube;


typedef struct SphereCollider
{
	vec3 pos, lastPos, velocity;
	float radius;
	float bounciness;
} SphereCollider;

typedef struct RaycastHit
{
	vec3 pos;
	float dist;
	vec3 norm;
} RaycastHit;


typedef struct PlayerData
{
	float moveSpeed;
	float slowDown;
	float jumpForce;
	float jumpDelay;
	float jumpGroundOffset;
	float gravity;
	float legRange;

	bool grounded;
	bool grappling;
	bool nearWall;
} PlayerData;

typedef struct Player
{
	Camera camera;
	SphereCollider collider;
	PlayerData data;
} Player;




// Custom lists require knowing about the things that they're custom to, and as such must be at the end.
#pragma region Custom lists

typedef struct Vec3List
{
	Vec3* l;
	unsigned int count;
} Vec3List;

typedef struct VertexList
{
	Vertex* l;
	unsigned int count;
} VertexList;

typedef struct TriList
{
	Tri* l;
	unsigned int count;
} TriList;

#pragma endregion



// Structs that require lists, and as such must be put at the end.

typedef struct UMesh
{
	VertexList verts;

	TriList tri;
} UMesh;

typedef struct Chunk
{
	ivec3 pos;
	byte indices[chunkWidth][chunkWidth][chunkWidth];
	float tiles[chunkWidth + 1][chunkWidth + 1][chunkWidth + 1];
	vec3 colors[chunkWidth + 1][chunkWidth + 1][chunkWidth + 1];
	VertexList verts;
	Mesh2 mesh;
} Chunk;

// Lists that require structs that require lists.

typedef struct ChunkList
{
	Chunk* l;
	unsigned int count;
} ChunkList;

// Struct that requires lists that require structs that require lists. Geez

typedef struct World
{
	ChunkList chunks;
	CaveNoise noise;
	cl_mem memObjWorld, memObjOffset;
	cl_kernel kernel;
	cl_command_queue queue;
	cl_context context;
	cl_program program;
} World;