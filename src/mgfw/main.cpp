/*
    Please, keep in mind that this file is just for testing
    purposes and is not related to the actual framework
*/

#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"

#include "../math/PhysicWorld.h"
#include "../math/PhysicRect.h"

using namespace mg;

int main(int argc, char** argv) {
    if(!init()) {
        priv::logError("MGFW initialization failed");
        return 1;
    }

    Font f;
    f.loadFromFile("arial.ttf", 25);

    uint32_t frames = 0;
    Clock clock;
    Clock fpsClock;

    const Vec2i windowSize = Vec2i(768, 768);
    Window window(windowSize,"Framework test", Window::Resizeable);

    Text fpsText;
    fpsText.setFont(&f);
    fpsText.setCharSize(20);
    fpsText.move(5, 5);

    PhysicWorld world(Vec2f(0.0, 5.0));

    PhysicRect box;
    box.setSize(50, 50);
    box.setPos(100, 100);
    box.setColor(Color::Orange);

    world.addPhysicShape(box);

    float timeAccumulator = 0.0;
    const float timeStep  = 1.0 / 60;

    bool running = true;
    while(running) {
        /* FPS related logic */
        {
            frames++;

            if(fpsClock.getElapsedTime().asSeconds() > 0.25) {
                uint32_t fps = (float)frames / fpsClock.restart().asSeconds();
                fpsText.setString("FPS: " + std::to_string(fps));
                frames = 0;
            }
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
                else if(event.key.keysym.sym == SDLK_SPACE) {

                }
            }
            if(event.type == SDL_WINDOWEVENT) {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    window.updateView();
                }
            }
        }

        /* Update loop ( Time step based ) */
        {
            timeAccumulator += clock.restart().asSeconds();

            while(timeAccumulator >= timeStep) {
                timeAccumulator -= timeStep;

                const uint8_t* keys = SDL_GetKeyboardState(nullptr);
                if(keys[SDL_SCANCODE_A]) {
                    box.applyForceCenter(Vec2f(-15.0, 0.0));
                }
                if(keys[SDL_SCANCODE_D]) {
                    box.applyForceCenter(Vec2f(15.0, 0.0));
                }
                if(keys[SDL_SCANCODE_W]) {
                    box.applyForceCenter(Vec2f(0.0, -15.0));
                }
                if(keys[SDL_SCANCODE_S]) {
                    box.applyForceCenter(Vec2f(0.0, 15.0));
                }
//                if(keys[SDL_SCANCODE_Q]) {
//                    box.applyForceCenter(-20.0, true);
//                }
//                if(keys[SDL_SCANCODE_E]) {
//                    box.applyForceCenter(20.0, true);
//                }

                world.update(Time::Seconds(timeStep));
//
//                b2Vec2 pos = box->GetPosition();
//                shape.setPos(pos.x * 50, pos.y * 50);
//                shape.setRotationRad(box->GetAngle());
            }
        }

        window.clear();

        // Render ...
        window.draw(box);
        window.draw(fpsText);

        window.display();
    }

    close();

	return 0;
}
