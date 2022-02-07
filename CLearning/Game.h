#pragma once

#include "Player.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xPos, double yPos);
void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(float deltaTime);

void MultiplayerInit();

void GLFWInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}


#pragma region Constant variables

#define sensitivity 0.3f
#define scrollSensitivity 0.1f

#pragma endregion


#pragma region non-constant variables

GLFWwindow* window;

Player player;

Object webHitObject;
Object2 MarchingCubesObject;

World world;

bool firstFrameForMouse = true;
bool mouseLocked = true;

float chunkRenderDist = 3.0f;

int error = 0;

Texture brickTex;

framebuffer FB, FB2;

bool restart;

#pragma endregion


void Start()
{
	GLFWInit();

	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Marching cubes!", NULL, NULL);
	if (window == NULL)
	{
		printf("Failed to create GLFW window\n");
		glfwTerminate();
		error = -1;
	}
	glfwMakeContextCurrent(window);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, mouseScrollCallback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		printf("Failed to initialize GLAD\n");
		error = -1;
	}

#ifndef CULLBACKFACES
	//glEnable(GL_CULL_FACE);
#endif

	CreateBasicShaders();
	CreateBasicMeshes();

	CreateFramebuffer(&FB);
	CreateFramebuffer(&FB2);

	//char brickTexLocation[] = "Resources/Textures/Images/Brick.jpg";
	//brickTex = GenTexture(brickTexLocation, sizeof(brickTexLocation) / sizeof(char), GL_NEAREST, GL_REPEAT);

	CreatePlayer(&player);


#pragma region Marching cubes and noise

	int noiseType;
	float noiseMultiplier = 0.5f;
	bool hasInputed = false;
	bool holdingKey = false;
	
		while (!hasInputed)
		{
			if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
			{
				if (!holdingKey)
				{
					noiseType = 0;
					hasInputed = true;
					holdingKey = true;
				}
			}
			else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
			{
				if (!holdingKey)
				{
					noiseType = 1;
					hasInputed = true;
					holdingKey = true;
				}
			}
			else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
			{
				if (!holdingKey)
				{
					noiseType = 2;
					hasInputed = true;
					holdingKey = true;
				}
			}
			else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
			{
				if (!holdingKey)
				{
					noiseType = 3;
					hasInputed = true;
					holdingKey = true;
				}
			}
			else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
			{
				if (!holdingKey)
				{
					noiseType = 4;
					hasInputed = true;
					holdingKey = true;
				}
			}
			else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
			{
				if (!holdingKey)
				{
					noiseType = 5;
					hasInputed = true;
					holdingKey = true;
				}
			}
			else holdingKey = false;
			glfwPollEvents();
		}

	world.noise.noise = fnlCreateState();
	world.noise.noise.noise_type = noiseType;
	world.noise.noise.cellular_distance_func = FNL_CELLULAR_DISTANCE_EUCLIDEAN;
	//world.noise.noises[0][0].cellular_return_type = FNL_CELLULAR_RETURN_VALUE_DISTANCE;
	world.noise.noise.seed = (int)time(NULL);

	world.noise.degredation = 0.75f;

	
	CreateWorld(&world, player.camera, chunkRenderDist);

	#pragma endregion

	webHitObject = CreateObject11(cube, DEFAULT_DIFFUSE_SHADER);
}

float prevTime = 0.0f;
int temp = 0.0f;

void Update()
{
	float time = glfwGetTime();
	float deltaTime = time - prevTime;
	float FPS = 1.0f / deltaTime;
	char buff[10];
	int err = _gcvt_s(buff, sizeof(buff), (float)FPS, 5);
	if (err != 0)
	{
		printf("_gcvt_s failed with error code %d\n", err);
		glfwSetWindowShouldClose(window, 1);
	}

	char* title = "Marching cubes! Also, the frame rate is:           ";
	//strcat_s(title, sizeof(title) / sizeof(char), buff);
	glfwSetWindowTitle(window, title);

	processInput(deltaTime);

	glBindFramebuffer(GL_FRAMEBUFFER, FB.FBO);
	glViewport(0, 0, BUFF_WIDTH, BUFF_HEIGHT);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	#pragma region rendering

	SetBasicUniforms(player.camera, /*0.0f*/3.0f);
	

	UpdateWorld(&world, player.camera, chunkRenderDist);

	for (int i = 0; i < world.chunks.count; i++)
	{
		DrawMesh22(world.chunks.l[i].mesh, player.camera, DIFF2_SHADER);
	}

	DrawObject1(webHitObject, player.camera);

	UpdatePlayer(&player, world);

	#pragma endregion

	if (wireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisable(GL_DEPTH_TEST);

	RenderFramebuffer11(FB, FB2, POST_PROCESSING_SHADER);


	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

	RenderFramebuffer11(FB2, screen, FBO_SHADER);

	prevTime = time;

	glfwSwapBuffers(window);
	glfwPollEvents();
}

void End()
{
	glfwTerminate();

	DeleteBasicShaders();
	DeleteBasicMeshes();

	DestroyObject2(MarchingCubesObject);

	for (int i = 0; i < world.chunks.count; i++)
		free(world.chunks.l[i].verts.l);
	free(world.chunks.l);
	world.chunks.l = 0;
	world.chunks.count = 0;

	clReleaseKernel(world.kernel);
	clReleaseProgram(world.program);
	clReleaseMemObject(world.mem_obj);
	clReleaseCommandQueue(world.queue);
	clReleaseContext(world.context);
}

int Run()
{
	Start();
	// Turns on wireframe, keep commented if not wanted.


	while (!glfwWindowShouldClose(window))
		Update();

	End();

	return error;
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);

	SCR_WIDTH = width;
	SCR_HEIGHT = height;
}

