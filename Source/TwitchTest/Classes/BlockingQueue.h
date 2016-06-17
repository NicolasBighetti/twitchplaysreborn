// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <mutex>
#include <condition_variable>
#include <semaphore.h> 
#include <deque>

/**
  * Blocking queue.
  */
template <typename T>
class BlockingQueue
{
private:
	// Mutex to push/pop
	std::mutex d_mutex;
	
	// Semaphore to handle when queue is empty
	Semaphore empty;
	
	// Queue containing elements
	TQueue<T> Queue;
public:
	/**
      *	Check if queue is empty.
	  */
	bool IsEmpty()
	{
		return Queue.IsEmpty();
	}

	/**
      *	Push new element in the queue.
	  */
	void push(T const& value) {

		d_mutex.lock();
		Queue.Enqueue(value);
		empty.post();
		d_mutex.unlock();
	}

	/**
      *	Pop an element from the queue (blocking method, until there is anything to pop).
	  */
	T pop() {
		T cmd;
		empty.wait();
		d_mutex.lock();
		Queue.Dequeue(cmd);
		d_mutex.unlock();
		return cmd;
	}

	/**
      *	Clear the queue.
	  */
	void clear() {
		d_mutex.lock();
		while (!Queue.IsEmpty()) {
			T item;
			Queue.Dequeue(item);
		}
		d_mutex.unlock();
	}
};