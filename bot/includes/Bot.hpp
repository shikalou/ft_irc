/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:15:04 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/08 16:42:38 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOT_HPP
#define BOT_HPP

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
#include <signal.h>


class Bot
{
	public:
		Bot() { _end = true;};
		Bot(int port, std::string pass);
		~Bot();

		Bot	operator=(Bot egal)
		{
			_port = egal._port;
			_pass = egal._pass;
			epoll_fd = egal.epoll_fd;
			_end = egal._end;
			sock = egal.sock;
			fd_co = egal.fd_co;
			jokes = egal.jokes;
			_sockaddr = egal._sockaddr;
			return (*this);
		}

		int		init_bot();
		void	run();
		void	add_epoll(int new_fd, int i);
		void	log_to_serv();
		void	fill_tab();
		void	send_mess(std::string str);

		int		epoll_fd;
		bool	_end;
		int		sock;
		int		fd_co;
		std::vector<std::string>	jokes;

		sockaddr_in _sockaddr;
	private:
		int			_port;
		std::string	_pass;
};

extern Bot bot;

#endif
