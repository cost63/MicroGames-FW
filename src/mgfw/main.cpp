#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"
#include "system/Window.h"
#include "system/ErrorLog.h"
#include "graphics/Renderer.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VertexArray.h"

using namespace mg;

int main(int argc, char** argv)
{
    if(!init())
    {
        PRINT_ERROR("MGFW initialization failed");
        return 1;
    }

    Window window(Vec2i(500, 400),"Something", Window::Shown);
    Renderer::setupBuffers();
    Renderer r;

    ShaderProgram s;
    s.loadFromFile("data/shaders/default.vert", "data/shaders/default.frag");

    VertexArray quad(PrimitiveType::PType_Quads, 6);
    quad[0].pos = {-0.5, 0.5};
    quad[1].pos = { 0.5, 0.5};
    quad[2].pos = { 0.5,-0.5};
    quad[3].pos = { 0.5,-0.5};
    quad[4].pos = {-0.5,-0.5};
    quad[5].pos = {-0.5, 0.5};

    bool running = true;
    while(running)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                running = false;
            }
            else if(event.type == SDL_KEYUP)
            {
                if(event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
            }
        }

        window.clear();

        RenderStates states;
        states.shader = &s;

        // Render ...
        r.draw(quad, states);

        r.render();

        window.display();
    }

    close();

	return 0;
}
