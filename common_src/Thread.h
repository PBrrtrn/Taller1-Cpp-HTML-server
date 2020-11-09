#ifndef __THREAD_H__
#define __THREAD_H__

#include <thread>

class Thread {
private:
	std::thread thread;
public:
	Thread();
	virtual ~Thread();
	virtual void run() = 0;
	void start();
	void join();
	Thread(const Thread&) = delete; 					 // Saco el constructor por copia
	Thread& operator=(const Thread&) = delete; // Saco la asignacion por copia
	Thread(Thread&& other);										 // Construccion por movimiento
	Thread& operator=(Thread&& other);				 // Asignacion por movimiento
};

#endif