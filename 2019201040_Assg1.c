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

//global var
char s[1024];
char* argv[100];
char path[50];
char cmd[1024];

char _lalias[100][10];
char _ralias[100][50];
int _calias=0;

int io=0;
int pip[2];


//functions
void pip_handle(char*);
void set_alarm(int);
void alarm_handle(int);
int al_srch(char*);
void makealias(char*);
void al_arr_update();
char* al_str_cleansing();
void fover_write(char*,char*);
void fappend_write(char*,char*);
void fappend_write_cmd(char*);
void show_history();
void clear_history();
void add_history(char*);
void bashrccreation();
void ext_parse(char *, char*, int);
void pip_exec(int , char**);

void ext_parse(char *s, char* tar, int ch)
{
		printf("\nEXT PARSE start with : ---%s--------------\n",s);
		char *p = strchr(s, '\n');
                if (p) *p = 0;
		printf("\nEXT PARSE start with : ---%s--------------\n",s);
		int i=0	;
		int flg=0;
		struct passwd *pwd = getpwuid(getuid());  // Check for NULL!
		char* usr= pwd->pw_name;
		char hst[100+1];
		gethostname(hst, sizeof(hst));  // Check the return value!
		char sym='$';	
		//char bin[]="/bin/";
		char bin[]="";
		strcpy(cmd,bin);
		char line[1024];
		char * args1[100];
		strcpy(line,s);
		printf("\nline in exPAr:----%s---\n",line);
		char* s1=strtok(line," ");
		printf("\n  In expar s1 val:-----%s-----\n",s1);
	
		int  _falias=al_srch(s1);
                if(_falias > -1){
			printf("\n . .. .. . %d.. . .. .\n",_falias);
			 char alline[100];
                         strcpy(alline,_ralias[_falias]);
			 char* als1=strtok(alline," ");
			  printf("\nOut while. ..  %d . .. %s\n",_falias,als1);
			 //args1[0]=als1;
			 s1=als1;
			 strcat(cmd,als1);
			 while(als1 != NULL){
			 	//als1 = strtok (NULL, " "i);
				printf("\nIn while. ..  %d . .. %s\n",i,als1);
				args1[i++]=als1;
			 	als1 = strtok (NULL, " ");
			 }
		
		}
		else if(_falias <= -1){
			strcat(cmd,s1);
		 	args1[i++]=s1;
		}
		_falias=-1;
		     printf("\n s1 val: %s",s1);
	 printf("\nf val: %d\n",_falias);
		while (s1!= NULL)
  		{
			if(!strcmp(s1,"$HOME")){
				printf("%s\n",pwd->pw_dir);
				flg=1;
				break;
			}
			   if(!strcmp(s1,"alias")){
                                char* al=strtok(NULL,"\n");
                                makealias(al);
                                flg=1;
                                break;
                        }
    			s1 = strtok (NULL, " ");
			printf("\n********************** s1 val: %s\n",s1);
			if(s1!=NULL)
				_falias=al_srch(s1);
			if(_falias > -1){
			
                	        printf("\n . .. .. . %d.. . .. .\n",_falias);
                        	char alline[100];
                         	strcpy(alline,_ralias[_falias]);
                         	char* als1=strtok(alline," ");
                          	printf("\nOut while. ..  %d . .. %s\n",_falias,als1);
                         	s1=als1;
                         	while(als1 != NULL){
                                //als1 = strtok (NULL, " "i);
                                	printf("\nIn while. ..  %d . .. %s\n",i,als1);
                                	args1[i++]=als1;
                                	als1 = strtok (NULL, " ");
                         	}

                

			}
			printf("\n**************************** s1 val: %s\n",s1);
			if(_falias <= -1){
                        	args1[i++]=s1;
	                }
                	_falias=-1;
		args1[i]=(char*)0;

		if(flg==1)
			continue;
        	int pid= fork();
		if(pid<0){
			printf("\nERROR: in pid\n");
			return ;
		}
	              //fork child
        	if(pid==0) {
			switch(ch)
			{
				case 1:
					// > overwrite implementation
					{
					printf("\nIN CASE 1\n");
					int f2 =open(tar,O_RDONLY | O_WRONLY | O_TRUNC|O_CREAT,0777);
        				if(f2<0){
                				printf("Error in target file open .  .. \n");
                				return;
        				}
					dup2(f2, STDOUT_FILENO);
				        close(f2);
					break;
					}
				case 2:
					{

					printf("\nIN CASE 2\n");
					// > append implementation
					int f2 =open(tar,O_WRONLY|O_APPEND|O_CREAT,0777);
        				if(f2<0){
                				printf("Error in target file open .  .. \n");
                				return;
        				}
					dup2(f2, STDOUT_FILENO);
				        close(f2);
					break;
					}
				case 3:
					{
					printf("\nIN CASE 3\n");
					//  implementation
					if(io!=0){
						dup2(io,0);
				        	close(io);
					}
					if(pip[1]!=1){
						dup2(pip[1],1);
				        	close(pip[1]);
					}
					break;
					}
				case 4:
					{
					printf("\nIN CASE 4\n");
					break;
					}
				default:
					break;


			}		
            		int ex = execvp(cmd,args1);
            		if(ex<0){
				perror("exec");
  	          		exit(1);
			}  
		      } else {                    //Parent
            			wait(NULL);
        			}
    }
    return ;
};

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
	char cwd[100+1];
	getcwd(cwd, sizeof(cwd));
	char sym='$';
	
	fprintf (fbrc,"user : %s\n", pwd->pw_name);
	fprintf (fbrc,"host : %s\n", hst);
	fprintf (fbrc,"HOME : %s\n", pwd->pw_dir);
	fprintf (fbrc,"PS1 : %c\n", sym);
	fprintf (fbrc,"PWD : %s\n", cwd);
	//fprintf (fbrc,"PATH : %s\n", pwd->pw_name);
	fclose(fbrc);
                /*struct passwd *pwd = getpwuid(getuid());  // Check for NULL!
                char* usr= pwd->pw_name;

                char hst[100+1];
                gethostname(hst, sizeof(hst));  // Check the return value!

                char sym[1]="$";
		  printf("%s\n",pwd->pw_dir);*/
	return;

};
//history maintain and retrieve
void add_history(char* s){
	//char his[]="/home/as2051/myhistory.txt";
	char his[]="myhistory.txt";
	FILE* fhis =fopen(his,"a+");
        if(fhis<0){
                printf("Error in History file open .  .. \n");
                return;
        }
        fprintf (fhis,"%s",s);
	fclose(fhis);
	return;
}
void clear_history(){
	char his[]="myhistory.txt";
        FILE* fhis =fopen(his,"w");
        if(fhis<0){
                printf("Error in History file open .  .. \n");
                return;
        }
        fclose(fhis);
        return;

}
void show_history(){
	char* his[5];
	his[0]="cat";
	his[1]="myhistory.txt";
	his[2]="-n";
	his[3]=(char*)0;
	int pid= fork();
        if(pid<0){
        	printf("\nERROR: in pid\n");
                return ;
        }
        //fork child
        if(pid==0) {
		printf("\n***************History till the last clean****************\n");
                 execvp("cat",his);
                 perror("exec");
                 exit(1);
	} 
	//Parent
	else {
              wait(NULL);
        }
}
void fappend_write_cmd(char* tar){

	/*int f2 =open(tar,O_WRONLY|O_APPEND|O_CREAT,0777);
        //int f2 =open(tar,O_RDONLY | O_WRONLY | O_TRUNC);
        if(f2<0){
                printf("Error in target file open .  .. \n");
                return;
        }
	*/	//string seperation
	char *f=s, *b=s;
	strsep(&b,">");
	printf("\nsep ..  . .. %s\n",f);
	ext_parse(f,tar,1);
	//free(f);
	//free(b);
    	return ;
}
void fover_write_cmd(char* tar){

	/*int f2 =open(tar,O_RDONLY | O_WRONLY | O_TRUNC|O_CREAT,0777);
        //int f2 =open(tar,O_RDONLY | O_WRONLY | O_TRUNC);
        if(f2<0){
                printf("Error in target file open .  .. \n");
                return;
        }*/
	char *f=s, *b=s;
	strsep(&b,">");
	printf("\nsep ..  . .. %s\n",f);
	ext_parse(f,tar,2);
	//free(f);
	//free(b);
	return;

}
void fappend_write(char* src,char* tar){
	printf("\nSource:%s",src);
	printf("\nTarget:%s",tar);
	 int f1 =open(src,O_RDONLY);
        if(f1<0){
                printf("Error in reading .  .. \n");
		fappend_write_cmd(tar);
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
		fover_write_cmd(tar);		
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
      	if (!(rht[c] == '=' || rht[c] == '"'|| rht[c] == '\'')) {
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
};
int repeat;
void alarm_handle(int sig) {
    //printf("\nALARM: ********** Hi ALARM Is Activated **************\n");
    if(--repeat){
    	alarm(1);
	printf("\nALARM: ********** Hi ALARM Is Activated **************\n");
    }
    else{
	    repeat=10;
	    exit(0);
    }
    //alarm(1);
    return ;
};
void set_alarm(int alarm_tm){
	signal(SIGALRM, alarm_handle);
    	alarm(alarm_tm);
    	while(repeat) 
		sleep(1);
    	printf("\nALARM: alarm stopped at %d. . . . .\n",alarm_tm);
    	return ;
};
void pip_exec(int x, char** pargs){
	int i=0;
	printf("============% d===========",x);
	for (i=0;i<(x-1);i++){
		pipe(pip);
	printf("===========*****=% d===========",i);
		ext_parse(pargs[i],NULL,3);
		close(pip[1]);
		io=pip[0];	
	}
	if((io!=0)&&(i==x-1))
		dup2(io,0);
	ext_parse(pargs[i],NULL,4);	
};
void pip_handle(char* s){
	printf("\n . .. .. . PIPE CALLED.. . .. .\n");
        char pline[1000];
	char* pargs[100];
        strcpy(pline,s);
	int i=0;
	char *f=s, *b=s;
	while(f!=NULL){
		strsep(&b,"|");
		printf("\nIn while. ..  . .. %s\n",f);
                pargs[i++]=f;
		f=b;
	}
	//free(f);
	//free(b);
	for(int j=0;j<i;j++)
		printf("\npipe arg %d: %s \n",j,pargs[j]);
	pip_exec(i,pargs);

	printf("\nPipe done . . .\n");
 	strcpy(s,"\n");
	return ;
};
 
int main(){
	//for fgets
	//char s[1024];
	//for getline()
	/*char *s;
	size_t s_size = 1024;
	s = (char *)malloc(s_size * sizeof(char));
    	if( s == NULL)
    	{
        	perror("Unable to allocate buffer");
        	exit(1);
    	}*/
//	char* argv[100];
//	char path[50];
//	char cmd[1024];
//	char end[]="exit\n";
//	char stp[]="STOP";

	/* bashrc file creation*/
	bashrccreation();
	while(1){

		/**/
		int i=0;
		struct passwd *pwd = getpwuid(getuid()); //user name
		char* usr= pwd->pw_name;

		char hst[100+1];
		gethostname(hst, sizeof(hst));//hostname/machine name
		
		char cwd[100+1];
		getcwd(cwd, sizeof(cwd));//pwd

		char sym='$';

		
		printf("\n%s@%s:~%s%c",usr,hst,cwd,sym);
		/**/
		int flg=0;	
		//fflush(stdin); 
		//fflush(stdout); 
		//if(!getline(&s,&s_size,stdin))
		// char s[1024];
		if(!fgets(s,1024,stdin))
			break;
		add_history(s); //history maintain
		char pip[]=" | ";
		char *pipfind = strstr(s, pip);
                if (pipfind) {
			pip_handle(s);
			flg=1;
		}
		if(strcmp(s,"\n")==0)
                                continue;
		if(strcmp(s,"exit\n")==0)
                                break;
		if(!strcmp(s,"history\n")){
                        show_history();
                        flg=1;
                }
		if(!strcmp(s,"clear history\n")){
                        clear_history();
                        flg=1;
                }

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
		//char bin[]="/bin/";
		char bin[]="";
		strcpy(cmd,bin);
		char line[1024];
		char * args1[100];
		strcpy(line,s);
		char* s1=strtok(line," ");
		printf("\n *******************s1 val: %s\n",s1);
		//cd implementation
		if(!strcmp(s1,"cd")){
			char* s2=strtok(NULL," ");
			int e= chdir(s2);
			if(e!=0){
				printf("ERROR: Unable to cd . Error %d",e);
			}
			printf("\nChanged the directory to %s",s2);
			flg=1;
                        continue;

		 }
		//ALARM
		if(!strcmp(s1,"alarm")){
				repeat=10;
                                char* alarm=args1[0]; //
                                char* alarm_tm=strtok(NULL," ");
				int alarm_tm_int=atoi(alarm_tm);
                                //int alarm_tm_int= (int)strtok(NULL," ");
				if(repeat>0)
					set_alarm(alarm_tm_int);
                                flg=1;
				repeat=0;
				fflush(stdin);
		                fflush(stdout);

				strcpy(s1,"x");
				continue;
                        }		
		
		int  _falias=al_srch(s1);
                if(_falias > -1){
			printf("\n . .. .. . %d.. . .. .\n",_falias);
			 char alline[100];
                         strcpy(alline,_ralias[_falias]);
			 char* als1=strtok(alline," ");
			  printf("\nOut while. ..  %d . .. %s\n",_falias,als1);
			 //args1[0]=als1;
			 s1=als1;
			 strcat(cmd,als1);
			 while(als1 != NULL){
			 	//als1 = strtok (NULL, " "i);
				printf("\nIn while. ..  %d . .. %s\n",i,als1);
				args1[i++]=als1;
			 	als1 = strtok (NULL, " ");
			 }
		
		}
		else if(_falias <= -1){
			strcat(cmd,s1);
		 	args1[i++]=s1;
		}
		_falias=-1;
		     printf("\n s1 val: %s",s1);
		
	//	strcat(cmd,s1);
    
		// 2nd arg for execv args
		//char * args1[100];
		/*int  _falias=al_srch(s1);
                     if(_falias > -1)
                            strcpy(s1,_ralias[_falias]);
			    */
	 printf("\nf val: %d\n",_falias);
		//args1[0]=s1;
		//int i=0;
		/*if(!strcmp(s1,"alarm")){
                                char* alarm=args1[0]; //
                                char* alarm_tm=strtok(NULL," ");
                                set_alarm(alarm_tm);
                                flg=1;
                               
                        }*/

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
				char* src=args1[i-2]; //token i -1
				char* tar=strtok(NULL," ");// token i+1
				fover_write(src,tar);
				flg=1;
				break;
			}
			// append >>
			if(!strcmp(s1,">>")){
                                char* src=args1[i-2];
                                char* tar=strtok(NULL," ");
                                fappend_write(src,tar);
				flg=1;
				break;
                        }

    			s1 = strtok (NULL, " ");
			printf("\n********************** s1 val: %s\n",s1);
			if(s1!=NULL)
				_falias=al_srch(s1);
			if(_falias > -1){
			
                	        printf("\n . .. .. . %d.. . .. .\n",_falias);
                        	char alline[100];
                         	strcpy(alline,_ralias[_falias]);
                         	char* als1=strtok(alline," ");
                          	printf("\nOut while. ..  %d . .. %s\n",_falias,als1);
                         	//args1[0]=als1;
                         	s1=als1;
                         	//strcat(cmd,als1);
                         	while(als1 != NULL){
                                //als1 = strtok (NULL, " "i);
                                	printf("\nIn while. ..  %d . .. %s\n",i,als1);
                                	args1[i++]=als1;
                                	als1 = strtok (NULL, " ");
                         	}

                

			}
			//	strcpy(s1,_ralias[_falias]);
				
			printf("\n**************************** s1 val: %s\n",s1);
			if(_falias <= -1){
                        	args1[i++]=s1;
	                }
                	_falias=-1;

			//args1[i++]=s1;
			//_falias=-1;
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
            		int ex = execvp(cmd,args1);
			if(ex<0){
            			perror("exec");
            			exit(1);
			}
        	} else {                    //Parent
            	wait(NULL);
        	}
    }

    return 0;
}
