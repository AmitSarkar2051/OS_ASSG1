#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

using namespace std; 
int main(){
	char s[1024];
	char* argv[100];
	char path[50];
	char cmd[1024];

	char econd[]="exit";
	while(1){


		if(!fgets(s,1024,stdin))
			break;
    		memset(cmd,0,sizeof(cmd));
    		if(strncmp(s, "exit", (strlen(s)-1))==0)  
			break;
    		strncpy(cmd,s,(strlen(s)-1));
    		strcpy(path,"/bin/");
    		strcat(path,cmd);
    		int pid= fork();              //fork child
    		if(pid==0){               //Child
        		execl(path,cmd,NULL);
        		exit(0);// you must exit from the child because now you are inside while loop of child. Otherwise you have to type exit twice to exit from the application. Because your while loop also became the part of every child and from the child again it will call fork and create a child again
    		}else{
        		wait(NULL);
    		}
 }
	return 0;
}
