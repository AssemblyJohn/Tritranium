/** Copyright (c) Lazu Ioan-Bogdan */

#include "Application.h"

/*

void enApplication::Initialize()
{
	SDL_Window *window;

	// Initialize memory
	// InitializeMemory();
	// Initialize the object graph
	YClass::StaticInit();
	// Initialize config data
	enConfig::Initialize();
	// Initialize video mode
	//InitializeVideo(&window);
	// Initialize OpenGL
	InitializeGL();
	// Initialize game
	game.Initialize();
}

int enApplication::Start()
{
	/*
	while (1) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		game->Step();

		SDL_GL_SwapWindow(window);

#ifdef EN_DEBUG
		static unsigned int ticks = 0;
		if (SDL_GetTicks() - ticks > 5000) {
			ticks = SDL_GetTicks();
			printf("=====\nTime last step: %f s\nTime process work: %f s\nTime world step: %f s\nTime render step: %f s\n=====\n",
				game->TimeStep(), game->TimeProcessWork(), game->TimeWorldStep(), game->TimeRenderStep());
		}
#endif
	}
	

	return 0;
}

*/