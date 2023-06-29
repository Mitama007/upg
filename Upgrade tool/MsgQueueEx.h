#ifndef MSGQUEUEEX_H_
#define MSGQUEUEEX_H_

#include "inc_inner.h"
#include "PSX_Semaphore.h"
#include "PSX_Mutex.h"
#include <deque>

using namespace std;

/*********************************************************************
名	称：CMsgQueueEx
功  	能：通用的消息队列模块，使用互斥锁保护读写过程被其它线程中断			
*********************************************************************/
template<typename T>
class CMsgQueueEx
{
private:
	deque<T> 	 	m_deque;		//数据载体	
	CPSX_Mutex		m_objLock;		//读写保护
	unsigned long	m_ulDataCount;
	enum {EN_LOCK_TIMEOUT = 1000};
private:
	void PushHeadDeque (T tNewElement);
	void PushTailDeque (T tNewElement);
	void PopHeadDeque (T &tElement);
	void PopTailDeque (T &tElement);
public:
	bool Init ();
	void Uninit ();	
	bool PushHead (T tNewElement);	
	bool PushTail (T tNewElement);	
	bool PopHead (T &tElement);	
	bool PopTail (T &tElement);
	bool PushDeque2Head (deque<T> deq);
	bool PushDeque2Tail (deque<T> deq);
	bool PopHead2Deque (deque<T> &deq, unsigned long ulCount);
	bool PopTail2Deque (deque<T> &deq, unsigned long ulCount);
	unsigned long RemoveAll ();
	unsigned long Count ();	
public:
	CMsgQueueEx ();
	~CMsgQueueEx ();
};

template<typename T>
CMsgQueueEx<T>::CMsgQueueEx ()
{
	m_ulDataCount = 0;
}
	
template<typename T>
CMsgQueueEx<T>::~CMsgQueueEx ()
{
	Uninit ();
}

