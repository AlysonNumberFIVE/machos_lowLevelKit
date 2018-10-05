


#include <stdio.h>
#include <signal.h>

void	killing(int sig)
{
	printf("kiling");
	return ;
}

int	main(void)
{
	signal(SIGKILL, killing);
	printf("hello world\n");
	return (0);
}
