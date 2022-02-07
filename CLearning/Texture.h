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