/*
    Please, keep in mind that this file is just for testing
    purposes and is not related to the actual framework
*/

#include <SDL2/SDL.h>
#include <iostream>

#include "MGFW.h"

#include "Box2D/Box2D.h"

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

    /* START - Box2D */

    b2Vec2 gravity(0.0, 10.0);
    b2World world(gravity);

    b2BodyDef groundDef;
    groundDef.position.Set(0.0, 25.0);

    b2Body* ground = world.CreateBody(&groundDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0, 10.0);

    ground->CreateFixture(&groundBox, 0.0);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(5.0, 4.0);

    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0, 1.0);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0;
    fixtureDef.friction = 0.3;

    body->CreateFixture(&fixtureDef);

    /* END - Box2D */

    const float timeStep    = 1.0 / 60.0;
    const int velocityIter  = 6;
    const int positionIter  = 2;

    float timeAccumulator   = 0.0;

    RectShape shape;
    shape.setSize(50, 50);
    shape.setPos(0, 200);
    shape.setColor(Color::Orange);

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

                world.Step(timeStep, velocityIter, positionIter);

                // Update with FPS as delta
            }

            b2Vec2 pos = body->GetPosition();
            shape.setPos(pos.x * 50, pos.y * 50);
        }

        window.clear();

        // Render ...
        window.draw(shape);
        window.draw(fpsText);

        window.display();
    }

    close();

	return 0;
}
