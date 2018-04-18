#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
	
	int child;
	
	char * argv[] = {"echo", "Hello, World!", NULL};
	char * envp[] = {NULL};
	
	if (!(child = fork())) {
		printf("pid %d: pid %d is my father\n", getpid(), getppid());
		execve("/bin/echo", argv, envp);
		printf("pid %d: I'm back, something is wrong!\n", getpid());
	} else {
		int selfpid = getpid();
		printf("pid %d: pid %d is my son\n", selfpid, child);
//		wait4(child, NULL, 0, NULL);
//		wait3(&child, 0, NULL);
		waitpid(child, &selfpid, 0);
		printf("pid %d: done\n", selfpid);
	}
}