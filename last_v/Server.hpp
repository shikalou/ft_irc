/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:25:21 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/18 15:52:18 by mcouppe          ###   ########.fr       */
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
#include <string.h>


#define RESET			"\033[0m"
#define ORANGE			"\033[30m"
#define ORANGE_B		"\033[1;30m"
#define RED				"\033[31m"
#define RED_B			"\033[1;31m"
#define GREEN			"\033[32m"
#define GREEN_B			"\033[1;32m"
#define	LAVENDER		"\033[33m"
#define	LAVENDER_B		"\033[1;33m"
#define LILAC			"\033[34m"
#define LILAC_B			"\033[1;34m"
#define LIGHT_BLUE		"\033[35m"
#define LIGHT_BLUE_B	"\033[1;35m"
#define LIGHT_PINK		"\033[36m"
#define LIGHT_PINK_B	"\033[1;36m"

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

		void	new_connection(struct epoll_event ev, sockaddr_in sockaddr);
};
