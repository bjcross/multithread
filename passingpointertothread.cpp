#include <iostream>
#include <thread>
using namespace std;



class fctor{
	public:
		void operator()(string* msg){
			cout << "t1 says: " << *msg << endl;		
			*msg = "well i fucked up";
		}
};



int main(){
//	fctor fct;
	string s = "Where i fuck you duck";
	string* ps = &s;
	thread t1(fctor(), ps);


	t1.join();
	cout << "main : " << s << endl;
	return 0;
}
