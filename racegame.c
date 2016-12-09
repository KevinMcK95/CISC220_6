#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 6
#define LEN 54 //length of spaces + car + # LANE NUM # + null= 40 + 3 + 10 + 1

int positionArr[NUM_THREADS-1]={0,0,0,0,0};
int first;

void printer(int position, int lane){
	int i;
	for (i=0;i<position;i++){
		printf("~");
	}
	printf("|->");
	for (i = (position+3); i<(40+3); i++){
		printf(" ");
	}
	printf("# Lane %d #\n",lane);
	return;
}

void mover(int lane){
	positionArr[lane-1] = positionArr[lane-1]+1;
	return;
}

int tester(void){
	int i;
	for(i=0;i<5;i++){
		if (positionArr[i]==40){
			return 0;
		}
	}
	return 1;
}

void * printing(void* laneJunk){
	while(tester() ){
		system("clear");
		printf("Welcome to CISC220 Racing Arena\n");
		printf("Hit Enter to move forward\n\n");
		int i, pos;
		for (i=0; i<5; i++){
			int lane = i+1;
			pos = positionArr[i];
			printer(pos,lane);
		}
		usleep(20*1000); //sleep for 20 milliseconds
	}
	pthread_exit(NULL);
}

void* user(void* lane){
	char input[10];
	while(tester() ){
		fgets(input,10,stdin);
		if (input[0] == '\n'){
			first = 1;
			mover(*((int*)lane));
		}
	}
	pthread_exit(NULL);
}

void* others(void* lane){
	while( tester() ){
		int sleep;
		sleep = rand() % 100;
		usleep(sleep*1000); //usleep time in microseconds, so multiply by 1000 to get milliseconds
		mover(*((int*)lane));
	}
	pthread_exit(NULL);
}

int main(void){
	first = 0; // the user hasn't inputted yet
	int id[NUM_THREADS];
	int rc;
	int lane;
	pthread_t threads[NUM_THREADS];
	id[0] = 0;
	rc = pthread_create(threads+0,NULL,printing,(void *) (id+0));
	if (rc){
		printf("ERROR; return code from pthread_create() is %d\n",rc);
		exit(-1);
	}
	for (lane=1; lane<NUM_THREADS; lane++){
		id[lane]=lane;
		if (lane == 1){
			rc = pthread_create(threads+lane,NULL,user,(void *) (id+lane));
		}
		else if (lane < NUM_THREADS){
			while(first == 0){
			}
			rc = pthread_create(threads+lane,NULL,others,(void *) (id+lane));
		}
		if (rc){
			printf("ERROR; return code from pthread_create() is %d\n",rc);
			exit(-1);
		}
	}
	//wait for threads to finish
	for(lane = 0; lane< NUM_THREADS; lane++){
		pthread_join(threads[lane],NULL);
	}
	//need to do one final print to show the last positions
	system("clear");
	printf("Welcome to CISC220 Racing Arena\n");
	printf("Hit Enter to move forward\n\n");
	int i, pos;
	for (i=0; i<5; i++){
		int lane = i+1;
		pos = positionArr[i];
		printer(pos,lane);
	}
	//find the winner and print that out
	for(lane = 1; lane<6; lane++){
		if (positionArr[lane-1]==40){
			printf("\nPlayer %d WINS\n",lane); //this means ties go to the lowest lane number
			pthread_exit(NULL);
			return 0;
		}
	}
}
