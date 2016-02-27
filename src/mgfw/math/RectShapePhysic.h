#pragma once

#include "../math/ShapePhysic.h"

namespace mg {

class RectShapePhysic : public ShapePhysic {
public:
    RectShapePhysic();

    void addToWorld(PhysicWorld& world) override;

private:
    void onSizeChange(const Vec2f& prevSize) override;

};

} // namespace mg
