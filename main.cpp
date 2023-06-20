/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/20 17:52:11 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Commands.hpp"



int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		std::cout << "./ircserv <port> <password>" << std::endl;
		return (1);
	}
	struct epoll_event ev[5];
	for (int h = 0; h < 5; h++)
	{
		ev[h].data.fd = 0;
	}

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
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(toto.port);
		
	if (bind(toto.sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
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
	int fd_co = accept(toto.sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	toto.fd_co = fd_co;
	ev->data.fd = toto.sock;
	ev->events = EPOLLIN;
	epoll_ctl(toto.epoll_fd, EPOLL_CTL_ADD, toto.sock, ev);
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
				if (toto.sock == ev[k].data.fd)
				{
					std::cout << "NOUVEAU CLIENT" << std::endl;
					toto.new_connection(ev[k], sockaddr);
					std::vector<char>	buffer(4096);
					std::string			cmd;
					
					int ret = recv(fd_co, &buffer[0], 1000, MSG_DONTWAIT);
					if (ret == 0){
						std::cout << "[DISCONNECTED]" << std::endl;
						return (1);
					}
					std::cout << "\n\n\n\ncommand  ="<< &buffer[0] << std::endl << std::endl << std::endl << std::endl;
					cmd.append(buffer.cbegin(), buffer.cend());
					toto._clients = toto.parsing_cmd(cmd);
					std::string tmp_pass = "PASS " + toto._clients[0]->getPass() + "\n";
					std::string tmp_nick = ":* NICK " + toto._clients[0]->getNick() + "\n";
					std::string rpl_wel = "001 " + toto._clients[0]->getNick() + " :Welcome to the " + toto.network + " Network, " + toto._clients[0]->getNick() + "\n";
					std::string	rpl_yoh = "002 " + toto._clients[0]->getNick() + " :Your host is " + toto.network + ", running version 2.4\n";
					send(fd_co, tmp_pass.c_str(), tmp_pass.length(), 0);
					send(fd_co, tmp_nick.c_str(), tmp_nick.length(), 0);
					send(fd_co, rpl_wel.c_str(), rpl_wel.length(), 0);
					send(fd_co, rpl_yoh.c_str(), rpl_yoh.length(), 0);
				}
				else if (ev[k].events == EPOLLET)
				{
					std::cout << "COMMAND : " << std::endl;
					std::vector<char>	buffer(4096);
					std::string			cmd;
					int ret =recv(ev[k].data.fd, &buffer[0], 1000, MSG_DONTWAIT);
					if (ret == 0){
						std::cout << "[DISCONNECTED]" << std::endl;
						return (1);
					}
					std::cout << &buffer[0] << std::endl;
					cmd.append(buffer.cbegin(), buffer.cend());
					toto._clients = toto.parsing_cmd(cmd);
				}
				else
				{
					std::vector<char>	buffer(4096);
					int ret =recv(fd_co, &buffer[0], 1000, MSG_DONTWAIT);
					if (ret > 5){
						std::string	cmd_str;
						cmd_str.append(buffer.cbegin(), buffer.cend());
						Commands cmd(cmd_str); 
						cmd.launcher();
							
					}
						std::cout << "cmd maybe ???? = " << &buffer[0] << "\n";
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
