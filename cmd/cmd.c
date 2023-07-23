#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_SIZE 256

bool get_command(char * str) {

	int symbol;                                                                
  	int i = 0;                                                            
  	while ((symbol = getchar()) != '\n') {  

    	if (i < STR_SIZE - 1){                                              
	      str[i] = symbol;                                             
	      i++;                                                          
	    } else {     

	     return false;                                                                                   
	    }
	  }                                                                 
	                                                         
	str[i]='\0';

	return true;

}

void stok(char **cmd, char * p_str, char * sep) {

	cmd[0] = p_str;
   	
   	int i = 1;
   	while ( p_str != NULL)
   	{
      	p_str = strtok (NULL, sep);
      	cmd[i] = p_str;
      	i++;
   	}
}

int main() {

	printf("Enter the command: \n");

	char str[STR_SIZE];
	char cmd_way[STR_SIZE] = "/bin/";

	if(get_command(str) == false) {
		
		printf("The command is full\n"); 
	    exit(1);
	}
  
	char *sep = " ";
   	char *p_str = strtok(str, sep);
   	strcat(cmd_way, p_str);

   	char *cmd[STR_SIZE];
   	stok(cmd, p_str, sep);

   	pid_t pid;
   	int status;

	pid = fork();

	if (pid == -1){

		perror("Fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0){

		execv(cmd_way, cmd);
		exit(EXIT_SUCCESS);
	}
	else {

		wait(&status);
		//printf("status = %d\n", WEXITSTATUS(status));
	}
	
   	exit(EXIT_SUCCESS);
}