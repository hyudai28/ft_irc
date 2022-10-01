#include <iostream>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>

int	create_server(int port_num)
{
	int socket_fd;
	struct protoent *protocol_entry;
	sockaddr socket_addr;

	protocol_entry = getprotobyname("tcp");
	socket_fd = socket(AF_INET, SOCK_STREAM, protocol_entry->p_proto);


	//?



	bind(socket_fd, &socket_addr, sizeof(socket_addr));
	listen(socket_fd, 42);


	printf("access wait\n");
	socklen_t	socket_len;
	int			client_num;
	client_num = accept(socket_fd, &socket_addr, &socket_len);
	printf("access[%d]\n", client_num);
	exit(0);
}

int	listen_server()
{
	return (0);
}

int main(int argc, char **argv)
{
	int port_number;

	//if (argc >= 2)
	//{
		port_number = atoi(argv[1]);
		port_number = 6667;
		create_server(port_number);
		listen_server();
	//}
}