#include "../include/Webserv.hpp"

//  Constructors / Destructor
Webserv::Webserv(void) : _server(NULL), _pathConfigFile("./configs/default.conf") { this->_parseConfigFile();}
Webserv::Webserv(const std::string& path) : _server(NULL), _pathConfigFile(path) {
	if (this->_pathConfigFile.size() < 5 || this->_pathConfigFile.compare(this->_pathConfigFile.size() - 5, 5, ".conf"))
		throw BadExtensionConfFile();
}
Webserv::~Webserv(void) {
	if (this->_server)
		delete this->_server;
	this->_server = NULL;
}

//  Private Exceptions
const char* Webserv::FileCannotBeOpen::what(void) const throw() {
	return "Error: Impossible to open your file.";
}

const char* Webserv::BadExtensionConfFile::what(void) const throw() {
	return "Error: Your config file need to have .conf extension.";
}

const char* Webserv::ConfigFileServerSection::what(void) const throw() {
	return "Error: Your config file need to have a server section.";
}

const char* Webserv::ConfigFilePort::what(void) const throw() {
	return "Error: Your config file need to have a port in server section.";
}

const char* Webserv::ConfigFileServerName::what(void) const throw() {
	return "Error: Your config file need to have a server name in server section.";
}

const char* Webserv::lineMustEndWithSemicolon::what(void) const throw() {
	return "Error: Your config file need to have a semicolon at the end of the line.";
}

//  Public Exceptions
const char* Webserv::ErrorNbrArg::what(void) const throw() {
	return "Error: Launch webserv with \"./webserv\" or \"./webserv [config file]\".";
}

//  Private Methods
void	Webserv::_parseServerSection(std::ifstream& file, std::string& line, int& port, std::string& serverName) {
	if (line == "server {") {
		while (std::getline(file, line) && line != "}") {
			std::size_t found = 0;
			if (line[line.size() - 1] != ';')
				throw lineMustEndWithSemicolon();
			if ((found = line.find("listen")) != std::string::npos) {
				while (!isspace(line[found]) && found < line.size())
					++found;
				while (isspace(line[found]))
					++found;
				port = std::atoi(line.substr(found).c_str());
			} else if ((found = line.find("host")) != std::string::npos) {
				while (!isspace(line[found]) && found < line.size())
					++found;
				while (isspace(line[found]))
					++found;
				serverName = line.substr(found, line.size() - found - 1);
			}
		}
		if (line != "}")
			throw ConfigFileServerSection();
	}
}

void	Webserv::_parseConfigFile(void) {
	std::ifstream	file;
	std::string		line;

	file.open(this->_pathConfigFile.c_str());
	if (!file.is_open())
		throw FileCannotBeOpen();

	int 		port = 0;
	std::string serverName;

	while (std::getline(file, line)) {
		this->_parseServerSection(file, line, port, serverName);
		if (port == 0)
			throw ConfigFilePort();
		if (serverName.empty())
			throw ConfigFileServerName();
	}
	this->_server = new Server(port, serverName);
	std::cout << "Host = " << this->_server->getServerName() << std::endl;
	std::cout << "Port = " << this->_server->getPort() << std::endl;
}

//  Public Methods
void	Webserv::run(void) {
	this->_server->startServer();
}