#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	string s = string(argv[1]);
	int n = atoi(s.c_str());
	int i;
	cout<<"a1 :- not a1."<<endl;
	for(i=2; i<=n; i++)
	{
		cout<<"a"<<i<<" + a"<<i<<" :- a"<<i-1<<"."<<endl;
	}
	return 0;
}

