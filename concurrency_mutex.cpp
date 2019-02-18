/* Apache License
Version 2.0, January 2004
http://www.apache.org/licenses/


Threads are used to make use of the concurrency provided by the CPU
mutex is used to prevent race conidtions between shared buffers used
by threads

Due to race contitions the list size is never the expected value
Add mutex to make the instruction  list.push_back(i); mutually
exclusive

Deadlock: Adding Mutex.lock and Mutex.unlock may resolve the race condition
but if one of the threads that has locked the mutex terminates without unlocking
the same all other threads will wait in the mutex and the program will not terminate.
To resolve this we should make sure that the mutex is always unlocked before
the thread exits.
Use std::lock_guard<std::mutex> Mguard(Mutex);


compilation cmd:
$ g++ -std=c++11 concurrency_mutex.cpp
*/



#include<iostream>
#include<thread>
#include<mutex>
#include<list>

const int SIZE = 100000;
const int MAX_THREADS = 16;

//std::list<int> g_list;
void growlist(std::list<int> &list /*std::string &s1*/, std::mutex &Mutex) 
{
	std::cout << "Growing the list using thread:" << std::this_thread::get_id() << std::endl;
	for (int i=0; i<SIZE; i++) {
		std::lock_guard<std::mutex> Mguard(Mutex);
		//Mutex.lock();
		list.push_back(i);
		if (i == SIZE/2)
			return;
		//Mutex.unlock();
	}
}
int main () 
{
	int cores = std::thread::hardware_concurrency();
	std::thread t[MAX_THREADS];
	std::list<int> list;
	std::mutex Mutex;
	std::string s = "HI";
	int i;
	std::cout << "No of CPU cores: " << cores << std::endl;
		for (i = 0; i < cores; i++) {
			t[i] = std::thread(growlist, std::ref(list) /*std::ref(s)*/, std::ref(Mutex));
		}
	std::cout << "Launched " << i << " threads ..." << std::endl;
		for (i = 0; i < cores; i++) {
			t[i].join();
		}
	std::cout << "All threads are done executing, list size: " << list.size() << " (expected:" \
		 << cores*SIZE << ")" << std::endl;
	return 0;
}
