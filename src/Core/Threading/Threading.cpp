/** Copyright (c) Lazu Ioan-Bogdan */

#include "Threading.h"











/* Old code
enSimpleMutex::enSimpleMutex(const char *name)
{		
	handle = CreateMutexA(NULL, NULL, name);
}

void enSimpleMutex::Unlock()
{
	ReleaseMutex(handle);	
}

void enSimpleMutex::Lock()
{
	WaitForSingleObject(handle, INFINITE);
}
*/


/**
 * Begin enThread


// 64 kb should do...
size_t enThread::STACK_SIZE = 1024 * 64;

enThread::enThread() : stopped(false), started(false) { }
enThread::~enThread() { }

DWORD WINAPI callback(void *arg)
{
	enThread *thrd = (enThread *)arg;
	thrd->Callback();

	return 0;
}

void enThread::Start()
{
	started = true;

	CreateThread(NULL, enThread::STACK_SIZE, callback, this, NULL, NULL);
}

void enThread::Stop()
{
	stopped = true;
}

bool enThread::Stopped() 
{
	return stopped;
}

bool enThread::Started()
{
	return started;
}

/**
 * End enThread
 */