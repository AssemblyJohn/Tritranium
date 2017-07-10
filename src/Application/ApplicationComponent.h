#ifndef __TRITRANIUM_APP_COMPONENT__
#define __TRITRANIUM_APP_COMPONENT__

#include "Platform\Platform.h"

BEGIN_TRITRANIUM

/**
 * Will dispatch this through the native bindings
 */
class PApplicationComponent
{
public:
	/** Called after creating the engine. Called on the UI thread. */
	virtual void OnAppInit() = 0;

	/**
	* The only method that is called on the render thread,  so we can init the render thread data.
	* Note that we don't have a 'render exit', all data is released automatically.
	*
	* All subsequent calls to 'onResume', 'onePause', 'onExit', 'onResChange' ... etc.. must only
	* be called if we were initialized. Else we might have an undefined state. Check inside engine
	* that we are initialized. If we are not, take no action.
	*
	* Called on the render thread.
	*/
	virtual void onAppRenderInit() = 0;

	/** Called on the UI thread */
	virtual void onAppResume() = 0;

	/** Called on the UI thread */
	virtual void onAppPause() = 0;

	/**
	* Called on the render thread. Might not be called on android. It will auto remove all the vid data there.
	*/
	virtual void OnAppRenderRelease() = 0;

	/** Called on the UI thread */
	virtual void OnAppExit() = 0;

	/** Called when the window changes resolution. Called on the render thread */
	virtual void OnAppResolutionChange(uint32 width, uint32 height) = 0;

	// Should add routines for handling input and handling the tick
};

END_TRITRANIUM

#endif