#pragma once

#include "../math/Matrix4.h"

namespace mg
{

class ShaderProgram;

// TODO(Smeky) Add transform and texture once they are implemented
struct RenderStates
{
    ShaderProgram* shader = nullptr;
    Matrix4 transform;
};

} // namespace mg
