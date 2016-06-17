// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <mutex>
#include <condition_variable>
/**
 * 
 */
class Semaphore
{
private:
	std::mutex mutex;
	std::mutex mtx;
	//std::unique_lock<std::mutex> lck(mtx);
	std::condition_variable condition;
	unsigned long count;
	bool ready = false;

public:
	Semaphore(unsigned long _count = 0) : count(_count) {}

	void post()
	{
		mutex.lock();
		++count;
		if (count > 0) {
			ready = true;
		}
		mutex.unlock();
		if (ready) {
			condition.notify_one();
		}
	}

	void wait()
	{ 
		std::unique_lock<std::mutex> lck(mtx);
		if (count <= 0) {
			ready = false;
		}
		//std::unique_lock<std::mutex> lck(mtx);
		while (!ready) condition.wait(lck);
		mutex.lock();
		--count;
		mutex.unlock();
	}
};
