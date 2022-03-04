//pipe1a.cpp

//terminal: ./pipe1a ps auxw will print the exam same thing as pipe1

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>

using namespace std;
 
int main(int argc, char *argv[])
{
  FILE *fpi;               	//for reading a pipe

  char buffer[BUFSIZ+1];   	//BUFSIZ defined in <stdio.h>
  char terminal_command[BUFSIZ+1]; //terminal command ps auxw
  int chars_read;

  memset (buffer, 0,sizeof(buffer));  //clear buffer

  strcpy(terminal_command, argv[1]);

  for(int i = 2; i < argc; i++){ //2 = argv[1]
    strcat(terminal_command, " ");
    strcat(terminal_command, argv[i]);
  }


  fpi = popen (terminal_command, "r"); 	//pipe to command "ps auxw" the -auxw does not compile
  if (fpi != NULL) {
	//read data from pipe into buffer
	chars_read = fread(buffer, sizeof(char), BUFSIZ, fpi); 
	if (chars_read > 0)
 	cout << "Output from pipe: " << buffer << endl;
	pclose (fpi);          	//close the pipe
	return 0;
  }
 
  return 1;
}