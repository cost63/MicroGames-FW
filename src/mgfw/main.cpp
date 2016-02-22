/*
    Please, keep in mind that this file is just for testing
    purposes and is not related to the actual framework
*/

#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"

using namespace mg;

int main(int argc, char** argv) {
    if(!init()) {
        priv::logError("MGFW initialization failed");
        return 1;
    }

    Font f;
    f.loadFromFile("arial.ttf", 25);

    Text fileText;
    fileText.setFont(&f);
    fileText.setCharSize(25);
    fileText.move(5, 50);
    fileText.enableStyle(Text::Italic);

    /* START - Test of File I/O */

    File file;
    file.open("test.txt", File::Read);
    fileText.setString(file.read());
    file.close();

    /* END - Test of File I/O */

    uint32_t frames = 0;
    Clock clock;
    Clock fpsClock;

    const Vec2i windowSize = Vec2i(768, 768);
    Window window(windowSize,"Framework test", Window::Resizeable);

    Text fpsText;
    fpsText.setFont(&f);
    fpsText.setCharSize(20);
    fpsText.move(5, 5);

    RectShape r;
    r.setSize(windowSize / 2);
    r.centerOrigin();
    r.setPos(windowSize / 2);
    r.setColor(Color::Red);

    RectShape r1;
    r1.setSize(windowSize / 3);
    r1.centerOrigin();
    r1.setPos(windowSize / 2);
    r1.setColor(Color::Green);
    r1.setRotation(90 / 3);

    RectShape r2;
    r2.setSize(windowSize / 4);
    r2.centerOrigin();
    r2.setPos(windowSize / 2);
    r2.setColor(Color::Blue);
    r2.setRotation(90 / 3 * 2);

    r.getVertices()[0].color.a = 127;
    r.getVertices()[1].color.a = 127;
    r.getVertices()[2].color.a = 127;
    r.getVertices()[3].color.a = 127;

    Camera cam;
    cam.move(0, -200);

    bool running = true;
    while(running) {
        Time delta = clock.restart();

        /* FPS related logic */
        {
            frames++;

            if(fpsClock.getElapsedTime().asSeconds() > 0.25) {
                uint32_t fps = (float)frames / fpsClock.restart().asSeconds();
                fpsText.setString("FPS: " + std::to_string(fps));
                frames = 0;
            }
        }

        /* Rectangle tests */
        {
            const float ticks = (float)SDL_GetTicks() / 1000;
            const float c = std::cos(ticks);
            const float s = std::sin(ticks);

            const float rotation = delta.asSeconds() * 2000;
            const float scale = (c + 1.5) / 2;
            const uint8_t aCos = (std::abs(c)) * 127;
            const uint8_t aSin = (std::abs(s)) * 127;

            r.rotate(rotation);
            r.setScale(scale);
            r2.getVertices()[0].color.a = aCos;
            r2.getVertices()[1].color.a = aCos;
            r2.getVertices()[2].color.a = aCos;
            r2.getVertices()[3].color.a = aCos;

            r1.rotate(rotation);
            r1.setScale(scale);
            r1.getVertices()[0].color.a = aSin;
            r1.getVertices()[1].color.a = aSin;
            r1.getVertices()[2].color.a = aSin;
            r1.getVertices()[3].color.a = aSin;

            r2.rotate(rotation);
            r2.setScale(scale);

            cam.move(200 * c * delta.asSeconds(), 200 * s * delta.asSeconds());
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

        RenderStates states;
        states.transform = cam.getMatrix();

        // Render ...
        window.draw(r, states);
        window.draw(r1, states);
        window.draw(r2, states);
        window.draw(fpsText);
        window.draw(fileText);

        window.display();
    }

    close();

	return 0;
}
