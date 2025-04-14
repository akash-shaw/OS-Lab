#include<stdio.h>
#include <string.h>

#include <unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
int *status;



int main(){
	int BUFLEN=10;
	char buffer[BUFLEN+1];
	strncpy(buffer, "CHILD\n", BUFLEN);
	buffer[BUFLEN]='\0';


	printf("%s\n%ld\n",buffer,strlen(buffer));
	return 0;
}