#pragma once

#include "../graphics/Shape.h"

namespace mg {

class RectShape : public Shape {
public:
    RectShape();

private:
    void onSizeChange(const Vec2f& prevSize) override;

};

} // namespace mg
