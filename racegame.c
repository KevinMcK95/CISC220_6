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

char* mover(char* str, int position, int moves, int len, int lane){
	char newString[len], ending[10];
	int i;
	for (i=0; i<(position+moves); i++){
		strcat(newString,"~");
	}
	strcat(newString,"|->");
	for (i=(position+moves+3); i<(len-10); i++){
		strcat(newString," ");
	}
	sprintf(ending,"# Lane %d #",lane);
	strcat(newString,ending);
	strcpy(str,newString);
	return str;
}

int main(void){
	int len = 40+3+10;
	char str1[len], str2[len], str3[len], str4[len], str5[len];
	strcpy(str1,"|->                                        # Lane 1 #");
	strcpy(str2,"|->                                        # Lane 2 #");
	strcpy(str3,"|->                                        # Lane 3 #");
	strcpy(str4,"|->                                        # Lane 4 #");
	strcpy(str5,"|->                                        # Lane 5 #");
	printer(str1,str2,str3,str4,str5);
	mover(str1,2,0,len,1);
	printer(str1,str2,str3,str4,str5);

	return 0;
}
