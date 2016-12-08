#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 6
#define LEN 54 //length of spaces + car + # LANE NUM # + null= 40 + 3 + 10 + 1

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

void mover(char* str){
	char ending[10], lane, cart[3];
	strcpy(cart,"|->");
	int i=0, position;
	while (i < LEN-1){
		if (str[i] == '|'){
			position = i;
		}
		if (i == 50){
			lane = str[i];
		}
		i++;
	}
	sprintf(ending,"# Lane %c #",lane);
	for (i=0; i<(LEN); i++){
		if (i<(position+1))
			str[i] = '~';
		else if (i < (position+4)){
			str[i] = cart[i-position-1];
		}
		else if (i < (LEN-11))
			str[i] = ' ';
		else
			str[i] = ending[i-LEN+11];
	}
	return;
}

void * printing(void* strAddress){
	char *strAdd;
	strAdd = (char *) strAddress;
	char *str1, *str2, *str3, *str4, *str5;
	str1 = strAdd[0];
	printf("%s\n",str1);
	str2 = (char *) strAdd[1]; 
	str3 = (char *) strAdd[2]; 
	str4 = (char *) strAdd[3]; 
	str5 = (char *) strAdd[4];
	usleep(20*1000); //sleep for 20 milliseconds
	printer(str1, str2, str3, str4, str5);
	pthread_exit(NULL);
}

void* user(void* str){
	char* str1;
	str1 = (char *) str;
	char input[10];
	fgets(input,10,stdin);
	if (input[0] != 'n'){
		mover(str1);
		printf("test\n");
//		mover(str1);
	}
	pthread_exit(NULL);
}

void* others(void* str){
	char* car;
	car = (char *) str;
	int sleep;
	sleep = rand() % 100;
	usleep(sleep*10000); //usleep time in microseconds, so multiply by 1000 to get milli
	mover(car);
	printf("sleep = %d\n",sleep);
	pthread_exit(NULL);
}

int main(void){
	int done = 0, i;
	int positions[5] = {0,0,0,0,0};
	char str1[LEN], str2[LEN], str3[LEN], str4[LEN], str5[LEN], strAdd[5][LEN];
	strcpy(strAdd[0],str1);
	strcpy(strAdd[1],str2); 
	strcpy(strAdd[2],str3);
	strcpy(strAdd[3],str4); 
	strcpy(strAdd[4],str5);
	strcpy(str1,"|->                                        # Lane 1 #");
	strcpy(str2,"|->                                        # Lane 2 #");
	strcpy(str3,"|->                                        # Lane 3 #");
	strcpy(str4,"|->                                        # Lane 4 #");
	strcpy(str5,"|->                                        # Lane 5 #");
	printer(str1,str2,str3,str4,str5);
//	mover(str1);
//	printer(str1,str2,str3,str4,str5);
//	return 0;
	int rc;
	int lane;
	pthread_t threads[NUM_THREADS];
	while (done != 1){
		for (lane=1; lane<NUM_THREADS+1; lane++){
			if (lane == 1){
				rc = pthread_create(threads+lane,NULL,user,(void *) str1);
				printer(str1,str2,str3,str4,str5);
			}
/*			else if (lane < 6){
				char *str;
				if (lane == 2)
					str = str2;
				else if (lane == 3)
					str = str3;
				else if (lane == 4)
					str = str4;
				else
					str = str5;
				rc = pthread_create(threads+lane,NULL,others,(void *) str);
			}
//			else
//				rc = pthread_create(threads+lane,NULL,printing,(void *) strAdd);*/
			if (rc){
				printf("ERROR; return code from pthread_create() is %d\n",rc);
				exit(-1);
			}
		}
	}
	pthread_exit(NULL);
}
