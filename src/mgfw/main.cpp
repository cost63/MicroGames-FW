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
#include "../system/InputManager.h"

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

    Texture tex;
    tex.loadFromFile("test.png");

    Sprite sprite;
    sprite.setTexture(&tex);
//    sprite.setPos(-1, -1);
    sprite.setSize(1);
    sprite.setColor(Color::Red,     0);
    sprite.setColor(Color::Green,   1);
    sprite.setColor(Color::Blue,    2);
    sprite.setColor(Color::White,   3);
    sprite.setUnitMode(UnitMode::Normalized);

//    PhysicWorld world(Vec2f(0.0, 10.0));
//
//    RectShapePhysic player;
//    player.setSize(1.0);
//    player.setPos(2.0, 2.0);
//    player.setRigidType(PhysicType::Dynamic);
//    player.setColor(Color::Red);
//    player.setDensity(1.0);
//    player.getVertices()[0].color = Color::Red;
//    player.getVertices()[1].color = Color::Green;
//    player.getVertices()[2].color = Color::Blue;
//    player.getVertices()[3].color = Color::White;
////    player.getVertices()[0].color = Color::Transparent;
//
//    RectShapePhysic box;
//    box.setSize(2, 2);
//    box.setPos(4, (float)windowSize.h / 50 - 3.2);
//    box.setColor(Color::Red);
//    box.setRigidType(PhysicType::Static);
//
//    RectShapePhysic ground;
//    ground.setSize((float)windowSize.w / 50, 1);
//    ground.setPos(0, (float)windowSize.h / 50 - 1.2);
//    ground.setColor(Color(100, 100, 200, 255));
//    ground.setRigidType(PhysicType::Static);
//
//    world.addPhysicShape(player);
//    world.addPhysicShape(box);
//    world.addPhysicShape(ground);
//
//    VertexArray test;
//    test.resize(5);
//    test.type = PrimitiveType::LineStrip;
//    test[0].pos = Vec2f(1, 1);
//    test[1].pos = Vec2f(3, 2);
//    test[2].pos = Vec2f(3, 4);
//    test[3].pos = Vec2f(2, 3);
//    test[4].pos = Vec2f(2.5, 2);
//    test.setColor(Color::Red);

//    CircleShapePhysic circle;
//    circle.setRadius(2.0);
//    circle.setPos(3.0, 3.0);
//    circle.setSagmentCount(64);
//    circle.setColor(Color::Yellow);

//    world.addPhysicShape(circle);

//    RectShape shape;
//    shape.setSize(1.0, 1.0);
//    shape.setPos(2.0, 2.0);
//    shape.setColor(Color::Orange);

    float timeAccumulator = 0.0;
    const float timeStep  = 1.0 / 60;

    priv::InputManager input;

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

        {
            InputEvent event;

            while(input.pollEvent(event)) {
                if(event.type == InputEvent::WindowClosed) {
                    running = false;
                }
                else if(event.type == InputEvent::KeyUp) {
                    if(event.key.code == Keyboard::Escape) {
                        running = false;
                    }
                    else if(event.key.code == Keyboard::Space) {
//                        player.ApplyLinearImpulseCenter(Vec2f(0.0, -10.0));
                    }
                }
                else if(event.type == InputEvent::WindowResized) {
                    window.updateView();
                }
            }
        }

        /* Update loop ( Time step based ) */
        {
            timeAccumulator += clock.restart().asSeconds();

            while(timeAccumulator >= timeStep) {
                timeAccumulator -= timeStep;
//
//                if(isKeyPressed(Keyboard::A)) {
//                    player.applyForceCenter(Vec2f(-15.0, 0.0));
//                }
//                if(isKeyPressed(Keyboard::D)) {
//                    player.applyForceCenter(Vec2f(15.0, 0.0));
//                }
//                if(isKeyPressed(Keyboard::W)) {
//                    player.applyForceCenter(Vec2f(0.0, -15.0));
//                }
//                if(isKeyPressed(Keyboard::S)) {
//                    player.applyForceCenter(Vec2f(0.0, 15.0));
//                }
//                if(isKeyPressed(Keyboard::Q)) {
//                    player.applyTorque(-20.0);
//                }
//                if(isKeyPressed(Keyboard::E)) {
//                    player.applyTorque(20.0);
//                }

//                world.update(Time::Seconds(timeStep));
            }
        }

        window.clear();


        window.draw(sprite);

        // Render ...
//        window.draw(shape);
//        window.draw(player);
//        window.draw(box);
//        window.draw(ground);
//        window.draw(test);
//        window.draw(circle);
        window.draw(fpsText);

        window.display();
    }

    close();

	return 0;
}
