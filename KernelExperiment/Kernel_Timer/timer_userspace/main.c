#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

main()
{
	int fd;
	int counter =0 ;
	int old_counter = 0;
	fd = open("dev/Timer",O_RDONLY);
	if(fd<0)
		return;
	while(1)
	{
		read(fd,&counter,sizeof(unsigned int));
		if(counter!=old_counter)
		{
			printf("Seconds after open /dev/Timer: %d\n",counter);
			old_counter = counter;
		}
	}

}

