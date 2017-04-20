#include "Thread.h"  


using namespace std;

class CMyTask: public CTask  
{  
public:  
    CMyTask(){}  
      
    inline int Run()  
    {  
        printf("%s/n", (char*)this->m_ptrData);  
        sleep(10);  
        return 0;  
    }  
};  
  
int main()  
{  
    CMyTask taskObj;  
      
    char szTmp[] = "this is the first thread running";  
    taskObj.SetData((void*)szTmp);  
    CThreadPool threadPool(10);  
      
    for(int i = 0; i < 20; i++)  
    {  
        threadPool.AddTask(&taskObj);  
    }  
      
    while(1)  
    {  
       cout<<"there are still "<<threadPool.getTaskSize()<<" tasks need to handle"<<endl;  
        if (threadPool.getTaskSize() == 0)  
        {  
            if (threadPool.StopAll() == -1)  
            {     
                cout<<"Now I will exit from main/n"<<endl;  
                exit(0);  
            }  
        }  
        sleep(2);  
    }  
      
    return 0;  
}  