/*********************************************************************
名  	称：Init
功	能：初始化消息队列，此函数将初始化消息队列数据到达的信号量，
				及消息队列读写保护的互斥锁		
参  	数：
 		无
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::Init ()
{	
	m_ulDataCount = 0;
	
	//初始化deque 读写互斥锁
	return (0 == m_objLock.Init());
}

/*********************************************************************
名  	称：Uninit
功	能：反初始化消息队列，此函数将反初始化通知消息队列数据到达通知
		的信号量，及消息队列读写保护的互斥锁
参  	数：
		无
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::Uninit ()
{
	//反初始化读写锁
	m_objLock.Destroy();	
}

/*********************************************************************
名  	称：PushHeadDeque
功	能：设置数据到Deque头部
参  	数：
 		tNewElement[IN]
 				要插入头部的数据，此数据必须是本模板类实例化时的
				数据类型
返回	值：	无			
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::PushHeadDeque (T tNewElement)
{
	//增加数据到deque头部
	m_deque.push_front (tNewElement);
	
	m_ulDataCount++;
}

/*********************************************************************
名  	称：PushTailDeque
功	能：设置数据到Deque尾部
参  	数：
 		tNewElement[IN]
 				要插入头部的数据，此数据必须是本模板类实例化时的
				数据类型
返回	值：	无	
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::PushTailDeque (T tNewElement)
{
	//增加数据到deque头部
	m_deque.push_back (tNewElement);
	
	m_ulDataCount++;
}

/*********************************************************************
名  	称：PopHeadDeque
功	能：获取消息队列头部的数据
参  	数：
 		tNewElement[OUT]
 				填充数据的变量，此数据是本模板类实例化时的数据类型
返回	值：	无		
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::PopHeadDeque (T &tElement)
{
	//获取deque中头部数据
	tElement = m_deque.front ();
	
	//删除deque的头部数据
	m_deque.pop_front ();
	m_ulDataCount--;
}

/*********************************************************************
名  	称：PopTailDeque
功	能：获取消息队列头部的数据
参  	数：
 		tNewElement[OUT]
 				填充数据的变量，此数据是本模板类实例化时的数据类型
返回	值：	无	
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::PopTailDeque (T &tElement)
{
	//获取deque中头部数据
	tElement = m_deque.back ();
	
	//删除deque的头部数据
	m_deque.pop_back ();
	m_ulDataCount--;
}	

/*********************************************************************
名  	称：PushHead
功	能：设置数据到消息队列头部
参  	数：
 		tNewElement[IN]
 				要插入头部的数据，此数据必须是本模板类实例化时的
				数据类型
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PushHead (T tNewElement)
{
	//锁定deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		PushHeadDeque (tNewElement);
		
		//deque解锁
		m_objLock.Unlock();
		return 1;
	}
	return 0;
}

/*********************************************************************
名  	称：PushTail
功	能：设置数据到消息队列尾部
参  	数：
 		tNewElement[IN]
 				要插入尾部的数据，此队列中数据必须是本模板类实例化时的
				数据类型
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PushTail (T tNewElement)
{
	//锁定deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		PushTailDeque (tNewElement);

		//deque解锁
		m_objLock.Unlock();		
		
		return 1;
	}
	return 0;
}

/*********************************************************************
名  	称：PopHead
功	能：获取消息队列头部的数据
参  	数：
 		tNewElement[OUT]
 				填充数据的变量，此数据是本模板类实例化时的数据类型
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PopHead (T &tElement)
{
	bool bRet = 0;
	
	//锁定deque
	if (m_ulDataCount > 0 && 0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{	
		if (0 < m_ulDataCount)
		{
			PopHeadDeque (tElement);		
			
			bRet = 1;
		}
		//deque解锁
		m_objLock.Unlock();
	}	
	return bRet;
}


/*********************************************************************
名  	称：PopTail
功	能：获取消息队列尾部的数据
参  	数：
 		tNewElement[OUT]
 				填充数据的变量，此数据是本模板类实例化时的数据类型
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PopTail (T &tElement)
{
	bool bRet = 0;
		
	//锁定deque
	if (m_ulDataCount > 0 && 0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{	
		if (0 < m_ulDataCount)
		{
			PopTailDeque (tElement);
					
			bRet = 1;
		}
		//deque解锁
		m_objLock.Unlock();
	}	
	return bRet;
}

/*********************************************************************
名  	称：PushDeque2Head
功	能：设置deque全部数据到消息队列头部
参  	数：
 		deque[IN]
 				要插入头部的数据，此数据必须是本模板类实例化时的
				数据类型
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PushDeque2Head (deque<T> deq)
{
	//锁定deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		//增加数据到deque头部

		unsigned long ulSize = deq.size ();
		while (ulSize-- > 0)
		{			
			PushHeadDeque (deq.back ());
			deq.pop_back ();
		}
		
		//deque解锁
		m_objLock.Unlock();
		return 1;
	}
	return 0;
}

/*********************************************************************
名  	称：PushDeque2Tail
功	能：设置deque全部数据到消息队列尾部
参  	数：
 		deque[IN]
 				要插入头部的数据，此队列中数据必须是本模板类实例化时的
				数据类型
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PushDeque2Tail (deque<T> deq)
{
	//锁定deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		//增加数据到deque尾部
		unsigned long ulSize = deq.size ();
		while (ulSize-- > 0)
		{
			PushTailDeque (deq.front ());
			deq.pop_front ();
		}
		
		//deque解锁
		m_objLock.Unlock();
		return 1;
	}
	return 0;
}

/*********************************************************************
名  	称：PopHead2Deque
功	能：获取消息队列头部的数据到队列
参  	数：
 		deque[OUT]
 				填充数据的队列，此数据是本模板类实例化时的数据类型
 		ulCount[OUT]
 				要Pop的数据总数，此数据不能大于本模块保存的最大数据总数
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PopHead2Deque (deque<T> &deq, unsigned long ulCount)
{
	bool bRet = 0;

	if (0 < ulCount && m_ulDataCount >= ulCount)
	{
	 	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	 	{
                if (m_ulDataCount >= ulCount)
                {
                    while (ulCount--)
                    {
                        T tElement;
                        
                        PopHeadDeque (tElement);
                        deq.push_back (tElement);
                    }
                    bRet = 1;					
                }
	 			//deque解锁
	 			m_objLock.Unlock();		
	 			
		}	
	}
	return bRet;
}

/*********************************************************************
名  	称：PopTail2Deque
功	能：获取消息队列尾部的数据到队列
参  	数：
 		deque[OUT]
 				填充数据的队列，此数据是本模板类实例化时的数据类型
 		ulCount[OUT]
 				要Pop的数据总数，此数据不能大于本模块保存的最大数据总数
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PopTail2Deque (deque<T> &deq, unsigned long ulCount)
{
	bool bRet = 0;

	if (0 < ulCount && m_ulDataCount >= ulCount)
	{
	 	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	 	{
                if (m_ulDataCount >= ulCount)
                {
                    while (ulCount--)
                    {
                        T tElement;
                        
                        PopTailDeque (tElement);
                        deq.push_front (tElement);
                    }
                    bRet = 1;					
                }
	 			
	 			//deque解锁
	 			m_objLock.Unlock();			 			
		}			
	}
	return bRet;
}

/*********************************************************************
名  	称：RemoveAll
功	能：清除消息队列中的所有数据
参  	数：
 		无
返回	值：		
		无
*********************************************************************/
template<typename T>
unsigned long CMsgQueueEx<T>::RemoveAll ()
{
	unsigned long ulCount = 0;
	
	//锁定deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{				
		unsigned long ulSize = m_ulDataCount;
		while (ulSize-- > 0)
		{			
			T Val;
			
			//遍历队列中所有数据进行删除
			PopHeadDeque (Val);
			
			ulCount++;
		}
		m_objLock.Unlock ();
	}
	return ulCount;
}

