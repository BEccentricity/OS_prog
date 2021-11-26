#include "transmitter.hpp"

#include "acceptor.hpp"




int main (int argc, char *argv[]) {

	for (int i = 0; i < 50; ++i) {
		execvp (argv[1], argv + 1);
	}



	return 0;
}
