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

    const Vec2i windowSize = Vec2i(600, 450);
    Window window(windowSize,"Framework test", Window::Resizeable);

    Font f;
    f.loadFromFile("arial.ttf", 30);
//    f.getGlyph('M', 30);
//    f.getGlyph('i', 30);
//    f.getGlyph('c', 30);
//    f.getGlyph('r', 30);
//    f.getGlyph('o', 30);
//    f.getGlyph(' ', 30);
//    f.getGlyph('G', 30);
//    f.getGlyph('a', 30);
//    f.getGlyph('m', 30);
//    f.getGlyph('e', 30);
//    f.getGlyph('s', 30);

//    Texture& tex = f.getTex();

//    Sprite s;
//    s.setTexture(&tex);
//    s.setSize(440, 440);
//    s.setCenter(windowSize / 2);

    Text s;
    s.setFont(&f);
    s.setString("Test string");

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
