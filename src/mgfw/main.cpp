#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"
#include "system/Window.h"
#include "system/ErrorLog.h"
#include "graphics/Renderer.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VertexArray.h"
#include "graphics/Sprite.h"

#include "graphics/Texture.h"

using namespace mg;

int main(int argc, char** argv) {
    if(!init()) {
        PRINT_ERROR("MGFW initialization failed");
        return 1;
    }

    Window window(Vec2i(600, 450),"Framework test", Window::Resizeable);

    Texture t;
    t.loadFromFile("test.png");

//    RenderStates states;
//    states.texture = &t;

    Sprite s;
    s.setTexture(&t);
    s.setSize(600, 450);

//    VertexArray quad(PrimitiveType::Quads, 4);
//    quad.normalized = true;

//    quad[0].pos = {150.0, 100.0};
//    quad[1].pos = {350.0, 100.0};
//    quad[2].pos = {350.0, 300.0};
//    quad[3].pos = {150.0, 300.0};

//    quad[0].pos = {-1.0,  1.0};
//    quad[1].pos = { 1.0,  1.0};
//    quad[2].pos = { 1.0, -1.0};
//    quad[3].pos = {-1.0, -1.0};
//
//    quad[0].color = Color::Red;
//    quad[1].color = Color::Green;
//    quad[2].color = Color::Blue;
//    quad[3].color = Color::White;
//
//    quad[0].texCoord = {0, 0};
//    quad[1].texCoord = {1, 0};
//    quad[2].texCoord = {1, 1};
//    quad[3].texCoord = {0, 1};

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
            if(event.type == SDL_WINDOWEVENT) {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    window.updateView();
                }
            }
        }

        window.clear();

        // Render ...
        window.draw(s);

        window.display();
    }

    close();

	return 0;
}
