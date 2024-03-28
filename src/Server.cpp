#include "../include/Server.hpp"

//  Constructors / Destructor
Server::Server(void) : _port(80), _host("localhost"), _request(NULL) {}
Server::Server(const int& port, const std::string& serverName) : _port(port), _host(serverName), _request(NULL) {}
Server::~Server(void) {
	if (this->_request)
		delete this->_request;
	this->_request = NULL;
	if (this->_fd[SERVER] != -1)
		close(this->_fd[SERVER]);
	if (this->_fd[CLIENT] != -1)
		close(this->_fd[CLIENT]);
}

//  Private Exceptions
const char* Server::ErrorSocket::what(void) const throw() {
	return "Error: Impossible to create a socket.";
}

const char* Server::ErrorBind::what(void) const throw() {
	return "Error: Impossible to bind the socket.";
}

const char* Server::ErrorAccept::what(void) const throw() {
	return "Error: Impossible to accept the connection.";
}

//  Getters
int			Server::getPort(void) const { return this->_port; }
std::string	Server::getServerName(void) const { return this->_host; }
int			Server::getFdServer(void) const { return this->_fd[SERVER]; }
int			Server::getFdClient(void) const { return this->_fd[CLIENT]; }

//  Setters
void		Server::setFdServer(const int& fd) { this->_fd[SERVER] = fd; }
void		Server::setFdClient(const int& fd) { this->_fd[CLIENT] = fd; }

//  Private Methods

void		Server::_readRequest(void) {
	std::string	contentClientRequest;
	char		buffer[1024];
	int			bytesRead = 1024, total = 0;

	while (bytesRead == 1024) {
		bzero(buffer, 1024);
		bytesRead = recv(this->_fd[CLIENT], buffer, sizeof(buffer), 0);
		if (bytesRead == -1) {
			close(this->_fd[CLIENT]);
			break;
		} else if (bytesRead == 0 && total == 0) {
			close(this->_fd[CLIENT]);
			break;
		} else
			total += bytesRead;
		contentClientRequest += buffer;
		if (bytesRead == 0)
			break;
	}
	std::cout << "Total bytes read: " << total << std::endl;
	this->_request = new Request(contentClientRequest);
}

//  Public Methods
void		Server::startServer(void) {
	struct sockaddr_in	serv_addr;

	this->_fd[SERVER] = socket(AF_INET, SOCK_STREAM, 0);
	if (this->_fd[SERVER] < 0)
		throw ErrorSocket();
	bzero((char*)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(this->_port);
	if (bind(this->_fd[SERVER], (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
		throw ErrorBind();
	listen(this->_fd[SERVER], 5);	// 5 is the maximum size of the queue of pending connections
	while (1) {
		std::cout << "\n+++++++ Waiting for new connection ++++++++\n\n";
		this->_fd[CLIENT] = accept(this->_fd[SERVER], NULL, NULL);
		if (this->_fd[CLIENT] < 0)
			throw ErrorAccept();
		this->_readRequest();
		if (this->_request)
			send(this->_fd[CLIENT], this->_request->getResponse().c_str(), this->_request->getResponse().size(), 0);
		close(this->_fd[CLIENT]);
	}
	close(this->_fd[SERVER]);
}