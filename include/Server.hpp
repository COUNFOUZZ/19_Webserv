#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "Define.hpp"
#include "Request.hpp"

class Server {
	private:
		int 		_fd[2];
		int 		_port;
		std::string _host;
		Request*	_request;

		Server(void);

		class ErrorSocket : public std::exception {
			public:
				const char* what(void) const throw();
		};
		class ErrorBind : public std::exception {
			public:
				const char* what(void) const throw();
		};
		class ErrorAccept : public std::exception {
			public:
				const char* what(void) const throw();
		};

		void		_readRequest(void);

	public:
		Server(const int& port, const std::string& serverName);
		~Server(void);

		std::string	getServerName(void) const;
		int			getPort(void) const;
		int			getFdServer(void) const;
		int			getFdClient(void) const;
		void		setFdServer(const int& fd);
		void		setFdClient(const int& fd);

		void		startServer(void);
};

#endif