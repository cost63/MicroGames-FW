#pragma once

#include "..\graphics\RenderStates.h"
#include "..\system\Window.h"

namespace mg {

class Drawable {
public:
    Drawable();

    virtual void draw(Renderer& renderer, RenderStates states) const = 0;

};

} // namespace mg
