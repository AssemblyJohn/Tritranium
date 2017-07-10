#pragma once

#include "Core\Core.h"
#include "Platform\PlatformVideo.h"
#include "Platform\PlatformAssertion.h"

#include "World.h"

BEGIN_TRITRANIUM

class PAssetManager;

struct PWindowView
{
	uint32 mWidth;
	uint32 mHeight;

	float mAspectRatio;

	const PVec2 GetResolution() const
	{
		return PVec2((float)mWidth, (float)mHeight);
	}
};

// TODO: move this somwhere else
class PEngineTime {
public:
	// TODO: fix everything to use float seconds, we don't need milli any more.
	/** Time since last tick in seconds */
	const float DeltaTime() const { return (mDeltaTime); }
	/** Total tick time in seconds */
	const float TotalTime() const { return (mTotalTime); } 
	/** Total time including time paused. Use when we need elapsed time of some sort. */
	float TotalTimeFull() { return (mTotalTimeFull); }
	/** Frame count */
	uint64 FrameCount() { return mFrameCount; }
	/** If the engine is paused, aka in background. */
	bool IsPaused() { return mPaused; }
	/** If the engine has been exited or exiting */
	bool IsExited() { return mExiting; }

	PEngineTime() :
		mTotalTime(0.0f),
		mDeltaTime(0.0f),
		mTimeTick(0.0f),
		mTimeWork(0.0f),
		mTimeRender(0.0f),
		mTimeInput(0.0f),
		mFrameCount(0L)
	{ }

private:
	friend class PEngine;

private:
	// Other private data
	float mTimeTick;
	float mTimeWork;
	float mTimeRender;
	float mTimeInput;

	float mTotalTimeFull;
	/** Total game time */
	float mTotalTime;
	/** Time since last game tick */
	float mDeltaTime;
	/** Frame count */
	uint64 mFrameCount;
	/** If we are paused */
	bool mPaused = false;
	/** If we are exited or exiting */
	bool mExiting = false;

	
public:
	PString ToString() {
		PString string = "";

		string = string + "EngineTime {" +
			"mTimeWaitRender(render scene)=" + mTimeRender +
			", mTimeTick(tick and renderTick)=" + mTimeTick +
			", mDeltaTime=" + mDeltaTime +
			", mTimeWork(coroutines, work)=" + mTimeWork +
			", mTimeInput=" + mTimeInput +
			", mTotalTime=" + mTotalTime +
			", mFrameCount=" + mFrameCount +
		'}';

		return string;
	}	
};

class PEngine
{
public:
	PEngine();
	~PEngine();

public:
	PWorld *GetWorld() 
	{
		return &mWorld;
	}

	PVidCommands *GetVidCommands() 
	{
		return &mVidCommands;
	}

	void CheckGame() { CHK(0); }

	void SetViewData(const PWindowView &view)
	{
		mView = view;
		mView.mAspectRatio = (float)mView.mWidth / mView.mHeight;
	}

	const PWindowView &GetViewData() const
	{
		return mView;
	}

	const PEngineTime &GetTime() const
	{
		return mTime;
	}

	/*
	const PAssetManager &GetAssetManager() const
	{
		return mAssetManager;
	}
	*/

	/*	
	public VidUtils getVidUtils() {
		return mVidUtils;
	}

	public AndroidInput getInput() {
		return mAndroidInput;
	}

	public EngineTime getTime() {
		return mTime;
	}

	

	public GameThread getGameThread() {
		return mGameThread;
	}

	public SceneRenderer getSceneRenderer() {
		return mRenderer;
	}
	*/

	/**
	 * Preparations before the tick
	 */
	void PreTick();

	/**
	* Engine's main ticking loop.
	*/
	void Tick();

private:
	void BeginTime();
	void EndTime();

private:
	// friend class PEngineLauncher;

private: /* View data */
	PWindowView mView;

private:
	// General engine data. Initialized by our launcher
	// GameThread mGameThread;
	PVidCommands mVidCommands;
	// AndroidInput mAndroidInput;
	
	// Owned world and renderer for the world's scene.
	PWorld mWorld;
	// SceneRenderer mRenderer;

	PAssetManager *mAssetManager;

	// Engine's module manager and asset manager
	// ModuleManager mModuleManager;
	// AssetManager mAssetManager;

private:
	// Timing
	PEngineTime mTime;
	PMarkTimer mTempTimer;
	PMarkTimer mTimer;
	PMarkTimer mTimerFull;

	bool mPaused;
};

END_TRITRANIUM