#pragma once

#include "../math/Matrix4.h"

namespace mg
{

class Texture;
class ShaderProgram;

// TODO(Smeky) Add transform and texture once they are implemented
struct RenderStates
{
    Matrix4 transform;
    Texture* texture = nullptr;
    ShaderProgram* shader = nullptr;
};

} // namespace mg
