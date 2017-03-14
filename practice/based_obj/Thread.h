 ///
 /// @file    Thread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-18 11:06:13
 ///
 
#ifndef _MY_THREAD_H_
#define _MY_THREAD_H_
#include "Noncopyable.h"
#include <functional>

namespace wd
{

class Thread : Noncopyable
{
public:
	typedef std::function<void()> ThreadCallback;
	Thread(ThreadCallback cb);
	~Thread();

	void start();
	void join();

	static void * threadFunc(void *);

private:
	pthread_t _pthId;
	bool _isRunning;
	ThreadCallback _cb;
};


}//end of namespace wd

#endif 