double lastXPos = 50.0, lastYPos = 50.0;
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstFrameForMouse)
	{
		lastXPos = xPos;
		lastYPos = yPos;

		firstFrameForMouse = false;
		return;
	}

	player.camera.yaw += ((float)xPos - lastXPos) * sensitivity;
	player.camera.pitch += (lastYPos - (float)yPos) * sensitivity;

	if (player.camera.pitch > 89.0f)
		player.camera.pitch = 89.0f;
	if (player.camera.pitch < -89.0f)
		player.camera.pitch = -89.0f;

	float cosOfYaw = cosf(glm_rad(player.camera.yaw));
	float sinOfYaw = sinf(glm_rad(player.camera.yaw));
	float cosOfPitch = cosf(glm_rad(player.camera.pitch));
	float sinOfPitch = sinf(glm_rad(player.camera.pitch));

	player.camera.forward[0] = sinOfYaw * cosOfPitch;
	player.camera.forward[1] = sinOfPitch;
	player.camera.forward[2] = cosOfYaw * cosOfPitch;

	player.camera.right[0] = cosOfYaw;
	player.camera.right[2] = -sinOfYaw;

	glm_normalize(player.camera.forward);

	glm_cross(player.camera.forward, player.camera.right, player.camera.up);


	lastXPos = xPos;
	lastYPos = yPos;

	//printf("(%f, %f)\n", player.camera.yaw, player.camera.pitch);
}

void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	chunkRenderDist += (float)yoffset * scrollSensitivity;
	chunkRenderDist = max(chunkRenderDist, 0.75f);
}

bool RLastFrame, spaceLastFrame;
float timeLastActivatedJump = -256.0f;
void processInput(float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, 1);

	bool RThisFrame;
	if ((RThisFrame = glfwGetKey(window, GLFW_KEY_R)) == GLFW_PRESS && RThisFrame != RLastFrame)
	{
		restart = true;
	}
	RLastFrame = RThisFrame;

	bool spaceThisFrame;
	bool isGrappling = false;

	if ((spaceThisFrame = (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)))
	{
		if (player.data.nearWall/*player.data.grounded*/ && !player.data.grappling && !spaceLastFrame)
		{
			vec3 vel;
			glm_vec3_scale(player.camera.forward, player.data.jumpForce, vel);
			glm_vec3_add(player.collider.velocity, vel, player.collider.velocity);
		}
		else
		{
			// Do stuff like double jumping here. =)
		}
	}
	else if (player.data.nearWall)
	{
		vec3 scaledVel;
		glm_vec3_scale(player.collider.velocity, player.data.slowDown, scaledVel);
		glm_vec3_lerp(player.collider.velocity, scaledVel, deltaTime, player.collider.velocity);
	}
	else
	{
	}
	spaceLastFrame = spaceThisFrame;

	vec3 camMovement;

	glm_vec3_zero(camMovement);

	/*if (isGrappling)
	{
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camMovement[0] -= 1;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camMovement[0] += 1;

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
			camMovement[1] -= 1;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
			camMovement[1] += 1;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camMovement[2] -= 1;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camMovement[2] += 1;


		glm_vec3_scale(camMovement, deltaTime * player.data.grappleMoveMul * _fnlInvSqrt(camMovement[0] * camMovement[0] + camMovement[1] * camMovement[1] + camMovement[2] * camMovement[2]), camMovement);
	}
	else
	{*/
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS && player.data.nearWall)
			camMovement[0] -= 1;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS && player.data.nearWall)
			camMovement[0] += 1;

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS && player.data.nearWall)
			camMovement[1] -= 1;
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS && player.data.nearWall)
			camMovement[1] += 1;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && player.data.nearWall)
			camMovement[2] -= 1;
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && player.data.nearWall)
			camMovement[2] += 1;


		glm_vec3_scale(camMovement, deltaTime * _fnlInvSqrt(camMovement[0] * camMovement[0] + camMovement[1] * camMovement[1] + camMovement[2] * camMovement[2]), camMovement);
	//}

	

	spaceLastFrame = spaceThisFrame;

	if (!player.data.nearWall) player.collider.velocity[1] -= player.data.gravity * deltaTime;

	MovePlayer(&player, camMovement);

	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
	{
		player.collider.pos[0] = 0.0f;
		player.collider.pos[1] = 100.0f;
		player.collider.pos[2] = 0.0f;
	}
}

void MultiplayerInit()
{

}