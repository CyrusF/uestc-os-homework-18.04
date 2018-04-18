#include <pthread.h>
#include <stdio.h>
#include <sys/msg.h>
#include <unistd.h>

typedef struct {
	long msgtype;
	char msg;
} Message;

int msgid;
int MSGSZ = 1;
int MSGTYPE = 233;

void productor(void *arg) {
	Message msg;
	msg.msgtype = MSGTYPE;  
	FILE *fp;
	fp = fopen("test.txt", "r");
	char ch;
	while ((ch = fgetc(fp)) != EOF) {
		msg.msg = ch;
		msgsnd(msgid, &msg, MSGSZ, 0);
		printf("in: %c\n", msg.msg);
		sleep(1);
	}
}

void consumer(void *arg) {
	Message msg;
	int ret;
	while (1) {
		ret = msgrcv(msgid, &msg, MSGSZ, MSGTYPE, IPC_NOWAIT);
		if (ret != -1) {
			printf("\t\tout: %c\n", msg.msg);
		} else {
			break;
		}
		sleep(2);
	}
}

int main() {
	int productor_N = 2;
	int consumer_N = 3;
	pthread_t ps[productor_N], cs[consumer_N];
	int selfpid = getpid();
	printf("pid: %d\n", selfpid);
	msgid = msgget(selfpid, IPC_CREAT | 0666);
	printf("msgid key: %d\n", msgid);

	for (int i = 0; i < productor_N; i++) {
		pthread_create(&ps[i], NULL, (void *)productor, NULL);
	}
	for (int i = 0; i < consumer_N; i++) {
		pthread_create(&cs[i], NULL, (void *)consumer, NULL);
	}

	for (int i = 0; i < productor_N; i++) {
		pthread_join(ps[i], NULL);
	}
	for (int i = 0; i < consumer_N; i++) {
		pthread_join(cs[i], NULL);
	}
}