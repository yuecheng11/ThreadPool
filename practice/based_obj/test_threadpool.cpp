 ///
 /// @file    test_pc.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-18 15:54:42
 ///
 
#include "Threadpool.h"
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <functional>

using std::cout;
using std::endl;

struct Task
{
	void process()
	{
		srand(time(NULL));
		int num = rand() % 100;
		cout << "num = " << num << endl;
		//sleep(1);
	}
};

int main(void)
{

	wd::Threadpool threadpool(4, 10);
	threadpool.start();
	int cnt = 20;
	Task task;
	while(cnt--)
	{
		threadpool.addTask(std::bind(&Task::process, &task));
		//sleep(1);
	}
	threadpool.stop();

	//sleep(20);

	return 0;
}
