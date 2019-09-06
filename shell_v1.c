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
	char end[]="exit\n";
	char stp[]="STOP";

	while(1){
		
		if(!fgets(s,1024,stdin))
			break;
		 if(strcmp(s,end)==0)
                                break;
		char *p = strchr(s, '\n');
                if (p) *p = 0;

		 strcat(s," STOP ");

    
		char bin[]="/bin/";
		strcpy(cmd,bin);
		char line[1024];
		strcpy(line,s);
		char* s1=strtok(line," ");
		strcat(cmd,s1);
    
		// 2nd arg for execv args
		char * args1[100];
		args1[0]=s1;
		int i=0;
		while (s1!= NULL)
  		{
    			if(strcmp(s1,stp)==0)
                                break;
    			s1 = strtok (NULL, " ");
			args1[++i]=s1;
			//printf("\ni:%d     p:%s   args[i-1]:%s    s: %s  len of P:%d \n",i,s1,args1[i],s,strlen(s1));

  		}
		/*int tmp= strlen(args1[i-1]);
		args1[i][tmp-1]='\0';
		printf("\n\ni:%d_____arg i :%s____sizeof arg i :____%d \n\n",i-1,args1[i-1],strlen(args1[i-1]));
		*/
		args1[i]=(char*)0;
		//args1[i]="donedonadon";
		
		//

		//printf("\n Path:%s s input :%s \n",cmd,s);
        	int pid= fork();
		if(pid<0){
			printf("\nERROR: in pid\n");
			return 0;
		}
	              //fork child
        	if(pid==0) {
	 		//printf("\n Path:%s args1:%s-%s-%s-%s \n",cmd,args1[0],args1[1],args1[2],args1[3]);
			//printf("\n Path:%s args1 size:%d-%d-%d-%d \n",cmd,strlen(args1[0]),strlen(args1[1]),strlen(args1[2]),strlen(args1[3]));
            		execvp(cmd,args1);
            		perror("exec");
            		exit(1);
        	} else {                    //Parent
            	wait(NULL);
        	}
    }

    return 0;
}
