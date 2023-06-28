/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:25:21 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/28 15:49:43 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cerrno>
#include <cstddef>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <vector>
#include <map>
#include <utility>
#include "Channel.hpp"
#include "Colors.hpp"

#define NICK_TOOBIG "abcdefghijk"

class Client;

class Server
{
	public:
		Server(int port, std::string pass);
		~Server();

		int			sock;
		std::string	password;
		int			port;
		int			epoll_fd;
		int			fd_co;
		std::string	network;

		std::map<std::string, Client*>	_clients;

		// void	new_connection(struct epoll_event ev, sockaddr_in sockaddr);
		int	parsing_cmd_co(std::string cmd, struct epoll_event ev, sockaddr_in sockaddr, int mode, int clfd);
		void new_client(struct epoll_event ev, int k, sockaddr_in sockaddr);
		int	set_clients_info(std::string cmd, Client *client);
		void	finish_connection(Client *client);
		void	add_epoll(int new_fd, int i, sockaddr_in sockaddr);
};

int	ft_error(std::string msg);

#endif
