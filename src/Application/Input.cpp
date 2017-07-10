/** Copyright (c) Lazu Ioan-Bogdan */

#include "Input.h"

/*
#include "SDL.h"
#include "SDL_keyboard.h"

// Utils
#include "Map.h"
#include "Profiler.h"
#include "String.h"
#include "PlatformLog.h"
*/

BEGIN_TRITRANIUM

/*
#define TAG TXT("EN_KEY_LISTENER")

enInputListener::enInputListener() 
{
	key = new TMap<int, bool>();
	memset(&mouse, 0, sizeof(enMouseInput));
}

enInputListener::~enInputListener()
{
	delete key;
}

void enInputListener::Initialize()
{
	LogDebug(TXT("Initializing key listener!\n"));
}

bool enInputListener::InputPressed(enInput key) const
{
	int enumKey = static_cast<int>(key);
	return this->key->Get(enumKey);
}

const enMouseInput &enInputListener::MouseState() const
{
	return mouse;
}

static bool PolledUpRemove = false;
static bool PolledDownRemove = false;

void enInputListener::ProcessEvents()
{
	SDL_Event event;

	if (PolledUpRemove)
	{
		PolledUpRemove = false;

		int enumKey = static_cast<int>(EN_MOUSE_SCROLL_UP);
		bool value = false;

		key->Put(enumKey, value);
	}

	if (PolledDownRemove)
	{
		PolledDownRemove = false;

		int enumKey = static_cast<int>(EN_MOUSE_SCROLL_DOWN);
		bool value = false;

		key->Put(enumKey, value);
	}
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type) {
		case SDL_MOUSEMOTION:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
		case SDL_MOUSEWHEEL:			
			HandleMouse(event);
			break;
		case SDL_KEYDOWN:	
			HandleKeyDown(event.key.keysym);
			break;
		case SDL_KEYUP:
			HandleKeyUp(event.key.keysym);
			break;
		case SDL_QUIT:
			Quit(0);
			break;
		}
	}
}

void enInputListener::HandleMouse(const SDL_Event &event)
{	
	bool modify = true;
	bool value = true;
	int enumKey = 0;

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		SDL_GetMouseState(&mouse.currentX, &mouse.currentY);

		if (mouse.leftDragging)
		{
			mouse.leftPressed = 0;
			mouse.deltaLeftX = mouse.downLeftX - mouse.currentX;
			mouse.deltaLeftY = mouse.downLeftY - mouse.currentY;
		}
		else
			mouse.deltaLeftX = mouse.deltaLeftY = 0;

		if (mouse.rightDragging)
		{
			mouse.rightPressed = 0;
			mouse.deltaRightX = mouse.downRightX - mouse.currentX;
			mouse.deltaRightY = mouse.downRightY - mouse.currentY;
		}
		else
			mouse.deltaRightX = mouse.deltaRightY = 0;
			
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED)
		{
			mouse.leftPressed = 1;
			mouse.leftDragging = 1;

			SDL_GetMouseState(&mouse.downLeftX, &mouse.downLeftY);
			
			enumKey = static_cast<int>(EN_MOUSE_LEFT);
		}
		else if (event.button.button == SDL_BUTTON_RIGHT && event.button.state == SDL_PRESSED)
		{
			mouse.rightPressed = 1;
			mouse.rightDragging = 1;

			SDL_GetMouseState(&mouse.downRightX, &mouse.downRightY);

			enumKey = static_cast<int>(EN_MOUSE_RIGHT);
		}		
		else
			modify = false;

		if (modify)
			key->Put(enumKey, value);

		break;
	case SDL_MOUSEBUTTONUP:
		if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_RELEASED)
		{
			mouse.leftPressed = 0;
			mouse.leftDragging = 0;
			mouse.deltaLeftX = mouse.deltaLeftY = 0;

			enumKey = static_cast<int>(EN_MOUSE_LEFT);
		}
		else if (event.button.button == SDL_BUTTON_RIGHT && event.button.state == SDL_RELEASED)
		{
			mouse.rightPressed = 0;
			mouse.rightDragging = 0;
			mouse.deltaRightX = mouse.deltaRightY = 0;

			enumKey = static_cast<int>(EN_MOUSE_RIGHT);
		}				
		else
			modify = false;

		if (modify)
			key->Put(enumKey, value);

		break;
	case SDL_MOUSEWHEEL:
		if (event.wheel.y > 0) 
		{
			enumKey = static_cast<int>(EN_MOUSE_SCROLL_UP);
			PolledUpRemove = true;
		}
		else if (event.wheel.y < 0)
		{
			enumKey = static_cast<int>(EN_MOUSE_SCROLL_DOWN);
			PolledDownRemove = true;
		}

		key->Put(enumKey, value);
		break;
	}
}

void enInputListener::HandleKeyDown(const SDL_Keysym &keysym)
{	
	if (keysym.sym == SDLK_ESCAPE)
		Quit(0);

	// Map the key
	enInput in = Map(keysym.sym);

	int enumKey = static_cast<int>(in);
	bool val = true;

	// Set the bool in the map as true
	key->Put(enumKey, val);
}

void enInputListener::HandleKeyUp(const SDL_Keysym &keysym)
{	
	// Map the key
	enInput in = Map(keysym.sym);
	
	int enumKey = static_cast<int>(in);
	bool val = false;

	// Set the bool in the map as false
	key->Put(enumKey, val);
}

enInput enInputListener::Map(const int &key)
{
	switch (key)
	{
	case SDLK_UP: return EN_KEY_UP;
	case SDLK_DOWN: return EN_KEY_DOWN;
	case SDLK_LEFT: return EN_KEY_LEFT;
	case SDLK_RIGHT: return EN_KEY_RIGHT;

	case SDLK_1: return EN_KEY_1;
	case SDLK_2: return EN_KEY_2;
	case SDLK_3: return EN_KEY_3;
	case SDLK_4: return EN_KEY_4;
	case SDLK_5: return EN_KEY_5;

	case SDLK_q: return EN_KEY_Q;
	case SDLK_e: return EN_KEY_E;
	case SDLK_w: return EN_KEY_W;
	case SDLK_a: return EN_KEY_A;
	case SDLK_s: return EN_KEY_S;
	case SDLK_d: return EN_KEY_D;
	case SDLK_f: return EN_KEY_F;
	case SDLK_SPACE: return EN_KEY_SPACE;

	case SDLK_EQUALS: return EN_KEY_EQUAL;
	case SDLK_MINUS: return EN_KEY_MINUS;

	// Default
	default: return EN_UNDEFINED;
	}
}

void enInputListener::Quit(int code)
{
	SDL_Quit();
	exit(code);
}
*/

END_TRITRANIUM