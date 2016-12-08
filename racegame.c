#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 6

void printer(char* str1, char* str2, char* str3, char* str4, char* str5){
	system("clear");
	printf("Welcome to CISC220 Racing Arena\n");
	printf("Hit Enter to move forward\n\n");
	printf("%s\n",str1);
	printf("%s\n",str2);
	printf("%s\n",str3);
	printf("%s\n",str4);
	printf("%s\n",str5);
	return;
}

char* mover(char* str, int position, int len, int lane){
	char newString[len], ending[10];
	int i;
	for (i=0; i<(position); i++){
		strcat(newString,"~");
	}
	strcat(newString,"|->");
	for (i=(position+4); i<(len-10); i++){
		strcat(newString," ");
	}
	sprintf(ending,"# Lane %d #",lane);
	strcat(newString,ending);
	strcpy(str,newString);
	return str;
}

void * printing(){
	pthread_exit(NULL);
}

void* user(void* t){
	int lane;
	lane = (int) t;
	char input[10];
	fgets(input,10,stdin);
	if (input[0] == '\n')
		printf("It worked!\n");
	else
		printf("Not proper entry!\n");
	pthread_exit(NULL);
}

void* others(){
	int sleep;
	sleep = rand() % 100;
	int pos;
	pthread_exit(NULL);
}

int main(void){
	int len = 40+3+10, done = 0, i;
	int positions[5] = {0,0,0,0,0};
	char str1[len], str2[len], str3[len], str4[len], str5[len];
	strcpy(str1,"|->                                        # Lane 1 #");
	strcpy(str2,"|->                                        # Lane 2 #");
	strcpy(str3,"|->                                        # Lane 3 #");
	strcpy(str4,"|->                                        # Lane 4 #");
	strcpy(str5,"|->                                        # Lane 5 #");
//	printer(str1,str2,str3,str4,str5);
//	mover(str1,2,0,len,1);
//	printer(str1,str2,str3,str4,str5);
/*	while (done != 1){
		for (i=0; i<5; i++){
			if (positions[i] <= 40)
				done = 1;
				continue;
		}
	}	*/
	int rc;
	long t;
	pthread_t threads[NUM_THREADS];
	for (t=0; t<NUM_THREADS; t++){
		rc = pthread_create(threads+t,NULL,user,(void *) t);
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
		}
	}
	pthread_exit(NULL);
}
