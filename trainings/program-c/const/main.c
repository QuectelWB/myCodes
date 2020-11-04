#include <stdio.h>

int g =2;
// const int g =2; If it is const , cannot be changed . But it is strange why
// the compiler cannot find the error?

extern void add_g(void);

main()
{
//g = 1;

	printf("%s %d\n", __func__, g);
	add_g();
	printf("%s %d\n", __func__, g);
}
