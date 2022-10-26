#include "Server.hpp"

#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <cerrno>

void	Server::socketHandle()
{
	errno = EAFNOSUPPORT;
	std::cerr << "Error: socket() failed..." << std::endl;
	std::cerr << std::strerror(errno) << std::endl;
	std::exit (1);
}

void	Server::setsockoptHandle()
{
	close(this->socketFd);
	std::cerr << "Error: setsockopt() failed..." << std::endl;
	std::cerr << std::strerror(errno) << std::endl;
	std::exit (1);
}

void	Server::ioctlHandle()
{
	close(this->socketFd);
	std::cerr << "Error: ioctl() failed..." << std::endl;
	std::cerr << std::strerror(errno) << std::endl;
	std::exit (1);
}

void	Server::bindHandle()
{
	close(this->socketFd);
	std::cerr << "Error: bind() failed..." << std::endl;
	std::cerr << std::strerror(errno) << std::endl;
	std::exit (1);
}

void	Server::listenHandle()
{
	close(this->socketFd);
	std::cerr << "Error: listen() failed..." << std::endl;
	std::cerr << std::strerror(errno) << std::endl;
	std::exit (1);
}

void	Server::acceptHandle()
{
	std::cerr << "Error: accept() failed..." << std::endl;
	std::cerr << std::strerror(errno) << std::endl;
	this->endServer = true;
}

void	Server::pollHandle()
{
	std::cerr << "Error: poll() failed..." << std::endl;
	std::cerr << std::strerror(errno) << std::endl;
	this->endServer = true;
}
