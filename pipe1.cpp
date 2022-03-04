//pipe1.cpp 
/*
inout | command1 | command 2 | command 3 | terminal screen

man popen(), man pclose(), ,man ps
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
using namespace std;
 
int main()
{
  FILE *fpi;               	//for reading a pipe
 
  char buffer[BUFSIZ+1];   	//BUFSIZ defined in <stdio.h>
 
  int chars_read;
  memset (buffer, 0,sizeof(buffer));  //clear buffer
  fpi = popen ("ps auxw", "r"); 	//pipe to command "ps auxw" the -auxw does not compile
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