 ///
 /// @file    test_pc.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-18 15:54:42
 ///
 
#include "Threadpool.h"
#include "Task.h"
#include <unistd.h>


int main(void)
{
	wd::Task *ptask = new wd::MyTask;

	wd::Threadpool threadpool(4, 10);
	threadpool.start();
	int cnt = 20;
	while(cnt--)
	{
		threadpool.addTask(ptask);
		//sleep(1);
	}
	threadpool.stop();

	//sleep(20);

	return 0;
}
