#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
#include "Define.hpp"
#include "Server.hpp"

class Webserv {
	private:
		Server*		_server;
		std::string _pathConfigFile;

		class FileCannotBeOpen : public std::exception {
			public:
				const char* what(void) const throw();
		};
		class BadExtensionConfFile : public std::exception {
			public:
				const char* what(void) const throw();
		};
		class ConfigFileServerSection : public std::exception {
			public:
				const char* what(void) const throw();
		};
		class ConfigFilePort : public std::exception {
			public:
				const char* what(void) const throw();
		};
		class ConfigFileServerName : public std::exception {
			public:
				const char* what(void) const throw();
		};
		class lineMustEndWithSemicolon : public std::exception {
			public:
				const char* what(void) const throw();
		};

		void		_parseConfigFile(void);
		void		_parseServerSection(std::ifstream& file, std::string& line, int& port, std::string& serverName);
		void		_confFileErrorsHandling(void);

	public:
		Webserv(void);
		Webserv(const std::string& path);
		~Webserv(void);

		class ErrorNbrArg : public std::exception {
			public:
				const char* what(void) const throw();
		};

		void		run(void);
};

#endif