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
	cout<<"a0."<<endl;
	for(i=1; i<=n; i++)
	{
		cout<<"a"<<i<<" :- a"<<i-1<<", not a"<<i<<"."<<endl;
	}
	return 0;
}

