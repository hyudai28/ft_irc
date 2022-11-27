#include "sender.hpp"

ssize_t	shortSend(int fd, std::string msg)
{
	ssize_t s;
	s = send(fd, msg.c_str(), msg.length(), 0);
	return s;
}