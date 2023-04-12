#include "Window.h"
#include "Log.h"

bool Window::initialize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0)
	{
		Log::error(LogCategory::Video, "Unable ot initialize SDL");
		return false;
	}
	SDLWindow = SDL_CreateWindow("Brick Breaker", 800, 600, width, height, 0);
	if (!SDLWindow)
	{
		Log::error(LogCategory::System, "Failed to create window");
		return false;
	}
	return true;
}

void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}
