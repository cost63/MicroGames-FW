#include "Renderer.h"

#include <GL/glew.h>

#include "../graphics/Vertex.h"

namespace mg
{

Renderer::Renderer()
{}

void Renderer::draw()
{
    const Vertex test[] = {
        { Vec2f(0, 0.5), Color::Red, Vec2f(0, 0) },
        { Vec2f(0.5, -0.5), Color::Green, Vec2f(0, 0) },
        { Vec2f(-0.5, -0.5), Color::Blue, Vec2f(0, 0) },
    };

    glBegin(GL_TRIANGLES);
        for( int i = 0; i < 3; i++ )
        {
            glColor3ubv(&test[i].color[0]);
            glVertex2fv(&test[i].pos[0]);
        }
    glEnd();
}

} // namespace mg
