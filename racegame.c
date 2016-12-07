#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>


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


int main(void){
	int len = 40+3+10;
	char str1[len], str2[len], str3[len], str4[len], str5[len];
	strcpy(str1,"|->                                        # Lane 1 #");
	strcpy(str2,"|->                                        # Lane 1 #");
	strcpy(str3,"|->                                        # Lane 1 #");
	strcpy(str4,"|->                                        # Lane 1 #");
	strcpy(str5,"|->                                        # Lane 1 #");
	printer(str1,str2,str3,str4,str5);
	return 0;
}
