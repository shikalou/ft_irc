/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/14 18:54:52 by mcouppe          ###   ########.fr       */
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
	std::cout << "sock before accept :" << sock << std::endl;
	int fd_co = accept(sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	if (fd_co == -1){
		std::cerr << "accept issue : " << errno << std::endl;
		return (1);
	}
	std::cout << "sock after accept : " << sock << "fd_client = " << fd_co << std::endl;
	ev->data.fd = sock;
	ev->events = EPOLLIN;
	epoll_ctl(toto.epoll_fd, EPOLL_CTL_ADD, sock, ev);
	while (1)
	{
		int event = epoll_wait(toto.epoll_fd, ev, 5, 10000);
		std::cout << "event after epoll_wait : " << event << std::endl;
		if (event < 0)
		{
			std::cout << "event a eu un souci : " << errno << std::endl;
			return (1);
		}
		else if (event > 0)
		{
/*

		ici je fais exactement pareil que dans le man de epoll (cf https://manpages.ubuntu.com/manpages/focal/fr/man7/epoll.7.html)
		y'a juste une partie ou dans le man ils appellent une fonction pour mettre socket non blocking
		du coup j'ai remis les fcntl qui faisaient tout buguer en haut mais ca marche pas ni avec ni sans lol

		aussi, seconde diff avec le man : la structure ev il aime pas trop dc peut etre un pblm avec ca ?

*/

			for (int n = 0; n < event; ++n){
				if (ev[n].data.fd == sock){
					addrlen = sizeof(sockaddr);
					fd_co = accept(sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
					if (fd_co == -1){
						std::cerr << "ze kroi ke zé vu un grominet" << std::endl;
						return (1);
					}
		//			int flags = fcntl(fd_co, F_GETFL, 0);
		//			fcntl(fd_co, F_SETFL, flags | O_NONBLOCK);
					ev->events = EPOLLIN | EPOLLET;
					ev->data.fd = fd_co;
					if (epoll_ctl(sock, EPOLL_CTL_ADD, fd_co, ev) == -1){
						std::cerr << "error on epoll_ctl : fd_co" << std::endl;
						return (1);
					}
				}
				else {
					std::cout << "ici on doit utiliser fd ???" << std::endl;
					break;
				}
			}
/*			std::cout << "event = " << event << "    lol = " << ev->data.fd << std::endl;
			if (event == ev->data.fd)
				std::cout << "NOUVEAU CLIENT" << std::endl;
			else
			{
				std::cout << "COMMAND : " << std::endl;
				char toto1[4608];
//				int i = read(fd_co, toto1, 4608);
				read(fd_co, toto1, 4608);
				std::cout << "client : " << toto1 << std::endl;
				break;
			}*/
			// if (j == 0)
			// {
			// 	std::string str = "CAP * LS :";
			// 	j++;
			// 	send(fd_co, str.c_str(), str.length(), 0);
			// }
		}
	}

	std::string rep = "je reponds hihi ca va et toi\n";
	send(fd_co, rep.c_str(), rep.length(), 0);

	close(fd_co);
	close(sock);
}
