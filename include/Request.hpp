#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

class Request {
	private:
		std::string _request;
		std::string _method;
		std::string _path;
		std::string _extension;
		std::string _response;

		Request(void);

		void		_parseRequest(void);
		void		_requestHandling(void);
		void		_contentType(void);

	public:
		Request(const std::string& request);
		~Request(void);

		std::string	getRequest(void) const;
		std::string	getResponse(void) const;
		std::string	getMethod(void) const;
		std::string	getPath(void) const;
		std::string	getExtension(void) const;
};

#endif