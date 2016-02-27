/*
    Please, keep in mind that this file is just for testing
    purposes and is not related to the actual framework
*/

#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"

#include "../math/PhysicWorld.h"
#include "../math/RectShapePhysic.h"
#include "../math/CircleShapePhysic.h"

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

    PhysicWorld world(Vec2f(0.0, 10.0));

    CircleShapePhysic player;
    player.setRadius(0.5);
    player.setPos(2.0, 2.0);
    player.setRigidType(PhysicType::Dynamic);
    player.setColor(Color::Red);
    player.setDensity(1.0);
//    player.getVertices()[1].color = Color::Yellow;
//    player.getVertices()[2].color = Color::Yellow;
    player.getVertices()[0].color = Color::Transparent;

    RectShapePhysic box;
    box.setSize(2, 2);
    box.setPos(4, (float)windowSize.h / 50 - 3.2);
    box.setColor(Color::Red);
    box.setRigidType(PhysicType::Static);

    RectShapePhysic ground;
    ground.setSize((float)windowSize.w / 50, 1);
    ground.setPos(0, (float)windowSize.h / 50 - 1.2);
    ground.setColor(Color(100, 100, 200, 255));
    ground.setRigidType(PhysicType::Static);

    world.addPhysicShape(player);
    world.addPhysicShape(box);
    world.addPhysicShape(ground);

//    CircleShapePhysic circle;
//    circle.setRadius(2.0);
//    circle.setPos(3.0, 3.0);
//    circle.setSagmentCount(64);
//    circle.setColor(Color::Yellow);

//    world.addPhysicShape(circle);

    RectShape shape;
    shape.setSize(1.0, 1.0);
    shape.setPos(2.0, 2.0);
    shape.setColor(Color::Orange);

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
                    player.ApplyLinearImpulseCenter(Vec2f(0.0, -10.0));
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
                    player.applyForceCenter(Vec2f(-15.0, 0.0));
                }
                if(keys[SDL_SCANCODE_D]) {
                    player.applyForceCenter(Vec2f(15.0, 0.0));
                }
                if(keys[SDL_SCANCODE_W]) {
                    player.applyForceCenter(Vec2f(0.0, -15.0));
                }
                if(keys[SDL_SCANCODE_S]) {
                    player.applyForceCenter(Vec2f(0.0, 15.0));
                }
                if(keys[SDL_SCANCODE_Q]) {
                    player.applyTorque(-20.0);
                }
                if(keys[SDL_SCANCODE_E]) {
                    player.applyTorque(20.0);
                }
                world.update(Time::Seconds(timeStep));
            }
        }

        window.clear();

        // Render ...
        window.draw(shape);
        window.draw(player);
        window.draw(box);
        window.draw(ground);
//        window.draw(circle);
        window.draw(fpsText);

        window.display();
    }

    close();

	return 0;
}
