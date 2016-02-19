/*
    Please, keep in mind that this file is just for testing
    purposes and is not related to the actual framework
*/

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
#include "system/File.h"

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

    /* START - Test of File I/O */

    File file;
    file.open("test.txt", File::Write);
    std::cout << file.read() << std::endl;
    file.close();

    /* END - Test of File I/O */

    uint16_t frames = 0;
    Clock clock;
    Clock fpsClock;

    const Vec2i windowSize = Vec2i(768, 768);
    Window window(windowSize,"Framework test", Window::Resizeable);

    Font f;
    f.loadFromFile("arial.ttf", 30);

    Text fpsText;
    fpsText.setFont(&f);
    fpsText.setCharSize(11);
    fpsText.move(5, 5);
    fpsText.setBoldStyle(true);

    RectShape r;
    r.setSize(windowSize / 4);
    r.setOrigin(windowSize / 8);
    r.setPos(windowSize / 2);
    r.setColor(Color::Orange);

    RectShape y;
    y.setSize(windowSize / 4);
    y.setOrigin(windowSize / 8);
    y.setPos(windowSize / 2);
    y.setColor(Color::Orange);
    y.setRotation(45);

    bool running = true;
    while(running) {
        Time delta = clock.restart();

        /* FPS related logic */
        {
            frames++;

            if(fpsClock.getElapsedTime().asSeconds() > 0.25) {
                uint16_t fps = (float)frames / fpsClock.restart().asSeconds();
                fpsText.setString("FPS: " + std::to_string(fps));
                frames = 0;
            }
        }

        /* Rectangle tests */
        {
            const float ticks = (float)SDL_GetTicks() / 1000;
            const float c = std::cos(ticks);
            const float s = std::sin(ticks);

            r.rotate(delta.asSeconds() * 500);
            r.setScale(c + 1.5, c + 1.5);
            r.getVertices()[0].color.a = (std::abs(c)) * 127;
            r.getVertices()[1].color.a = (std::abs(c)) * 127;
            r.getVertices()[2].color.a = (std::abs(c)) * 127;
            r.getVertices()[3].color.a = (std::abs(c)) * 127;

            y.rotate(delta.asSeconds() * 500);
            y.setScale(c + 1.5, c + 1.5);
            y.getVertices()[0].color.a = (std::abs(s)) * 127;
            y.getVertices()[1].color.a = (std::abs(s)) * 127;
            y.getVertices()[2].color.a = (std::abs(s)) * 127;
            y.getVertices()[3].color.a = (std::abs(s)) * 127;
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
        window.draw(y);
        window.draw(fpsText);

        window.display();
    }

    close();

	return 0;
}
