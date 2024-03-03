#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

class Webserv {
    private:
        std::string _pathDefaultConfFile;

        class FileCannotBeOpen : public std::exception {
            public:
                const char* what(void) const throw();
        };
        class BadExtension : public std::exception {
            public:
                const char* what(void) const throw();
        };
    public:
        Webserv(void);
        Webserv(const Webserv& src);
        Webserv(const std::string& path);
        ~Webserv(void);

        Webserv&    operator=(const Webserv& dest);

        class ErrorNbrArg : public std::exception {
            public:
                const char* what(void) const throw();
        };
};

#endif