// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <mutex>
#include <condition_variable>
/**
 * 
 */
class TWITCHTEST_API Semaphore
{
private:
	std::mutex mutex;
	std::mutex mtx;
	std::condition_variable condition;
	unsigned long count;
	bool ready = false;

public:
	Semaphore()
		: count()
	{}

	void post()
	{
		mutex.lock();
		++count;
		ready = true;
		mutex.unlock();
		condition.notify_one();
	}

	void wait()
	{ 
		mutex.lock();
		if (count == 0) {
			ready = false;
		}
		mutex.unlock();
		std::unique_lock<std::mutex> lck(mtx);
		while (!ready) condition.wait(lck);
		mutex.lock();
		--count;
		mutex.unlock();
	}
};
