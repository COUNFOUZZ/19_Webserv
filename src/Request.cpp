#include "../include/Request.hpp"

// Constructor / Destructor
Request::Request(const std::string& request) : _request(request) {
	this->_parseRequest();
	this->_requestHandling();
	// this->_requestHandling();
}

Request::~Request(void) {}

// Getters
std::string	Request::getRequest(void) const { return this->_request; }
std::string	Request::getResponse(void) const { return this->_response; }
std::string	Request::getMethod(void) const { return this->_method; }
std::string	Request::getPath(void) const { return this->_path; }
std::string	Request::getExtension(void) const { return this->_extension; }

// Private Methods
void	Request::_contentType() {
	std::string contentType("Content-Type: ");

	this->_response += contentType;
	if (this->_extension == ".html")
		this->_response += "text/html; charset=utf-8\n";
	else if (this->_extension == ".htm")
		this->_response += "text/html; charset=utf-8\n";
	else if (this->_extension == ".ico")
		this->_response += "image/x-icon\n";
}

void	Request::_requestHandling(void) {
	std::string	responseHeader("HTTP/1.1 200 OK\n");

	if (this->_method == "GET") {
		std::ifstream		file(this->_path.substr(1).c_str());
		std::string			body;
		std::stringstream	ss;

		if (!file.is_open()) {
			responseHeader = "HTTP/1.1 404 Not Found\nContent-Type: text/html; charset=utf-8\n";
			this->_response = responseHeader;
			file.open("404.html");		// not the final path !
			if (!file.is_open()) {
				this->_response += "Content-Length: 89\n\n<html><head><title>404 Not Found</title></head><body><h1>404 Not Found</h1></body></html>";
				return ;
			}
			std::string		line;
			while (std::getline(file, line))
				body += line;
			ss << body.size();
			this->_response += "Content-Length: " + ss.str() + "\n\n" + body;
		} else {
			this->_response = responseHeader;
			this->_contentType();
			std::string		line;
			while (std::getline(file, line))
				body += line;
			ss << body.size();
			this->_response += "Content-Length: " + ss.str() + "\n\n" + body;
		}
		file.close();
	}
}

void	Request::_parseRequest(void) {
	this->_method = this->_request.substr(0, this->_request.find(' '));
	this->_path = this->_request.substr(this->_request.find(' ') + 1, this->_request.find(' ', this->_request.find(' ') + 1) - this->_request.find(' ') - 1);
	this->_extension = this->_path.substr(this->_path.find_last_of('.'));
	std::cout << "Method: " << this->_method << std::endl;
	std::cout << "Path: " << this->_path << std::endl;
	std::cout << "Extension: " << this->_extension << std::endl;
}