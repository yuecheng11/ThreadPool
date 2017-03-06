 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-19 10:23:27
 ///
 
#include "Threadpool.h"
#include "ThreadpoolThread.h"
#include "Task.h"
#include <unistd.h>

namespace wd
{
Threadpool::Threadpool(int threadNum, int buffSize)
: _threadNum(threadNum)
, _bufSize(buffSize)
, _buf(_bufSize)
, _isExit(false)
{
	_vecThreads.reserve(_threadNum);
}

Threadpool::~Threadpool()
{
	if(!_isExit)
	{
		stop();
	}
}

void Threadpool::start()
{
	for(int idx = 0; idx != _threadNum; ++idx)
	{
		Thread * pThread = new ThreadpoolThread(*this);
		_vecThreads.push_back(pThread);
	}
	vector<Thread *>::iterator it = _vecThreads.begin();
	for(; it != _vecThreads.end(); ++it)
	{
		(*it)->start();
	}
}

void Threadpool::stop()
{
	if(!_isExit)
	{
		while(!_buf.empty())
		{
			sleep(1);
		}
		_isExit = true;
		vector<Thread *>::iterator it;
		for(it = _vecThreads.begin();
			it != _vecThreads.end();
			++it)
		{
			(*it)->join();
			delete (*it);
		}
		_vecThreads.clear();
	}
}

void Threadpool::addTask(Task * ptask)
{
	_buf.push(ptask);
}

Task * Threadpool::getTask()
{
	return _buf.pop();
}


void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task * ptask = getTask();
		if(ptask)
			ptask->process();
	}
}


}// end of namespace wd


