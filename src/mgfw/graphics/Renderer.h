#pragma once

#include <ShaderProgram.h>

namespace mg
{

class Renderer
{
public:
    Renderer();

    static void setupBuffers();

    void draw(ShaderProgram& shader);

private:
    static uint32_t s_quadVAO;

};

} // namespace mg
