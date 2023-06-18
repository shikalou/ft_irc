/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:25:21 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/14 16:46:16 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <cstdint>
#include <cstddef>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

class Server
{
	public:
		Server(int port, std::string pass);
		~Server();

		std::string	password;
		int			port;
		int			epoll_fd;
};
