#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

std::mutex m;

void share_print(string msg, int id){
	lock_guard<mutex> guard(m);
	//m.lock();
	cout << msg << id << endl;
	m.unlock();
}

void function_1(){
	for (int i=0; i<100; i++){
		share_print(string("t1: "), i);
	}
}


int main(){
	thread t1(function_1);

	for (int i=100; i<200; i++){
		share_print(string("main : "), i);
	}

	t1.join();
	return 0;
}
