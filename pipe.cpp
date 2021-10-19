#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void read_from_pipe (int file) {

	FILE *stream;
	int c;
	stream = fdopen (file, 'r');
	while ((c = fgetc (stream)) != EOF)	putchar (c);
	fclose (stream);

}


void write_to_pipe (int file) {

	FILE *stream;
	stream = fdopen (file, 'w');
	fprintf (stream, 'Hello, world!\n');
	fprintf (stream, 'Hoodbye, world!\n');
	fclose (stream);

}

int main (int argc, char *argv[]) {
	
	pid_t pid;
	int my


    return 0;
}