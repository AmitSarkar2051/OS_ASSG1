//#include<iostreamu>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<pwd.h>
//#include "al_map.h"
char _lalias[100][10];
char _ralias[100][50];
int _calias=0;


//using namespace std;
//
void bashrccreation(){
	char tar[]="mybashrc";
	FILE* fbrc =fopen(tar,"w");
        if(fbrc<0){
                printf("Error in target file open .  .. \n");
                return;
        }
	struct passwd *pwd = getpwuid(getuid());
       	char hst[100+1];
        gethostname(hst, sizeof(hst));	
	char sym='$';
	
	fprintf (fbrc,"user : %s\n", pwd->pw_name);
	fprintf (fbrc,"host : %s\n", hst);
	fprintf (fbrc,"HOME : %s\n", pwd->pw_dir);
	fprintf (fbrc,"PS1 : %c\n", sym);
	fprintf (fbrc,"PWD : %s\n", pwd->pw_name);
	fprintf (fbrc,"PATH : %s\n", pwd->pw_name);
	fclose(fbrc);
                /*struct passwd *pwd = getpwuid(getuid());  // Check for NULL!
                char* usr= pwd->pw_name;

                char hst[100+1];
                gethostname(hst, sizeof(hst));  // Check the return value!

                char sym[1]="$";
		  printf("%s\n",pwd->pw_dir);*/
	return;

};
void fappend_write(char* src,char* tar){
	//printf("\nSource:%s",src);
	//printf("\nTarget:%s",tar);
	 int f1 =open(src,O_RDONLY);
        if(f1<0){
                printf("Error in reading .  .. \n");
                return;
        }
        int f2 =open(tar,O_WRONLY|O_APPEND|O_CREAT,0777);
        //int f2 =open(tar,O_RDONLY | O_WRONLY | O_TRUNC);
        if(f2<0){
                printf("Error in target file open .  .. \n");
                return;
        }
        int r,w;
        char c;
        //printf("\nstart. .  . \n");
        while(r>0)
        {
                r=read(f1,&c,sizeof(c));
                write(f2,&c,sizeof(c));
        }
        //printf("\nEnd.   . . . . \n");
        return;
};
void fover_write(char* src,char* tar){
        printf("\nSource:%s",src);
        printf("\nTarget:%s",tar);

	int f1 =open(src,O_RDONLY);
	if(f1<0){
		printf("Error in reading .  .. \n");
		return;
	}
	//int f2 =open(tar,O_WRONLY|O_CREAT,0777);
	int f2 =open(tar,O_RDONLY | O_WRONLY | O_TRUNC|O_CREAT,0777);
	if(f2<0){
                printf("Error in target file open .  .. \n");
		return;
        }
	int r,w;
	char c;
	printf("\nstart. .  . \n");
	while(r>0)
	{
		r=read(f1,&c,sizeof(c));
		write(f2,&c,sizeof(c));
	}
	printf("\nEnd.   . . . . \n");
	return;
	
};
 char *lft;
   char* rht;
   char cln[100];

char* al_str_cleansing()
{
//	char* cln;
	int c=0;
	int d=0;
	while (rht[c] != '\0')
   	{
      	if (!(rht[c] == '=' || rht[c] == '"')) {
        	cln[d] = rht[c];
        d++;
      }
      c++;
   }

   cln[d] = '\0';
   //return *cln;
};
//=strtok(str,"=");
void al_arr_update(){
	strcpy(_lalias[_calias],lft);
        strcpy(_ralias[_calias],cln);
        _calias++;
}
void makealias(char* str){
	char line[100];
	strcpy(line,str);
        lft = strtok(line,"=");
        rht=strchr(str,'=');//=strtok(str,"=");
        //char* rht;
	//rht=n;
	char tar[]="mybashrc";
	printf("\nalias : %s \nleft:%s \nRight:%s \n",str,lft,rht);
	FILE* fbrc =fopen(tar,"a+");
        if(fbrc<0){
                printf("Error in target file open .  .. \n");
                return;
        }
	//fprintf (fbrc,"%s%s\n", lft,rht);
	al_str_cleansing();
	al_arr_update();
//	myprint(lft,rht);
	printf("\nalias : %s \nleft:%s \nRight:%s \n",str,_lalias[_calias-1],_ralias[_calias-1]);
	char e='=';
	fprintf (fbrc,"%s%c%s\n", lft,e,cln);
	fclose(fbrc);

};

