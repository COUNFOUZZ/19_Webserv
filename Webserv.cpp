#include "Webserv.hpp"

//  Constructors / Destructor
Webserv::Webserv(void) : _pathDefaultConfFile("./configs/default.conf") {
    std::ifstream   file;

    file.open(this->_pathDefaultConfFile.c_str());
    if (!file.is_open())
        throw FileCannotBeOpen();
}

Webserv::Webserv(const Webserv& src) { *this = src; }
Webserv::Webserv(const std::string& path) : _pathDefaultConfFile(path) {
    if (this->_pathDefaultConfFile.size() < 5 || this->_pathDefaultConfFile.compare(this->_pathDefaultConfFile.size() - 5, 5, ".conf"))
        throw BadExtension();

    std::ifstream   file;
    
    file.open(this->_pathDefaultConfFile.c_str());
    if (!file.is_open())
        throw FileCannotBeOpen();
}

Webserv::~Webserv(void) {}

//  operator overload
Webserv&    Webserv::operator=(const Webserv& dest) {
    if (this == &dest)
        return *this;
    this->_pathDefaultConfFile = dest._pathDefaultConfFile;
    return *this;
}

//  Private Exceptions
const char* Webserv::FileCannotBeOpen::what(void) const throw() {
    return "Error: Impossible to open your config file.";
}

const char* Webserv::BadExtension::what(void) const throw() {
    return "Error: Your config file need to have .conf extension.";
}

//  Public Exceptions
const char* Webserv::ErrorNbrArg::what(void) const throw() {
    return "Error: Launch webserv with \"./webserv\" or \"./webserv [config file]\".";
}