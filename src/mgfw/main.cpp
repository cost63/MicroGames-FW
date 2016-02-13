#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"
#include "system/Window.h"
#include "system/ErrorLog.h"
#include "graphics/Renderer.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VertexArray.h"
#include "graphics/Sprite.h"
#include "graphics/CircleShape.h"

#include "graphics/Image.h"
#include "graphics/Texture.h"
#include "graphics/Font.h"
#include "graphics/Text.h"

#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"

using namespace mg;

int main(int argc, char** argv) {
    if(!init()) {
        priv::logError("MGFW initialization failed");
        return 1;
    }

    const Vec2i windowSize = Vec2i(1024, 768);
    Window window(windowSize,"Framework test", Window::Resizeable);

//    const Vec2f offset = { 50, 50 };
//    const Vec2f size = { 100, 100 };
//
//    VertexArray s;
//    s.type = PrimitiveType::Quads;
//    s.resize(8);
//    s[0] = Vertex({0, 0}, Color::Red);
//    s[1] = Vertex({size.x, 0}, Color::Green);
//    s[2] = Vertex(size, Color::Blue);
//    s[3] = Vertex({0, size.y}, Color::White);
//
//    s[4] = Vertex(offset + Vec2f(0, 0), Color::Red);
//    s[5] = Vertex(offset + Vec2f(size.x, 0), Color::Green);
//    s[6] = Vertex(offset + size, Color::Blue);
//    s[7] = Vertex(offset + Vec2f(0, size.y), Color::White);

//    Font f;
//    f.loadFromFile("arial.ttf", 30);
//
    Texture tex;
    tex.loadFromFile("test.png");

    Sprite s;
    s.setTexture(&tex);
    s.setSize(windowSize);
    s.setCenter(windowSize / 2);

//    VertexArray s;
//    s.type = PrimitiveType::Quads;
//    s.resize(4);
//    s[0].pos = Vec2f(0, 0);
//    s[1].pos = Vec2f(600, 0);
//    s[2].pos = Vec2f(600, 450);
//    s[3].pos = Vec2f(0, 450);
//
//    s[0].texCoord = Vec2f(0, 0);
//    s[1].texCoord = Vec2f(tex.getSize().w, 0);
//    s[2].texCoord = Vec2f(tex.getSize().w, tex.getSize().h);
//    s[3].texCoord = Vec2f(0, tex.getSize().h);
//
//    Transformable t;
//    t.setSize(tex.getSize());
//
//    RenderStates a;
//    a.texture = &tex;
//    a.transform = t.getMatrix();

//    Text s;
//    s.setFont(&f);
//    s.setString("Test string");
//    s.setCharSize(100);

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
