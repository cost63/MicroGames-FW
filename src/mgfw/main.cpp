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

    const Vec2i windowSize = Vec2i(1024, 768);
    Window window(windowSize,"Framework test", Window::Resizeable);

    Font f;
    f.loadFromFile("arial.ttf", 30);

    Text fpsText;
    fpsText.setFont(&f);
    fpsText.setCharSize(16);
    fpsText.move(5, 5);

    RectShape r;
    r.setSize(windowSize / 2);
    r.setCenter(windowSize / 2);
    r.setColor(Color::Orange);

    bool running = true;
    while(running) {
        frames++;

        if(clock.getElapsedTime().asSeconds() > 0.25) {
            uint16_t fps = (float)frames / clock.restart().asSeconds();
            fpsText.setString("fps: " + std::to_string(fps));
            frames = 0;
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
