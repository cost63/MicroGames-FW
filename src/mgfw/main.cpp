#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"
#include "system/Window.h"
#include "system/ErrorLog.h"
#include "graphics/Renderer.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VertexArray.h"

using namespace mg;

int main(int argc, char** argv) {
    if(!init()) {
        PRINT_ERROR("MGFW initialization failed");
        return 1;
    }

    Window window(Vec2i(500, 400),"Something", Window::Shown);

    ShaderProgram s;
    s.loadFromFile("src/mgfw/graphics/shaders/default.vert", "src/mgfw/graphics/shaders/default.frag");

    RenderStates states;
    states.shader = &s;

    VertexArray quad(PrimitiveType::LineStrip, 4);
    quad[0].pos = {150.0, 100};
    quad[1].pos = {350.0, 100};
    quad[2].pos = {350.0, 300};
    quad[3].pos = {150.0, 300};
    quad[0].color = Color::Red;
    quad[1].color = Color::Green;
    quad[2].color = Color::Blue;
    quad[3].color = Color::White;

    bool running = true;
    while(running) {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }
            else if(event.type == SDL_KEYUP) {
                if(event.key.keysym.sym == SDLK_ESCAPE) {
                    running = false;
                }
            }
        }

        window.clear();

        // Render ...
        window.draw(quad, states);

        window.display();
    }

    close();

	return 0;
}
