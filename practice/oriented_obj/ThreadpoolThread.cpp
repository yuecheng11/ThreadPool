 ///
 /// @file    ThreadpoolThread.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-19 10:30:04
 ///
 
#include "ThreadpoolThread.h"
#include "Threadpool.h"

namespace wd
{
ThreadpoolThread::ThreadpoolThread(Threadpool & threadpool)
: _threadpool(threadpool)
{}


void ThreadpoolThread::run()
{
	_threadpool.threadFunc();
}

}// end of namespace wd
