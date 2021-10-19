#include "transmitter.hpp"

#include "acceptor.hpp"




int main (int argc, char *argv[]) {

	if (argc == 2) {
		transmitter (argv[1]);
	}

	if (argc == 1) {
		acceptor ();
	}

	if (argc > 2) {

		fprintf (stderr, "Incorrect input");
		exit(1);
	}

	return 0;
}
