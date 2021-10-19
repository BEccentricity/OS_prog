#include "transmitter.hpp"
#include "acceptor.hpp"


void transmitter (char* path) {

	pid_t pid_acceptor = 0;
	int fd_trader;
	int fd_file;
	int fd_data;
	const char fifo_trader[] = "/tmp/fifo.trader";
	char fifo_data[max_len_fifo_name] = "/tmp/fifo.";

	fd_file = open (path, O_RDONLY);
	if (fd_file < 0) {
		perror ("open()");
		exit (error_404);
	}

	printf ("file open success\n\n");

	if((mkfifo(fifo_trader, 0666)) == -1 && errno != EEXIST) {
		perror ("mkfifo()");
		exit (error_404);
	}

	fd_trader = open(fifo_trader, O_RDONLY);
	if (fd_trader < 0) {
		perror ("open()");
		exit (error_404);
	}


	printf("creation fifo_trader success\n\n");

	acceptor_connection (fifo_data, fd_trader, &pid_acceptor);

	printf ("success connection\n\n");


	if (mkfifo(fifo_data, 0666) < 0 && errno != EEXIST) {
		perror ("mkfifo()");
		exit (error_404);
	}

	printf ("%s\n\n", fifo_data);

	fd_data = open (fifo_data, O_WRONLY | O_NDELAY);
	if (fd_data < 0) {
		perror("open()");
		exit (error_404);
	}


	trasmit_file (&fd_file, &fd_data);

	if (close(fd_trader) < 0){
		perror("close()");
		exit(error_404);
	}

	if (close(fd_data) < 0){
		perror("close()");
		exit(error_404);
	}

	if (close(fd_file) < 0){
		perror("close()");
		exit(error_404);
	}

	printf ("trasmitter has finished\n\n");

}


void  acceptor_connection (char* fifo_data,  int fd_trader, pid_t* pid_acceptor) {

	if(read (fd_trader, pid_acceptor, sizeof(pid_t)) < 0) {
		perror ("read()");
		exit (error_404);
	}

	if (*pid_acceptor == 0) {
		fprintf(stderr, "acceptor not available\n");
		exit(error_404);
	}

	sprintf (fifo_data + 10, "%d", *pid_acceptor);
}


void trasmit_file (int* fd_file, int* fd_data) {

	if (fcntl(*fd_data, F_SETFL, O_WRONLY)) {
		perror("fcntl()");
		exit(error_404);
	}

	while (just_do_it) {
		ssize_t len = splice (*fd_file, NULL, *fd_data, NULL, PIPE_BUF, SPLICE_F_MOVE);
		if (len < 0 ) {
			perror ("splice()");
			exit (error_404);
		}

		if (len == 0) break;
	}

}