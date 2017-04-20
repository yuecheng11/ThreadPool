#include "Thread.h"  

using namespace std;

void CTask::SetData(void * data)  
{  
	m_ptrData = data;  
}  
  
vector<CTask*> CThreadPool::m_vecTaskList;		   //\u4efb\u52a1\u5217\u8868  
bool CThreadPool::shutdown = false;  
	  
pthread_mutex_t CThreadPool::m_pthreadMutex = PTHREAD_MUTEX_INITIALIZER;   
pthread_cond_t CThreadPool::m_pthreadCond = PTHREAD_COND_INITIALIZER;  
  
/** 
 * \u7ebf\u7a0b\u6c60\u7ba1\u7406\u7c7b\u6784\u9020\u51fd\u6570 
 */  
CThreadPool::CThreadPool(int threadNum)  
{  
	this->m_iThreadNum = threadNum;  
	cout << "I will create " << threadNum << " threads" << endl;  
	Create();  
}  
  
/** 
 * \u7ebf\u7a0b\u56de\u8c03\u51fd\u6570 
 */  
void* CThreadPool::ThreadFunc(void* threadData)  
{  
	pthread_t tid = pthread_self();  
	while (1)  
	{  
		pthread_mutex_lock(&m_pthreadMutex);  
		while (m_vecTaskList.size() == 0 && !shutdown)	
		{  
			pthread_cond_wait(&m_pthreadCond, &m_pthreadMutex);  
		}  
		  
		if (shutdown)  
		{  
			pthread_mutex_unlock(&m_pthreadMutex);	
			cout<<"thread "<<pthread_self()<<" will exit/n"<<endl;  
			pthread_exit(NULL);   
		}  
		  
		cout<<"tid"<<tid<<" run/n"<<endl;  
		vector<CTask*>::iterator iter = m_vecTaskList.begin();	
		  
		/** 
		* \u53d6\u51fa\u4e00\u4e2a\u4efb\u52a1\u5e76\u5904\u7406\u4e4b 
		*/	
		CTask* task = *iter;  
		if (iter != m_vecTaskList.end())  
		{  
			task = *iter;  
			m_vecTaskList.erase(iter);	
		}  
		  
		pthread_mutex_unlock(&m_pthreadMutex);	
		  
		task->Run(); /** \u6267\u884c\u4efb\u52a1 */  
		cout<<"tid: "<<tid<<" idle/n"<<endl;	
	}  
	return (void*)0;  
}  
  
/** 
 * \u5f80\u4efb\u52a1\u961f\u5217\u91cc\u8fb9\u6dfb\u52a0\u4efb\u52a1\u5e76\u53d1\u51fa\u7ebf\u7a0b\u540c\u6b65\u4fe1\u53f7 
 */  
int CThreadPool::AddTask(CTask *task)  
{  
	pthread_mutex_lock(&m_pthreadMutex);  
	this->m_vecTaskList.push_back(task);  
	pthread_mutex_unlock(&m_pthreadMutex);	
	pthread_cond_signal(&m_pthreadCond);  
	return 0;  
}  
  
/** 
 * \u521b\u5efa\u7ebf\u7a0b 
 */  
int CThreadPool::Create()  
{  
	pthread_id = (pthread_t*)malloc(sizeof(pthread_t) * m_iThreadNum);	
	for(int i = 0; i < m_iThreadNum; i++)  
	{  
		pthread_create(&pthread_id[i], NULL, ThreadFunc, NULL);  
	}  
	return 0;  
}  
  
/** 
 * \u505c\u6b62\u6240\u6709\u7ebf\u7a0b 
 */  
int CThreadPool::StopAll()	
{  
	/** \u907f\u514d\u91cd\u590d\u8c03\u7528 */  
	if (shutdown)  
	{  
		return -1;	  
	}  
	printf("Now I will end all threads!!/n");  
	/** \u5524\u9192\u6240\u6709\u7b49\u5f85\u7ebf\u7a0b\uff0c\u7ebf\u7a0b\u6c60\u8981\u9500\u6bc1\u4e86 */  
	shutdown = true;  
	pthread_cond_broadcast(&m_pthreadCond);  
	  
	/** \u963b\u585e\u7b49\u5f85\u7ebf\u7a0b\u9000\u51fa\uff0c\u5426\u5219\u5c31\u6210\u50f5\u5c38\u4e86 */  
	for (int i = 0; i < m_iThreadNum; i++)	
	{  
		pthread_join(pthread_id[i], NULL);	  
	}  
	  
	free(pthread_id);  
	pthread_id = NULL;	
	  
	/** \u9500\u6bc1\u6761\u4ef6\u53d8\u91cf\u548c\u4e92\u65a5\u4f53 */  
	pthread_mutex_destroy(&m_pthreadMutex);  
	pthread_cond_destroy(&m_pthreadCond);  
	  
	return 0;  
}  
  
/** 
 * \u83b7\u53d6\u5f53\u524d\u961f\u5217\u4e2d\u4efb\u52a1\u6570 
 */  
int CThreadPool::getTaskSize()	
{  
	return m_vecTaskList.size();	  
}  

