/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/10 00:08:01 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}
	struct epoll_event ev[5];

	Server toto(atoi(argv[1]), argv[2]);
	toto.epoll_fd = epoll_create1(0);

	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		std::cout << "socket failed" << std::endl;
		exit(1);
	}
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(toto.port);
		
	if (bind(sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
	{
		std::cout << "bind failed" << std::endl;
		exit (1);
	}
	if (listen(sock, 10) < 0)
	{
		std::cout << "listen failed" << std::endl;
		exit(1);
	}
	int addrlen = sizeof(sockaddr);
	int fd_co = accept(sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	ev->data.fd = sock;
	ev->events = EPOLLIN;
	epoll_ctl(toto.epoll_fd, EPOLL_CTL_ADD, sock, ev);
	send(fd_co, toto.password.c_str(), toto.password.length(), 0);
	while (1)
	{
		int event = epoll_wait(toto.epoll_fd, ev, 5, 10000);
		if (event < 0)
		{
			std::cout << "event a eu un souci : " << errno << std::endl;
			return (1);
		}
		else if (event > 0)
		{
			char toto1[4608];
			int i = read(fd_co, toto1, 4608);
			std::cout << "client : " << toto1 << std::endl;
		}
	}

	std::string rep = "je reponds hihi ca va et toi\n";
	send(fd_co, rep.c_str(), rep.length(), 0);

	close(fd_co);
	close(sock);
}