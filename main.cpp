#include "Webserv.hpp"

int main(int argc, const char **argv) {
    try {
        if (argc > 2)
            throw Webserv::ErrorNbrArg();
        // Webserv webserv("Test.conf");
        Webserv test2(argv[1]);
        // Webserv test3;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}