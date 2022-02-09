#pragma once
#include "List.h"

/*float* data = {
	{ 0.0f, 1.0f, 2.0f, 3.0f, 4.0f },
	{ 5.0f, 6.0f, 7.0f, 8.0f, 9.0f }
};
int widthOfData = 5;
int heightOfData = 2;
int sizeOfData = sizeof(data);

void TestMultithread()
{
	float* result = malloc(sizeOfData);
	// Setup OpenCL.
	cl_device_id device;
	cl_platform_id platform = NULL;
	cl_uint ret_num_devices;
	cl_uint ret_num_platforms;
	cl_int ret = clGetPlatformIDs(1, &platform, &ret_num_platforms);
	ret = clGetDeviceIDs(platform, CL_DEVICE_TYPE_ALL, 1, &device, &ret_num_devices);
	cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &ret);
	printf("3, ");
	cl_command_queue queue = clCreateCommandQueueWithProperties(context, device, (cl_queue_properties)0, NULL);
	printf("4, ");

	// Define out kernal. It just calculates the sine of the input data.
	const char* source = {
		"kernel void calcSin(global float* data, global float* result) {\n"
		"	int id = get_global_id(0);\n"
		"	result[id] = sin(data[id]);\n"
		"}\n"
	};

	// Create memory buffers on the device for each vector.
	cl_mem a_mem_obj = clCreateBuffer(context, CL_MEM_READ_ONLY,
		sizeOfData, NULL, &ret);
	cl_mem b_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
		sizeOfData, NULL, &ret);

	// Copy the lists A and B to their respective memory buffers.
	ret = clEnqueueWriteBuffer(queue, a_mem_obj, CL_TRUE, 0,
		sizeOfData, data, 0, NULL, NULL);
	ret = clEnqueueWriteBuffer(queue, b_mem_obj, CL_TRUE, 0,
		sizeOfData, result, 0, NULL, NULL);

	// Compile the kernal.
	cl_program program = clCreateProgramWithSource(context, 1, (const char**)&source, NULL, NULL);
	printf("5, ");
	clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	printf("6, ");
	cl_kernel kernel = clCreateKernel(program, "calcSin", NULL);
	printf("7, ");

	// Set the arguments of the kernel
	ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), (void*)&a_mem_obj);
	ret = clSetKernelArg(kernel, 1, sizeof(cl_mem), (void*)&b_mem_obj);
	printf("10, ");
	size_t global_dimensions[] = { widthOfData, heightOfData, 0 };
	printf("11, ");
	clEnqueueNDRangeKernel(queue, kernel, 1, NULL, global_dimensions, NULL, 0, NULL, NULL);
	printf("12, ");

	// Read back the results.
    // Read the memory buffer C on the device to the local variable C
	float* C = (float*)malloc(sizeOfData);
	ret = clEnqueueReadBuffer(queue, b_mem_obj, CL_TRUE, 0,
		sizeOfData, C, 0, NULL, NULL);
	printf("13!\n");

	// Wait for everything to finish.
	clFinish(queue);

	for (int i = 0; i < widthOfData * heightOfData; i++)
		printf("%f, ", C[i]);
}*/