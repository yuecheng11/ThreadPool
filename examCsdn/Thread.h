#ifndef __THREAD_H	
#define __THREAD_H	
  
#include <vector>  
#include <string>  
#include <pthread.h>  
#include <iostream>  
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;  
  
/** 
 * \u6267\u884c\u4efb\u52a1\u7684\u7c7b\uff0c\u8bbe\u7f6e\u4efb\u52a1\u6570\u636e\u5e76\u6267\u884c 
 */  
class CTask  
{  
protected:	
	string m_strTaskName;  /** \u4efb\u52a1\u7684\u540d\u79f0 */  
	void* m_ptrData;	   /** \u8981\u6267\u884c\u7684\u4efb\u52a1\u7684\u5177\u4f53\u6570\u636e */  
public:  
	CTask(){}  
	CTask(string taskName)	
	{  
		m_strTaskName = taskName;  
		m_ptrData = NULL;  
	}  
	virtual int Run()= 0;  
	void SetData(void* data);	 /** \u8bbe\u7f6e\u4efb\u52a1\u6570\u636e */  
  
public:  
	virtual ~CTask(){}	
};	
  
/** 
 * \u7ebf\u7a0b\u6c60\u7ba1\u7406\u7c7b\u7684\u5b9e\u73b0 
 */  
class CThreadPool  
{  
private:  
	static	vector<CTask*> m_vecTaskList;	  /** \u4efb\u52a1\u5217\u8868 */  
	static	bool shutdown;					  /** \u7ebf\u7a0b\u9000\u51fa\u6807\u5fd7 */			
	int 	m_iThreadNum;					  /** \u7ebf\u7a0b\u6c60\u4e2d\u542f\u52a8\u7684\u7ebf\u7a0b\u6570 */  
	pthread_t	*pthread_id;  
	  
	static pthread_mutex_t m_pthreadMutex;	  /** \u7ebf\u7a0b\u540c\u6b65\u9501 */  
	static pthread_cond_t m_pthreadCond;	  /** \u7ebf\u7a0b\u540c\u6b65\u7684\u6761\u4ef6\u53d8\u91cf */  
  
protected:	
	static void* ThreadFunc(void * threadData); /** \u65b0\u7ebf\u7a0b\u7684\u7ebf\u7a0b\u56de\u8c03\u51fd\u6570 */  
	static int MoveToIdle(pthread_t tid);		/** \u7ebf\u7a0b\u6267\u884c\u7ed3\u675f\u540e\uff0c\u628a\u81ea\u5df1\u653e\u5165\u5230\u7a7a\u95f2\u7ebf\u7a0b\u4e2d */  
	static int MoveToBusy(pthread_t tid);		/** \u79fb\u5165\u5230\u5fd9\u788c\u7ebf\u7a0b\u4e2d\u53bb */  
	  
	int Create();		   /** \u521b\u5efa\u7ebf\u7a0b\u6c60\u4e2d\u7684\u7ebf\u7a0b */  
  
public:  
	CThreadPool(int threadNum = 10);  
	int AddTask(CTask *task);	   /** \u628a\u4efb\u52a1\u6dfb\u52a0\u5230\u4efb\u52a1\u961f\u5217\u4e2d */  
	int StopAll();				   /** \u4f7f\u7ebf\u7a0b\u6c60\u4e2d\u7684\u7ebf\u7a0b\u9000\u51fa */	
	int getTaskSize();			   /** \u83b7\u53d6\u5f53\u524d\u4efb\u52a1\u961f\u5217\u4e2d\u7684\u4efb\u52a1\u6570 */  
};	
  
#endif	

