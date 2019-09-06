#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<vector>
using namespace std; 
int main(){
	string s,cmd;
	while(cmd!="exit"){
		cin>>cmd;
		vector<string> vect;
		vect.push_back(cmd);
		while(cin.get()=='\n'){

			cout<<"* :";
			cin>>cmd;
			vect.push_back(cmd);
		}
		for(int j = 0;  j < vect.size();  ++j)
			cout<<vect[j]<<endl;

		string path="/bin/ls";
		const char **argv = new const char* [vect.size()+2];   // extra room for program name and sentinel
    		argv [0] = vect[0].c_str();         // by convention, argv[0] is program name
    		for (int j = 0;  j < vect.size()+1;  ++j)     // copy args
            		argv [j+1] = vect[j] .c_str();
		for(int j = 0;  j < vect.size();  ++j)
			cout<<(*argv[j])<<endl;

		argv [vect.size()+1] = NULL;  // end of arguments sentinel is NULL
		//execv ("/bin/ls", (char **)argv);

	/*//	string path"/bin/"+cmd;
		//vector<string> vect;
		//const char *path=path_tmp;
		const char **argv= new const char* [s.size()+2];
		argv[0]=path_tmp;

		for (int j = 0;  j < s.size()+1;  ++j)     // copy args
            		argv [j+1] = s[j].;
			
		argv [s.size()+1] = NULL;
	      	 execv ("/bin/ls", (char **)argv);	
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
		//cout<<endl<<pid<<":"<<path<<"-"<<s<<endl;*/

	}
	return 0;
}
