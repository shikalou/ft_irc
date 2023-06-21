/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:25:21 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/21 17:43:52 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <vector>
#include <map>
#include <utility>
#include "Client.hpp"

#define NICK_TOOBIG "abcdefghijk"

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
		std::map<std::string, Client*>	parsing_cmd_co(std::string cmd, struct epoll_event ev, sockaddr_in sockaddr);
		void	set_clients_info(std::string cmd, Client *client);
		void	finish_connection(Client *client);
};

int	ft_error(std::string msg);
