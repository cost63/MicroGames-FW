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
    Polygon         = 7,
    Quads           = 8,
    QuadStrip       = 9,
};

} // namespace mg
