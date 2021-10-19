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
#pragma once


void transmitter (char* path);

void acceptor_connection (char* fifo_data,  int fd_trader, pid_t* pid_acceptor);

void trasmit_file (int* fd_file, int* fd_data);