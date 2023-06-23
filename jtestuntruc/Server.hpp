/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:25:21 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/19 00:02:14 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "Colors.hpp"
#include "Client.hpp"

# define EVENT_SIZE 1024

class Server
{
	public:
		Server(int port, std::string pass);
		~Server();

		int			sock;
		std::string	password;
		int			port;
		int			fd_co;
		int			epoll_fd; //epfd

		std::vector<Client*>	_clients;

		int		new_connection(void);
		int		client_request(int fd_main);
	//	void	new_connection(struct epoll_event ev, sockaddr_in sockaddr);
};

int	ft_error(std::string msg, int ret);
#endif