int al_srch(char* s1){
	int i=0;
	int _f=-1;
	while(i <= _calias){
		if(strcmp(s1,_lalias[i])==0)
			_f=i;
		i++;
		
	}
	return  _f;
}
 
int main(){
	//for fgets
	char s[1024];
	//for getline()
	/*char *s;
	size_t s_size = 1024;
	s = (char *)malloc(s_size * sizeof(char));
    	if( s == NULL)
    	{
        	perror("Unable to allocate buffer");
        	exit(1);
    	}*/
	char* argv[100];
	char path[50];
	char cmd[1024];
//	char end[]="exit\n";
//	char stp[]="STOP";

	/* bashrc file creation*/
	bashrccreation();
	while(1){

		/**/

		struct passwd *pwd = getpwuid(getuid());  // Check for NULL!
		char* usr= pwd->pw_name;

		char hst[100+1];
		gethostname(hst, sizeof(hst));  // Check the return value!

		char sym='$';


		printf("\n%s@%s:%c",usr,hst,sym);
		/**/
		int flg=0;		
		//if(!getline(&s,&s_size,stdin))
		if(!fgets(s,1024,stdin))
			break;
		if(strcmp(s,"exit\n")==0)
                                break;
		char *p = strchr(s, '\n');
                if (p) *p = 0;

		 //strcat(s," STOP ");

    		/***************************

		char * prompt[4];
                prompt[0]="/bin/echo";
		prompt[1]="-n";
		prompt[2]="$(whoami)@$(hostname)$PWD";
		prompt[3]=(char*)0;
		execvp(prompt[0],prompt);
		 ****************************/
		char nouse[]="";
		char bin[]="/bin/";
		strcpy(cmd,bin);
		char line[1024];
		strcpy(line,s);
		char* s1=strtok(line," ");
		printf("\n *******************s1 val: %s\n",s1);
		int  _falias=al_srch(s1);
                     if(_falias > -1)
                            strcpy(s1,_ralias[_falias]);
		_falias=-1;
		     printf("\n s1 val: %s",s1);
		
		strcat(cmd,s1);
    
		// 2nd arg for execv args
		char * args1[100];
		/*int  _falias=al_srch(s1);
                     if(_falias > -1)
                            strcpy(s1,_ralias[_falias]);
			    */
	 printf("\nf val: %d\n",_falias);
		args1[0]=s1;
		int i=0;
		while (s1!= NULL)
  		{
    			
			
			if(s1[strlen(s1)-1] == '\n'){
				printf("\nMilgaya Enter . . . balleh balleh. .\n");
				return 0;
			}
			if(!strcmp(s1,"$HOME")){
				printf("%s\n",pwd->pw_dir);
				flg=1;
				break;
			}
			//printf("\nlast char:%c-chking",s1[strlen(s1)-1]);
			//if(strcmp(s1,stp)==0)
                           //     break;
			   if(!strcmp(s1,"alias")){
                                char* al=strtok(NULL,"\n");
                                makealias(al);
                                flg=1;
                                break;
                        }

			   //     overwrite >
			if(!strcmp(s1,">")){
				char* src=args1[i-1];
				char* tar=strtok(NULL," ");
				fover_write(src,tar);
				flg=1;
				break;
			}
			// append >>
			if(!strcmp(s1,">>")){
                                char* src=args1[i-1];
                                char* tar=strtok(NULL," ");
                                fappend_write(src,tar);
				flg=1;
				break;
                        }

    			s1 = strtok (NULL, " ");
			printf("\n********************** s1 val: %s\n",s1);
			if(s1!=NULL)
				_falias=al_srch(s1);
			if(_falias > -1)
				strcpy(s1,_ralias[_falias]);
				
			printf("\n**************************** s1 val: %s\n",s1);

			args1[++i]=s1;
			_falias=-1;
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
		if(flg==1)
			continue;
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
