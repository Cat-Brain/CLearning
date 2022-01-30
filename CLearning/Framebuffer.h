#pragma once
#include "Object.h"

framebuffer screen = { 0, 0, 0 };

void CreateFramebuffer(framebuffer* fb)
{
    glGenFramebuffers(1, &fb->FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, fb->FBO);
    // create a color attachment texture
    glGenTextures(1, &fb->TCB);
    glActiveTexture(GL_TEXTURE0 + fb->TCB);
    glBindTexture(GL_TEXTURE_2D, fb->TCB);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, BUFF_WIDTH, BUFF_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb->TCB, 0);
    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &fb->RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, fb->RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, BUFF_WIDTH, BUFF_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb->RBO); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CreateFramebuffer2(framebuffer2* fb)
{
    glGenFramebuffers(1, &fb->FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, fb->FBO);
    // - position color buffer
    glGenTextures(1, &fb->gPosition);
    glBindTexture(GL_TEXTURE_2D, fb->gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, BUFF_WIDTH, BUFF_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fb->gPosition, 0);

    // - normal color buffer
    glGenTextures(1, &fb->gNormal);
    glBindTexture(GL_TEXTURE_2D, fb->gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, BUFF_WIDTH, BUFF_HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, fb->gNormal, 0);

    // - color + specular color buffer
    glGenTextures(1, &fb->gAlbedoSpec);
    glBindTexture(GL_TEXTURE_2D, fb->gAlbedoSpec);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BUFF_WIDTH, BUFF_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, fb->gAlbedoSpec, 0);

    // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
    glGenRenderbuffers(1, &fb->RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, fb->RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, BUFF_WIDTH, BUFF_HEIGHT); // use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fb->RBO); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void RenderFramebuffer11(framebuffer FB1, framebuffer FB2, Shader shader)
{
    glUseProgram(shader);

    glUniform1i(glGetUniformLocation(shader, "tex"), FB1.TCB);
	glBindFramebuffer(GL_FRAMEBUFFER, FB2.FBO);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glBindTexture(GL_TEXTURE_2D, FB1.TCB);
    
	glBindVertexArray(quad2DVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void RenderFramebuffer21(framebuffer2 FB2, framebuffer FB1, Shader shader)
{
    glUseProgram(shader);

    glUniform1i(glGetUniformLocation(shader, "gPosition"), 0);
    glUniform1i(glGetUniformLocation(shader, "gNormal"), 1);
    glUniform1i(glGetUniformLocation(shader, "gAlbedoSpec"), 2);
    glBindFramebuffer(GL_FRAMEBUFFER, FB1.FBO);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, FB2.gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, FB2.gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, FB2.gAlbedoSpec);

    glBindVertexArray(quad2DVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}