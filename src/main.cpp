#include "../include/Webserv.hpp"

int main(int argc, const char **argv) {
	try {
		if (argc > 2)
			throw Webserv::ErrorNbrArg();
		else if (argc == 2) {
			Webserv webserv(argv[1]);
		} else {
			Webserv webserv;
			webserv.run();
		}
	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}