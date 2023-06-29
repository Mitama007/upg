#ifndef MSGQUEUEEX_H_
#define MSGQUEUEEX_H_

#include "inc_inner.h"
#include "PSX_Semaphore.h"
#include "PSX_Mutex.h"
#include <deque>

using namespace std;

/*********************************************************************
��	�ƣ�CMsgQueueEx
��  	�ܣ�ͨ�õ���Ϣ����ģ�飬ʹ�û�����������д���̱������߳��ж�			
*********************************************************************/
template<typename T>
class CMsgQueueEx
{
private:
	deque<T> 	 	m_deque;		//��������	
	CPSX_Mutex		m_objLock;		//��д����
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
��  	�ƣ�Init
��	�ܣ���ʼ����Ϣ���У��˺�������ʼ����Ϣ�������ݵ�����ź�����
				����Ϣ���ж�д�����Ļ�����		
��  	����
 		��
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::Init ()
{	
	m_ulDataCount = 0;
	
	//��ʼ��deque ��д������
	return (0 == m_objLock.Init());
}

/*********************************************************************
��  	�ƣ�Uninit
��	�ܣ�����ʼ����Ϣ���У��˺���������ʼ��֪ͨ��Ϣ�������ݵ���֪ͨ
		���ź���������Ϣ���ж�д�����Ļ�����
��  	����
		��
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::Uninit ()
{
	//����ʼ����д��
	m_objLock.Destroy();	
}

/*********************************************************************
��  	�ƣ�PushHeadDeque
��	�ܣ��������ݵ�Dequeͷ��
��  	����
 		tNewElement[IN]
 				Ҫ����ͷ�������ݣ������ݱ����Ǳ�ģ����ʵ����ʱ��
				��������
����	ֵ��	��			
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::PushHeadDeque (T tNewElement)
{
	//�������ݵ�dequeͷ��
	m_deque.push_front (tNewElement);
	
	m_ulDataCount++;
}

/*********************************************************************
��  	�ƣ�PushTailDeque
��	�ܣ��������ݵ�Dequeβ��
��  	����
 		tNewElement[IN]
 				Ҫ����ͷ�������ݣ������ݱ����Ǳ�ģ����ʵ����ʱ��
				��������
����	ֵ��	��	
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::PushTailDeque (T tNewElement)
{
	//�������ݵ�dequeͷ��
	m_deque.push_back (tNewElement);
	
	m_ulDataCount++;
}

/*********************************************************************
��  	�ƣ�PopHeadDeque
��	�ܣ���ȡ��Ϣ����ͷ��������
��  	����
 		tNewElement[OUT]
 				������ݵı������������Ǳ�ģ����ʵ����ʱ����������
����	ֵ��	��		
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::PopHeadDeque (T &tElement)
{
	//��ȡdeque��ͷ������
	tElement = m_deque.front ();
	
	//ɾ��deque��ͷ������
	m_deque.pop_front ();
	m_ulDataCount--;
}

/*********************************************************************
��  	�ƣ�PopTailDeque
��	�ܣ���ȡ��Ϣ����ͷ��������
��  	����
 		tNewElement[OUT]
 				������ݵı������������Ǳ�ģ����ʵ����ʱ����������
����	ֵ��	��	
*********************************************************************/
template<typename T>
void CMsgQueueEx<T>::PopTailDeque (T &tElement)
{
	//��ȡdeque��ͷ������
	tElement = m_deque.back ();
	
	//ɾ��deque��ͷ������
	m_deque.pop_back ();
	m_ulDataCount--;
}	

/*********************************************************************
��  	�ƣ�PushHead
��	�ܣ��������ݵ���Ϣ����ͷ��
��  	����
 		tNewElement[IN]
 				Ҫ����ͷ�������ݣ������ݱ����Ǳ�ģ����ʵ����ʱ��
				��������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PushHead (T tNewElement)
{
	//����deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		PushHeadDeque (tNewElement);
		
		//deque����
		m_objLock.Unlock();
		return 1;
	}
	return 0;
}

/*********************************************************************
��  	�ƣ�PushTail
��	�ܣ��������ݵ���Ϣ����β��
��  	����
 		tNewElement[IN]
 				Ҫ����β�������ݣ��˶��������ݱ����Ǳ�ģ����ʵ����ʱ��
				��������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PushTail (T tNewElement)
{
	//����deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		PushTailDeque (tNewElement);

		//deque����
		m_objLock.Unlock();		
		
		return 1;
	}
	return 0;
}

/*********************************************************************
��  	�ƣ�PopHead
��	�ܣ���ȡ��Ϣ����ͷ��������
��  	����
 		tNewElement[OUT]
 				������ݵı������������Ǳ�ģ����ʵ����ʱ����������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PopHead (T &tElement)
{
	bool bRet = 0;
	
	//����deque
	if (m_ulDataCount > 0 && 0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{	
		if (0 < m_ulDataCount)
		{
			PopHeadDeque (tElement);		
			
			bRet = 1;
		}
		//deque����
		m_objLock.Unlock();
	}	
	return bRet;
}


/*********************************************************************
��  	�ƣ�PopTail
��	�ܣ���ȡ��Ϣ����β��������
��  	����
 		tNewElement[OUT]
 				������ݵı������������Ǳ�ģ����ʵ����ʱ����������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PopTail (T &tElement)
{
	bool bRet = 0;
		
	//����deque
	if (m_ulDataCount > 0 && 0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{	
		if (0 < m_ulDataCount)
		{
			PopTailDeque (tElement);
					
			bRet = 1;
		}
		//deque����
		m_objLock.Unlock();
	}	
	return bRet;
}

/*********************************************************************
��  	�ƣ�PushDeque2Head
��	�ܣ�����dequeȫ�����ݵ���Ϣ����ͷ��
��  	����
 		deque[IN]
 				Ҫ����ͷ�������ݣ������ݱ����Ǳ�ģ����ʵ����ʱ��
				��������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PushDeque2Head (deque<T> deq)
{
	//����deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		//�������ݵ�dequeͷ��

		unsigned long ulSize = deq.size ();
		while (ulSize-- > 0)
		{			
			PushHeadDeque (deq.back ());
			deq.pop_back ();
		}
		
		//deque����
		m_objLock.Unlock();
		return 1;
	}
	return 0;
}

/*********************************************************************
��  	�ƣ�PushDeque2Tail
��	�ܣ�����dequeȫ�����ݵ���Ϣ����β��
��  	����
 		deque[IN]
 				Ҫ����ͷ�������ݣ��˶��������ݱ����Ǳ�ģ����ʵ����ʱ��
				��������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
bool CMsgQueueEx<T>::PushDeque2Tail (deque<T> deq)
{
	//����deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		//�������ݵ�dequeβ��
		unsigned long ulSize = deq.size ();
		while (ulSize-- > 0)
		{
			PushTailDeque (deq.front ());
			deq.pop_front ();
		}
		
		//deque����
		m_objLock.Unlock();
		return 1;
	}
	return 0;
}

/*********************************************************************
��  	�ƣ�PopHead2Deque
��	�ܣ���ȡ��Ϣ����ͷ�������ݵ�����
��  	����
 		deque[OUT]
 				������ݵĶ��У��������Ǳ�ģ����ʵ����ʱ����������
 		ulCount[OUT]
 				ҪPop�����������������ݲ��ܴ��ڱ�ģ�鱣��������������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
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
	 			//deque����
	 			m_objLock.Unlock();		
	 			
		}	
	}
	return bRet;
}

/*********************************************************************
��  	�ƣ�PopTail2Deque
��	�ܣ���ȡ��Ϣ����β�������ݵ�����
��  	����
 		deque[OUT]
 				������ݵĶ��У��������Ǳ�ģ����ʵ����ʱ����������
 		ulCount[OUT]
 				ҪPop�����������������ݲ��ܴ��ڱ�ģ�鱣��������������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
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
	 			
	 			//deque����
	 			m_objLock.Unlock();			 			
		}			
	}
	return bRet;
}

/*********************************************************************
��  	�ƣ�RemoveAll
��	�ܣ������Ϣ�����е���������
��  	����
 		��
����	ֵ��		
		��
*********************************************************************/
template<typename T>
unsigned long CMsgQueueEx<T>::RemoveAll ()
{
	unsigned long ulCount = 0;
	
	//����deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{				
		unsigned long ulSize = m_ulDataCount;
		while (ulSize-- > 0)
		{			
			T Val;
			
			//�����������������ݽ���ɾ��
			PopHeadDeque (Val);
			
			ulCount++;
		}
		m_objLock.Unlock ();
	}
	return ulCount;
}

