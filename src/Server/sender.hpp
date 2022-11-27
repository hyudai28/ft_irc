#ifndef SENDER_HPP
# define SENDER_HPP

#include <iostream>
#include <sys/socket.h>

ssize_t	shortSend(int fd, std::string msg);

#endif