 ///
 /// @file    ThreadpoolThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-19 10:27:19
 ///
 
#ifndef _MY_THREADPOOLTHREAD_H_
#define _MY_THREADPOOLTHREAD_H_
#include "Thread.h"
#include <iostream>


namespace wd
{
class Threadpool;
class ThreadpoolThread : public Thread
{
public:
	ThreadpoolThread(Threadpool & threadpool);
	void run();
private:
	Threadpool & _threadpool;
};

}// end of namespace wd

#endif
