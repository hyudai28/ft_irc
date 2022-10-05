#ifndef SERVER_HPP
# define SERVER_HPP

class Server
{
	private:
		int	port;
		int	socket_fd;
	public:
		Server();
		~Server();

		void	server_start(int port);

		int		get_port();
};

#endif /* SERVER_HPP */
