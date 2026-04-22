#include "Framebuffer.hpp"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

/*
    We have to attach at least one buffer (color, depth or stencil buffer).
    There should be at least one color attachment.
    All attachments should be complete as well (reserved memory).
    Each buffer should have the same number of samples.
*/

Framebuffer::Framebuffer()
{
    glCreateFramebuffers(1, &mFbo);

}