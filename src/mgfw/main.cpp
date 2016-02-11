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

    Image image;
    image.create(Vec2u(300, 300), Color::Yellow);

    Image image2;
    image2.create(Vec2u(200, 200), Color::Red);

    Image image3;
    image3.create(Vec2u(100, 100), Color::Orange);

    image.copyPixels(image2.getPixels(), image2.getSize(), Vec2u(50, 50));
    image.copyPixels(image3.getPixels(), image3.getSize(), Vec2u(100, 100));

    Texture tex;
    tex.copyFromImage(image);

    Sprite s;
    s.setTexture(&tex);
    s.setSize(300, 300);
    s.setCenter(windowSize / 2);

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
