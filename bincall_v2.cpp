#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>

using namespace std; 
int main(){
	string s,cmd;
	while(cmd!="exit"){
		getline(cin,cmd,' ');
		getline(cin,s);
		string path_tmp="/bin/"+cmd;
		//vector<string> vect;
		//const char *path=path_tmp;
		const char **argv= new const char* [s.size()+2];
		argv[0]=path_tmp;

		for (int j = 0;  j < s.size()+1;  ++j)     // copy args
            		argv [j+1] = s[j];
			
		argv [s.size()+1] = NULL;  
		//char* token=strlok(s," ");
		
		//char const* arg[]=s;
		//arg,NULL);
	//	int i=0;
	//	while(s[i]!=' ')
	//		strcat(cmd,s[i++]);
		int pid=fork();
		if(pid<0){
			cout<<"\nERRROR: Unable to call fork - "<<pid<<endl;
		}
		if(pid==0){
			//execvp("/bin/ls", const_cast<char**>(s));
			execv("/bin/ls",(char**)argv);
			cout<<endl<<path<<" has been esecuted.\n";
		}
		//cout<<endl<<pid<<":"<<path<<"-"<<s<<endl;

	}
	return 0;
}
