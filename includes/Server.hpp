/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:25:21 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/04 14:13:34 by mcouppe          ###   ########.fr       */
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
#include "ft_error.hpp"
#include "Colors.hpp"

#define NICK_TOOBIG "abcdefghijk"

class Client;
class Channel;

class Server
{
	public:
		Server();
		Server(int port, std::string pass);
		~Server();

		Server operator=(const Server *egal);

		int			sock;
		std::string	password;
		int			port;
		int			epoll_fd;
		int			fd_co;
		std::string	network;

		std::map<int, Client*>	_clients;
		std::vector<Channel *> _channels;

		void	accept_newclient(sockaddr_in sockaddr);
		void	add_epoll(int new_fd, int i);
		int		init_serv();
		int		run_serv();
		std::vector<Channel *> getChannel() const { return (_channels);}
	private:
		sockaddr_in	_sockaddr;
};

extern Server server;


#endif