/*********************************************************************
��  	�ƣ�Count
��	�ܣ���ȡ��Ϣ�����������ܸ���
��  	����
 		��
����	ֵ��		
		���ض����������ܸ�����Ϣ				
*********************************************************************/
template<typename T>
unsigned long CMsgQueueEx<T>::Count ()
{
	unsigned long ulSize = 0;
	
	//����deque
	if (0 == m_objLock.Lock (EN_LOCK_TIMEOUT))
	{
		ulSize = m_ulDataCount;
		//deque����
		m_objLock.Unlock();
	}
	return ulSize;
}






/*********************************************************************
��  	�ƣ�CNotifyQueue
�� 	�ܣ���MsgQueueEx(���ݶ���)�Ļ����������첽֪ͨ����				
*********************************************************************/
template<typename T>
class CNotifyQueue 
{
private:
	CPSX_Semaphore	m_objSem;		//���ݵ���֪ͨ
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
��  	�ƣ�Init
��	�ܣ���ʼ����Ϣ���У��˺���������ʼ��֪ͨ��Ϣ�������ݵ���
		���ź���
��  	����
 		��
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
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
��  	�ƣ�Uninit
��	�ܣ�����ʼ����Ϣ���У��˺���������ʼ��֪ͨ��Ϣ�������ݵ���
		���ź���
��  	����
		��
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
*********************************************************************/
template<typename T>
void CNotifyQueue<T>::Uninit ()
{
	//����ʼ������
	m_objQueue.Uninit ();

	//����ʼ���ź���
	m_objSem.Destroy();
}

/*********************************************************************
��  	�ƣ�PushHead
��	�ܣ��������ݵ���Ϣ����β��
��  	����
 		tNewElement[IN]
 				Ҫ����β�������ݣ������ݱ����Ǳ�ģ����ʵ����ʱ��
				��������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
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
��  	�ƣ�PushTail
��	�ܣ��������ݵ���Ϣ����β��
��  	����
 		tNewElement[IN]
 				Ҫ����β�������ݣ������ݱ����Ǳ�ģ����ʵ����ʱ��
				��������
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
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
��  	�ƣ�PopTail
��	�ܣ���ȡ��Ϣ����β��������
��  	����
 		tNewElement[OUT]
 				������ݵı������������Ǳ�ģ����ʵ����ʱ����������
 		ulMs[OUT]
 				Pop����ʱ���ȴ�ʱ��
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
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
��  	�ƣ�PopTail
��	�ܣ���ȡ��Ϣ����β��������
��  	����
 		tNewElement[OUT]
 				������ݵı������������Ǳ�ģ����ʵ����ʱ����������
		ulMs[OUT]
 				Pop����ʱ���ȴ�ʱ��
����	ֵ��		
		1	�ɹ�
		0	ʧ��				
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
��  	�ƣ�Count
��	�ܣ���ȡ��Ϣ�����������ܸ���
��  	����
 		��
����	ֵ��		
		���ض����������ܸ�����Ϣ				
*********************************************************************/
template<typename T>
unsigned long CNotifyQueue<T>::Count ()
{
	return m_objQueue.Count();
}

/*********************************************************************
��  	�ƣ�RemoveAll
��	�ܣ������Ϣ�����е���������
��  	����
 		��
����	ֵ��		
		��
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