/*********************************************************************
名  	称：Count
功	能：获取消息队列中数据总个数
参  	数：
 		无
返回	值：		
		返回队列中数据总个数信息				
*********************************************************************/
template<typename T>
unsigned long CMsgQueueEx<T>::Count ()
{
	unsigned long ulSize = 0;
	
	//锁定deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		ulSize = m_ulDataCount;
		//deque解锁
		m_objLock.Unlock();
	}
	return ulSize;
}






/*********************************************************************
名  	称：CNotifyQueue
功 	能：在MsgQueueEx(数据队列)的基础上增加异步通知功能				
*********************************************************************/
template<typename T>
class CNotifyQueue 
{
private:
	CPSX_Semaphore	m_objSem;		//数据到达通知
	CMsgQueueEx<T>	m_objQueue;
public:
	virtual bool Init ();
	virtual void Uninit ();
	virtual bool PushHead (T tNewElement);
	virtual bool PushTail (T tNewElement); 
	virtual unsigned long RemoveAll ();
	virtual unsigned long Count ();
	bool PopHead (T &tElement, unsigned long ulMs = 0);
	bool PopTail (T &tElement, unsigned long ulMs = 0);
public:
	CNotifyQueue ();
	virtual ~CNotifyQueue ();
};

template<typename T>
CNotifyQueue<T>::CNotifyQueue ()
{
}

template<typename T>
CNotifyQueue<T>::~CNotifyQueue ()
{
	Uninit ();
}

/*********************************************************************
名  	称：Init
功	能：初始化消息队列，此函数将反初始化通知消息队列数据到达
		的信号量
参  	数：
 		无
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CNotifyQueue<T>::Init ()
{	
	if (m_objQueue.Init ())
	{
		return (0 == m_objSem.Init(0, 0));
	}
	return 0;
}

/*********************************************************************
名  	称：Uninit
功	能：反初始化消息队列，此函数将反初始化通知消息队列数据到达
		的信号量
参  	数：
		无
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
void CNotifyQueue<T>::Uninit ()
{
	//反初始化队列
	m_objQueue.Uninit ();

	//反初始化信号量
	m_objSem.Destroy();
}

/*********************************************************************
名  	称：PushHead
功	能：设置数据到消息队列尾部
参  	数：
 		tNewElement[IN]
 				要插入尾部的数据，此数据必须是本模板类实例化时的
				数据类型
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CNotifyQueue<T>::PushHead (T tNewElement)
{	
	if (m_objQueue.PushHead (tNewElement))
	{
		return (0 == m_objSem.Post());
	}
	return 0;	
}

/*********************************************************************
名  	称：PushTail
功	能：设置数据到消息队列尾部
参  	数：
 		tNewElement[IN]
 				要插入尾部的数据，此数据必须是本模板类实例化时的
				数据类型
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CNotifyQueue<T>::PushTail (T tNewElement)
{
	if (m_objQueue.PushTail (tNewElement))
	{		
		return (0 == m_objSem.Post());
	}
	return 0;	
}

/*********************************************************************
名  	称：PopTail
功	能：获取消息队列尾部的数据
参  	数：
 		tNewElement[OUT]
 				填充数据的变量，此数据是本模板类实例化时的数据类型
 		ulMs[OUT]
 				Pop数据时最大等待时间
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CNotifyQueue<T>::PopHead (T &tElement, unsigned long ulMs /* = 0*/)
{	
	if (0 == m_objSem.Wait (ulMs))
	{
		return m_objQueue.PopHead (tElement);
	}
	return 0;
}

/*********************************************************************
名  	称：PopTail
功	能：获取消息队列尾部的数据
参  	数：
 		tNewElement[OUT]
 				填充数据的变量，此数据是本模板类实例化时的数据类型
		ulMs[OUT]
 				Pop数据时最大等待时间
返回	值：		
		1	成功
		0	失败				
*********************************************************************/
template<typename T>
bool CNotifyQueue<T>::PopTail (T &tElement, unsigned long ulMs /* = 0*/)
{
	if (0 == m_objSem.Wait (ulMs))
	{
		return m_objQueue.PopTail (tElement);
	}
	return 0;
}

/*********************************************************************
名  	称：Count
功	能：获取消息队列中数据总个数
参  	数：
 		无
返回	值：		
		返回队列中数据总个数信息				
*********************************************************************/
template<typename T>
unsigned long CNotifyQueue<T>::Count ()
{
	return m_objQueue.Count();
}

/*********************************************************************
名  	称：RemoveAll
功	能：清除消息队列中的所有数据
参  	数：
 		无
返回	值：		
		无
*********************************************************************/
template<typename T>
unsigned long CNotifyQueue<T>::RemoveAll ()
{
	unsigned long ulRet   = 0;
	unsigned long ulCount = 0;
	
	ulCount = m_objQueue.RemoveAll ();
	
	ulRet = ulCount;
	while (ulCount--)
	{
		m_objSem.Wait(0);
	}
	return ulRet;
}	

#endif /*MSGQUEUEEX_H_*/
