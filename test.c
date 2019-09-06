//#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

//using namespace std; 
int main(){
	char s[1024];
	char* argv[100];
	char path[50];
	char cmd[1024];

	while(1){
		
		if(!fgets(s,1024,stdin))
			break;
		  char end[]="exit\n";
                 if(strcmp(s,end)==0)
                                break;

	//	char* s1;
		strcat(s," STOP");
		/*char *p = strchr(s, '\n');
                if (p) *p = 0;
                if(strcmp(s, "exit")==0)
                        break;
		
		char end[]="exit";
		 if(strcmp(s,end)==0)
                                break;*/
		char* args1[100];
		int i=0;
		 char* s1 = strtok (s, " ");
		 args1[0]=s1;
		 char stp[]="STOP";
		while ((s1!= NULL)||(s1!="STOP"))
  		{
    			s1 = strtok (NULL, " ");
			args1[++i]=s1;
			printf("\np:%s   args[i-1]:%s    s: %s  len of P:%d \n",s1,args1[i],s,strlen(s1));
			char ch = s1[strlen(s1)];
			if(strcmp(s1,stp)==0)
				break;	

  		}
		//args1[++i]=(char*)0;
	}
		//

		//printf("\n Path:%s cmd:%s \n",cmd,*args);
    return 0;
}
