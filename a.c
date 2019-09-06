#include<stdio.h>
#include<stdlib.h>
void printDir() 
{ 
    char cwd[1024]; 
    getcwd(cwd, sizeof(cwd)); 
    printf("\nDir: %s", cwd); 
} 
int main(){
	printDir();
return 0;
}
