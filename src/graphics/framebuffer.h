#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class FrameBuffer
{
public:
    FrameBuffer(int width, int height);
    ~FrameBuffer();

    GLuint get_frame_texture();

    void bind() const;
    void unbind() const;

private:
    GLuint fbo;
    GLuint texture;
    GLuint rbo;
};