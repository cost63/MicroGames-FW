#pragma once

namespace mg
{

struct RenderEntity
{
    RenderStates states;
    PrimitiveType type;
    uint32_t vertexIndex = 0;
    uint32_t vertexCount = 0;
};

} // namespace mg
