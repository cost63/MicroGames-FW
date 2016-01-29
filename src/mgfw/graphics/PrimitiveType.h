#pragma once

namespace mg {

enum class PrimitiveType {
    Points          = 0,
    Lines           = 1,
    LineLoop        = 2,
    LineStrip       = 3,
    Triangles       = 4,
    TriangleStrip   = 5,
    TriangleFan     = 6,
    Quads           = 7,
    QuadStrip       = 8,
    Polygon         = 9,
};

} // namespace mg
