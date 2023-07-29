#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int pid1;
	int pid2;
	int pid_end_1;
	int	pid_end_2;

	pid1 = fork();
	if (pid1 == -1)
	{
		printf("Error crating process\n");
		return (1);
	}
	if (pid1 == 0)
	{
		printf("Started execution of process %d\n", getpid());
		sleep(4);
		printf("Finished execution of process %d\n", getpid());
		return (0);
	}
	pid2 = fork();
	if (pid2 == -1)
	{
		printf("Error creating process\n");
		return (1);
	}
	if (pid2 == 0)
	{
		printf("Started execution of process %d\n", getpid());
		sleep(1);
		printf("Finished execution of process %d\n", getpid());
		return (0);
	}
	
	pid_end_1 = waitpid(pid1, NULL, WNOHANG);
	printf("first finished process %d\n", pid_end_1);
	pid_end_2 = waitpid(pid2, NULL, WNOHANG);
	printf("second finished process %d\n", pid_end_2);
	return (0);
}
