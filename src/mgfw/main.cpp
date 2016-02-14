#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"
#include "system/Window.h"
#include "system/ErrorLog.h"
#include "system/Clock.h"
#include "graphics/Renderer.h"
#include "graphics/ShaderProgram.h"
#include "graphics/VertexArray.h"
#include "graphics/Sprite.h"
#include "graphics/CircleShape.h"
#include "graphics/RectShape.h"

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

    uint16_t frames = 0;
    Clock clock;
    Clock fpsClock;

    const Vec2i windowSize = Vec2i(1024, 768);
    Window window(windowSize,"Framework test", Window::Resizeable);

    Font f;
    f.loadFromFile("arial.ttf", 30);

    Text fpsText;
    fpsText.setFont(&f);
    fpsText.setCharSize(16);
    fpsText.move(5, 5);

    RectShape r;
    r.setSize(windowSize / 4);
    r.setOrigin(windowSize / 8);
    r.setPos(windowSize / 2);
    r.setColor(Color::Orange);

    bool running = true;
    while(running) {
        Time delta = clock.restart();

        /* FPS related logic */
        {
            frames++;

            if(fpsClock.getElapsedTime().asSeconds() > 0.25) {
                uint16_t fps = (float)frames / fpsClock.restart().asSeconds();
                fpsText.setString("fps: " + std::to_string(fps));
                frames = 0;
            }
        }

        /* Rectangle tests */
        {
            const float ticks = (float)SDL_GetTicks() / 1000;
            const float c = std::cos(ticks);
            const float s = std::sin(ticks);

            r.rotate(delta.asSeconds() * 20);
            r.setScale(c + 1.5, c + 1.5);
            r.getVertices()[0].color.r = (std::abs(c)) * 255;
            r.getVertices()[1].color.g = (std::abs(-s)) * 255;
            r.getVertices()[2].color.b = (std::abs(s)) * 255;
            r.getVertices()[3].color.a = (std::abs(-c)) * 255;
        }

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
        window.draw(r);
        window.draw(fpsText);

        window.display();
    }

    close();

	return 0;
}
