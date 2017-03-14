 ///
 /// @file    Task.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2016-03-19 10:52:12
 ///
 
#ifndef __MY_TASK_H_
#define __MY_TASK_H_
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <iostream>

using std::cout;
using std::endl;

namespace wd
{
class Task
{
public:
	virtual void process()=0;
};

class MyTask : public Task
{
public:
	void process()
	{
		srand(time(NULL));
		int num = rand() % 100;
		cout << "produce num:" << num << endl;
		sleep(1);
	}
};


}// end of namespace wd


#endif
