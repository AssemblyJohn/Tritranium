#include "Engine.h"

BEGIN_TRITRANIUM

PEngine::PEngine() :
	mPaused(false)
{

}

PEngine::~PEngine()
{

}

void PEngine::PreTick()
{
	// TODO: any other stuff
	mTimer.Mark();
}

/**
* Engine's main ticking loop.
*/
void PEngine::Tick() {
	if (mPaused) {
		LogWarning(TXT("Paused but we tick!"));

		// ThreadUtils.sleep(20);
		return;
	}

	BeginTime();

	// 1. Tick the world
	mTempTimer.Mark();

	mWorld.BeginTick();

	{
		mWorld.TickWorld();
		mWorld.RenderTick();
	}

	mTime.mTimeTick = mTempTimer.Elapsed();

	// 1. Post the draws
	mTempTimer.Mark();

	//mRenderer.render();

	mTime.mTimeRender = mTempTimer.Elapsed();

	// Process the private working queue. If it's posted data, or coroutines or anything else
	mTempTimer.Mark();

	//processCoroutines();
	//processWork();

	// Finish the tick. All the deletes are done after the tick and after processing coroutines
	mWorld.FinishTick();

	mTime.mTimeWork = mTempTimer.Elapsed();

	EndTime();
}

void PEngine::BeginTime() 
{
	// How much elapsed
	float elapsed = mTimer.Elapsed();
	// Mark the timer
	mTimer.Mark();

	// Time full, including pauses, and not scaling this time
	float elapsedFull = mTimerFull.Elapsed();
	mTimerFull.Mark();

	// Clamp the elapsed time between 1000 and 2.5 fps so we don't get awfully wrong values when ticking entities
	// 1 ms and    400 ms
	//  ||          ||
	// 1000 fps    2.5 fps
	// elapsed = XMath.Clamp(elapsed, 1f, 400f);

	// Set set times
	mTime.mDeltaTime = elapsed;
	mTime.mTotalTime += elapsed;
	mTime.mTotalTimeFull += elapsedFull;
}

void PEngine::EndTime() 
{
	// Increment frame count
	mTime.mFrameCount++;

	// Debug data
	LogDebug("Game tick time data: %s", mTime.ToString().c_str());
	//if (Log.DEBUG_MODE && mTime.mFrameCount % 25 == 0) {
	//Log.d(TAG, "Game tick time data: " + mTime.toString());
	//}
}

END_TRITRANIUM