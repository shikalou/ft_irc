/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:25:21 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/29 11:50:29 by ldinaut          ###   ########.fr       */
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

		std::map<int, Client*>	_clients;

		void	parsing_cmd_co(std::string cmd, int clfd);
		int		set_clients_info(std::string cmd, Client *client);
		void	finish_connection(Client *client);
		void	accept_newclient(sockaddr_in sockaddr);
		void	add_epoll(int new_fd, int i);
		int		init_serv();
		int		run_serv();
	private:
		sockaddr_in	_sockaddr;
};

int	ft_error(std::string msg);

#endif
