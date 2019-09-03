#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <QReadWriteLock>
#include <QWaitCondition>
#include <QQueue>

template <typename T>
class SyncQueue
{
public:
	SyncQueue();

	virtual ~SyncQueue() {};


	inline bool isEmpty() const;
	inline bool isEnough() const;
	inline bool isFull() const;

	bool put(const T& t, unsigned long wait_timeout_ms = ULONG_MAX);
	bool tack(T& result, unsigned long wait_timeout_ms = ULONG_MAX);

	void wakeALL()
	{
		cond_full.wakeAll();
	}

private:
	mutable QReadWriteLock lock;//保证能在const方法中上锁
	QWaitCondition cond_empty;
	QWaitCondition cond_full;
	QQueue<T> queue;
	int enough;
	int full;
};



template <typename T>
bool SyncQueue<T>::isEmpty() const
{
	QReadLocker locker(&lock);
	Q_UNUSED(locker);
	return queue.isEmpty();
}

template <typename T>
bool SyncQueue<T>::isFull() const
{
	QReadLocker locker(&lock);
	Q_UNUSED(locker);
	return queue.size() >= full;
}

template <typename T>
bool SyncQueue<T>::isEnough() const
{
	QReadLocker locker(&lock);
	Q_UNUSED(locker);
	return queue.size() >= enough;
}

template <typename T>
SyncQueue<T>::SyncQueue()
	:queue()
	,enough(40)
	,full(800)
{

}

template <typename T>
bool SyncQueue<T>::put(const T& t, unsigned long wait_timeout_ms /*= ULONG_MAX*/)
{
	bool ret = true;
	QWriteLocker locker(&lock);
	Q_UNUSED(locker);
	if (queue.size() >= full)
	{
		cond_full.wait(&lock, wait_timeout_ms);//释放锁等待条件满足
	}
	if (queue.size() >= full)
	{
		return false;
	}
	queue.enqueue(t);
	if (queue.size() >= enough)
	{
		cond_empty.wakeOne();
	}

	return ret;
}

template <typename T>
bool SyncQueue<T>::tack(T& result, unsigned long wait_timeout_ms /*= ULONG_MAX*/)
{
	bool ret = true;
	QWriteLocker locker(&lock);
	Q_UNUSED(locker);
	if (queue.size() <= 0)
	{
		cond_empty.wait(&lock, wait_timeout_ms);
	}

	if (queue.size() <= 0)
	{
		cond_full.wakeOne();//唤醒等待put的线程
		return false;
	}
	result = queue.dequeue();
	cond_full.wakeOne();//唤醒等待put的线程
	return ret;
}

#endif