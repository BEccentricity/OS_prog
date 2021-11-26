#include "acceptor.hpp"




void acceptor () {

	int fd_data;
	int fd_trader;
	const char fifo_trader[] = "/tmp/fifo.trader";
	char fifo_data[max_len_fifo_name] = "/tmp/fifo.";
	sprintf(fifo_data + 10, "%d", getpid());

	if ((mkfifo(fifo_trader, 0666)) == -1 && errno != EEXIST) {
		perror ("mkfifo()");
		exit (error_404);
	}

	fd_trader = open (fifo_trader, O_WRONLY);
	if (fd_trader < 0) {
		perror("open()");
		exit(error_404);
	}

	if (mkfifo(fifo_data, 0666) < 0 && errno != EEXIST) {
		perror ("mkfifo()");
		exit (error_404);
	}

	fd_data = open(fifo_data, O_RDONLY | O_NDELAY);
	if (fd_data < 0 && errno != ENOENT) {
		perror("open()");
		exit (error_404);
	}

	//

	printf ("\n%s\n\n", fifo_data);

	printf ("creation fifo_trader success\n\n");

	trasmitter_connection (fd_trader);

	printf ("success connection\n\n");

	//sleep(1);

	accept_file (&fd_data);

	if (close(fd_trader) < 0){
		perror("close()");
		exit(error_404);
	}


	if (close(fd_data) < 0){
		perror("close()");
		exit(error_404);
	}

	printf ("\nacceptor has finished\n\n");
}

void trasmitter_connection (int fd_trader) {
	pid_t pid_acceptor = getpid();
	if (write(fd_trader, &pid_acceptor, sizeof(pid_t)) < 0) {
		perror("write()");
		exit(error_404);
	}
}

void accept_file (int* fd_data) {
	fd_set nfds;
	struct timeval waiting = {timeout, 0};
	int select_res;

	FD_ZERO (&nfds);
	FD_SET (*fd_data, &nfds);

	select_res = select (*(fd_data) + 1, &nfds, NULL, NULL, &waiting);

	switch (select_res) {
		case 0:
			fprintf (stderr, "trasmitter was killed\n");
			return;
		case -1:
			perror ("select()");
			exit(error_404);
		default:;
	}
	
	if (fcntl(*fd_data, F_SETFL, O_RDONLY)) {
		perror("fcntl()");
		exit(error_404);
	}

	while(just_do_it) {
		ssize_t len = splice (*fd_data, NULL, STDOUT_FILENO, NULL, PIPE_BUF, SPLICE_F_MOVE);
		if (len < 0) {
			perror("splice()");
			exit(error_404);
		}

		if (len == 0) {
			break;
		}
	}
}

