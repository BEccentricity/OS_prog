#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//#include <signal.h>
#include <limits.h>
#include <sys/time.h>
#pragma once

enum {

	error_404 = -1,
	timeout = 1,
	just_do_it = 2,
	max_len_fifo_name = 30,
	all_rdwr = 00666

};


void acceptor ();

void trasmitter_connection (int fd_trader);

void accept_file (int* fd_data);
