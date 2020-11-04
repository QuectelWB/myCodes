#include<stdio.h>
extern int g;

void add_g(void)
{
	printf("[%s] g= %d \n",__func__,g);
	g++;
	printf("[%s] g= %d \n",__func__,g);
}
