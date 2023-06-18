/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/18 18:34:07 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"
#include "Colors.hpp"

int	error_int(std::string msg){
	std::cerr << RED <<  msg << RESET << std::endl;
	return (1);
}
void	new_connection()
{

}

int main(int argc, char *argv[])
{
	if (argc != 3)
		return (error_int("./ircserv <port> <password>"));
	struct epoll_event ev[5];
	for (int h = 0; h < 5; h++)
		ev[h].data.fd = 0;

	Server toto(atoi(argv[1]), argv[2]);
	toto.epoll_fd = epoll_create1(0);

	toto.sock = socket(AF_INET, SOCK_STREAM, 0);
	// int flags = fcntl(toto.sock, F_GETFL, 0);
	// fcntl(toto.sock, F_SETFL, flags | O_NONBLOCK);
	if (toto.sock == -1)
		return (error_int("socket failed"));
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(toto.port);
		
	if (bind(toto.sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
		return (error_int("bind failed"));
	if (listen(toto.sock, 10) < 0)
		return (error_int("listen failed"));
	int addrlen = sizeof(sockaddr);
	int fd_co = accept(toto.sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	toto.fd_co = fd_co;
	ev->data.fd = toto.sock;
	ev->events = EPOLLIN;
	epoll_ctl(toto.epoll_fd, EPOLL_CTL_ADD, toto.sock, ev);
	while (1)
{	
		int event = epoll_wait(toto.epoll_fd, ev, 5, 10000);
		if (event < 0)
			return (error_int("Error: epoll_wait failed"));
		else if (event > 0)
		{
			for (int k = 0; k < 6; ++k)
			{
//		ici qd on est sur le event[5] est tres negatif vraiment un boloss
				std::cout << LAVENDER << "[LOG]\nevent = " << event << " event[" << k << "].data.fd = " << ev[k].data.fd << RESET << std::endl;
				if (toto.sock == ev[k].data.fd)
				{
					std::cout << GREEN << "[NOUVEAU CLIENT]" << RESET <<  std::endl;
					toto.new_connection(ev[k], sockaddr);
					write(fd_co, ":* NICK ldinaut", 12);
				}
				else if (ev[k].events == EPOLLIN)
				{
					std::cout << GREEN << "[COMMAND]" << RESET << std::endl;
					std::cout << LIGHT_BLUE << "[DEBUG]\nici le fd sur lequel on ecoute : " << ev[k].data.fd << RESET << std::endl;
					char toto1[1000];
					recv(ev[k].data.fd, toto1, 1000, MSG_DONTWAIT);
					std::string buffer(toto1);
					if (buffer.find("CAP LS") != std::string::npos)
						std::cout << ORANGE << "[INFO CLIENT]" << RESET << std::endl;
					std::cout << "client : " << toto1 << std::endl;
				}
			}
			// if (j == 0)
			// {
			// 	std::string str = "CAP * LS :";
			// 	j++;
			// 	send(fd_co, str.c_str(), str.length(), 0);
			// 
		}
	}

// 	std::string rep = "je reponds hihi ca va et toi\n";
// 	send(toto.fd_co, rep.c_str(), rep.length(), 0);

// 	close(toto.fd_co);
// 	close(toto.sock);
}
