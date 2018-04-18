#include <pthread.h>
#include <stdio.h>

int n = 0;

void *A(void *arg) {
	while (1) {
		n++;
	}
}

void *B(void *arg) 
{
	while (1) 
	{
		printf("%d\n", n);
		n = 0;
	}
}


int main(void) {
	pthread_t p1, p2;
	pthread_create(&p1, NULL, A, NULL);
	pthread_create(&p2, NULL, B, NULL);
	pthread_join(p1, NULL);
	pthread_join(p2, NULL);
}