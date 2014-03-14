#include <stdlib.h>

#include <stdio.h>

int main(int argc, char** argv)
{
 int i,n;
 if(argc==1) return 0;
 n= atoi(argv[1]);
 printf("a(0) :- #0.9.\n");
 for(i=0; i<n; i++)
 {
	printf("a(%d) :- a(%d).\n", i+1, i);
 }
 return 0;
}
