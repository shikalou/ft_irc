/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/17 20:25:49 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	new_connection()
{

}

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

	toto.sock = socket(AF_INET, SOCK_STREAM, 0);
	// int flags = fcntl(toto.sock, F_GETFL, 0);
	// fcntl(toto.sock, F_SETFL, flags | O_NONBLOCK);
	if (toto.sock == -1)
	{
		std::cout << "socket failed" << std::endl;
		exit(1);
	}
	sockaddr_in sockaddr_serv;
	sockaddr_serv.sin_family = AF_INET;
	sockaddr_serv.sin_addr.s_addr = INADDR_ANY;
	sockaddr_serv.sin_port = htons(toto.port);
		
	if (bind(toto.sock, (struct sockaddr*)&sockaddr_serv, sizeof(sockaddr)) < 0)
	{
		std::cout << "bind failed" << std::endl;
		exit (1);
	}
	if (listen(toto.sock, 10) < 0)
	{
		std::cout << "listen failed" << std::endl;
		exit(1);
	}

	int addrlen = sizeof(sockaddr);
	int fd_co = accept(toto.sock, (struct sockaddr*)&sockaddr_serv, (socklen_t*)&addrlen);
	if (fd_co < 0)
		std::cout << ORANGE << "first accept failed" << RESET << std::endl;
	toto.fd_co = fd_co;
	ev->data.fd = toto.sock;
	ev->events = EPOLLIN;
	epoll_ctl(toto.epoll_fd, EPOLL_CTL_ADD, toto.sock, ev);
	int j = 0;
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
			for (int k = 0; k < 6; ++k)
			{
				std::cout << "event = " << event << "    lol = " << ev[k].data.fd << std::endl;
				if (toto.sock == ev[k].data.fd)
				{
					std::cout << LIGHT_BLUE << "NOUVEAU CLIENT" << std::endl;
					char toto1[4608];
					recv(toto.fd_co, toto1, 4608, MSG_DONTWAIT);
					std::cout << "client dans new : " << toto1 << RESET << std::endl;
					toto.new_connection(ev[k], sockaddr_serv);
				}
				else if (ev[k].events)
				{
					std::cout << ORANGE << "COMMAND :  with : " << ev[k].data.fd << std::endl;
					char toto1[1000];
					recv(ev[0].data.fd, toto1, 1000, MSG_DONTWAIT);
					std::cout << "client : " << toto1 << RESET << std::endl;
				//	parse_received(toto1);
				}
			}
			// if (j == 0)
			// {
			// 	std::string str = "CAP * LS :";
			// 	j++;
			// 	send(fd_co, str.c_str(), str.length(), 0);
			// }
		}
	}

// 	std::string rep = "je reponds hihi ca va et toi\n";
// 	send(toto.fd_co, rep.c_str(), rep.length(), 0);

// 	close(toto.fd_co);
// 	close(toto.sock);
}