#include <stdio.h>

 

void main(int argc, char *argv[], char * envp[])
//void main(char * envp[])

{

    int i;

 

    for (i = 0; envp[i] != NULL; i++)

    {
	//if(envp[i]=="HOME")    

        printf("\n%s", envp[i]);

    }

}
