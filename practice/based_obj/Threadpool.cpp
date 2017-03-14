 ///
 /// @file    Threadpool.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-19 10:23:27
 ///
 
#include "Threadpool.h"
#include "Thread.h"
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
		Thread * pThread = new Thread(
				std::bind(&Threadpool::threadFunc,this));
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

void Threadpool::addTask(Task ptask)
{
	_buf.push(ptask);
}

Threadpool::Task Threadpool::getTask()
{
	return _buf.pop();
}


void Threadpool::threadFunc()
{
	while(!_isExit)
	{
		Task ptask = getTask();
		if(ptask)
			ptask();
	}
}


}// end of namespace wd


