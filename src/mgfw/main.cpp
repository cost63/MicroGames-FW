#include <SDL.h>
#include <iostream>


int main(int argc, char** argv)
{
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
	}
	else
	{
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_SHOWN);

		if(window == nullptr)
		{
			std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
		}
		else
		{
			screenSurface = SDL_GetWindowSurface(window);

			bool running = true;
			while(running)
            {
                SDL_Event event;

                while(SDL_PollEvent(&event))
                {
                    if(event.type == SDL_QUIT)
                    {
                        running = false;
                    }
                    else if(event.type == SDL_KEYUP)
                    {
                        if(event.key.keysym.sym == SDLK_ESCAPE)
                        {
                            running = false;
                        }
                    }
                }

                SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 255, 255, 255));
                SDL_UpdateWindowSurface(window);
            }
		}
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
