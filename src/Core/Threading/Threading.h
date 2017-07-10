/** Copyright (c) Lazu Ioan-Bogdan */

#ifndef __TRITRANIUM_THREAD_H__
#define __TRITRANIUM_THREAD_H__

#include "Platform\Platform.h"
#include "Platform\PlatformAssertion.h"
#include "Platform\PlatformMemory.h"

#include <thread>
#include <mutex>

#undef Yield

BEGIN_TRITRANIUM

/**
 * Scoped lock template. Will lock upon construction and unlock upon deconstruction.
 */
template<class T>
class TScopedLock
{
public:
	TScopedLock(T *lock)
	{
		

		mLock = lock;

		mLock->Lock();
	}

	~TScopedLock()
	{
		mLock->Unlock();
	}

private:
	T *mLock;
};


/**
 * Simple mutex wrapper.
 */
class PMutex
{
public:
	FORCEINLINE void Lock()
	{
		mutex.lock();
	}

	FORCEINLINE void Unlock()
	{
		mutex.unlock();
	}

private:	
	::std::mutex mutex;
};


/**
 * Scoped mutex managing a simple mutex.
 *
 * When it quires a mutex it will 'Lock' and when it gets out of scope it will 'Unlock' the mutex.
 */
class PScopedMutex
{
public:
	PScopedMutex()
	{		
		mMutex.Lock();
	}

	~PScopedMutex()
	{
		mMutex.Unlock();		
	}

private:
	PMutex mMutex;
};

/**
 * Simple runnable with a run callback.
 */
class PRunnable
{
	// Run callback
	virtual void Run() = 0;
};


class PThread
{
public:
	PThread()
	{
		
	}

	~PThread()
	{

	}

private:
		/*
	// Callback operation executed when the thread is started. Do not directly use.
	virtual void Callback() {};	
	// Callback executed when it's added to the game operation queue. Do not directly use.
	virtual void GameCallback(enGame *) {};

	void Start();
	void Stop();

	// If we are started
	bool Started();
	// If we are stopped
	bool Stopped();
	*/

public: /** Static utils */
	static size_t GetCurrentThreadId()
	{
		// TODO: use this for the id same as the string (PString)
		::std::hash<::std::thread::id> hasher;
		
		return hasher(::std::this_thread::get_id());
	}

	static void Yield()
	{
		::std::this_thread::yield();
	}

	static void Sleep(uint32 milli)
	{		
		// ::std::this_thread::sleep_for(::std::chrono::duration<uint32, ::std::chrono::nanoseconds>(milli));
	}

protected:
	volatile bool stopped;
	volatile bool started;
	volatile bool running;

	static size_t STACK_SIZE;

private:
	::std::thread thread;
};

END_TRITRANIUM

#endif