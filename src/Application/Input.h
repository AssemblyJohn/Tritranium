/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef EN_KEY_LISTENER_H
#define EN_KEY_LISTENER_H

#include "Platform\Platform.h"

/*
// #include "ReferenceCounting.h"

struct SDL_Keysym;
union SDL_Event;

BEGIN_TRITRANIUM

// Should receive a boolean for these if that key is pressed. Should be enought for the moment...
typedef enum enInput
{
	EN_KEY_UP,
	EN_KEY_DOWN,
	EN_KEY_LEFT,
	EN_KEY_RIGHT,

	EN_KEY_1,
	EN_KEY_2,
	EN_KEY_3,
	EN_KEY_4,
	EN_KEY_5,

	EN_KEY_Q,
	EN_KEY_E,
	EN_KEY_W,
	EN_KEY_A,
	EN_KEY_S,
	EN_KEY_D,
	EN_KEY_F,
	EN_KEY_SPACE,

	EN_KEY_EQUAL,
	EN_KEY_MINUS,

	// These can also be used, independently of the enMouseInput struct
	EN_MOUSE_LEFT,
	EN_MOUSE_RIGHT,
	EN_MOUSE_SCROLL_UP,
	EN_MOUSE_SCROLL_DOWN,

	EN_UNDEFINED
} enInput;

typedef struct enMouseInput {
	// Will be true only one step. After that it is switched to false. If we need drag data use leftDraggin or rightDragging
	unsigned int leftPressed	: 1;
	// Same as above.
	unsigned int rightPressed	: 1;

	// If the mouse is dragged with the left key
	unsigned int leftDragging	: 1;
	// If the mouse is dragged with the right key
	unsigned int rightDragging	: 1;

	// -1 down, 0 still, 1 up
	int wheel					: 2;

	// Where the mouse was pressed (with the left key)
	int downLeftX;
	int downLeftY;

	// Same but for right
	int downRightX;
	int downRightY;

	// Where the mouse is now
	int currentX;
	int currentY;

	// How much did the mouse travel after a press
	int deltaLeftX;
	int deltaLeftY;

	// How much did the mouse travel after a press
	int deltaRightX;
	int deltaRightY;
} enMouseInput;

template<class K, class V> class TMap;

class enInputListener
{
public:
	enInputListener();
	~enInputListener();
	void Initialize();

	// To be called in the main loop
	void ProcessEvents();

	// If a key is pressed
	bool InputPressed(enInput) const;
	// Mouse state
	const enMouseInput &MouseState() const;
private:
	void HandleMouse(const SDL_Event &);
	void HandleKeyDown(const SDL_Keysym &);
	void HandleKeyUp(const SDL_Keysym &);
	enInput Map(const int &);
	void Quit(int);

	TMap<int, bool> *key;
	enMouseInput mouse;
};

END_TRITRANIUM
*/

#endif