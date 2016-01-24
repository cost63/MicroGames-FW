#pragma once

namespace mg
{

class ShaderProgram;

// TODO(Smeky) Add transform and texture once they are implemented
struct RenderStates
{
    ShaderProgram* shader = nullptr;
};

} // namespace mg
