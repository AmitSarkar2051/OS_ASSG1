#include<iostream>
#include<stdlib.h>
#include<unistd.h>
#include<wait.h>
#include<sys/types.h>
#include<unistd.h>

using namespace std; 
int main(){
	string s,cmd;
	while(cmd!="exit"){
		//string cmd;
		//cin>>cmd;
		//char* arg;
		getline(cin,cmd,' ');
		getline(cin,s);
		string path="/bin/"+cmd;
		//char const *path={"/bin/",cmd}
		//char const *arg[]={s,NULL};
		char const* arg[]=s;
		//arg,NULL);
	//	int i=0;
	//	while(s[i]!=' ')
	//		strcat(cmd,s[i++]);
		int pid=fork();
		if(pid<0){
			cout<<"\nERRROR: Unable to call fork - "<<pid<<endl;
		}
		if(pid==0){
			execvp("/bin/ls", const_cast<char**>(arg));

			//cout<<endl<<path<<" has been esecuted.\n";
		}
		//cout<<endl<<pid<<":"<<path<<"-"<<s<<endl;

	}
	return 0;
}
