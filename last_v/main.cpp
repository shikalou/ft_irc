/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/26 19:57:58 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Commands.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3)
		return (ft_error(" usage [./ircserv <port> <password>]"));
	struct epoll_event ev[5];
	for (int h = 0; h < 5; h++)
		ev[h].data.fd = 0;

	Server toto(atoi(argv[1]), argv[2]);
	toto.epoll_fd = epoll_create1(0);

	toto.sock = socket(AF_INET, SOCK_STREAM, 0);
	// int flags = fcntl(toto.sock, F_GETFL, 0);
	// fcntl(toto.sock, F_SETFL, flags | O_NONBLOCK);
	if (toto.sock == -1)
		return (ft_error("socket failed"));
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(toto.port);
		
	if (bind(toto.sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
		return (ft_error("bind failed"));
	if (listen(toto.sock, 10) < 0)
		return (ft_error("listen failed"));
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
			return (ft_error(std::string(strerror(errno))));
		else if (event > 0)
		{
			for (int k = 0; k < 6; ++k)
			{
				if (toto.sock == ev[k].data.fd)
				{
					std::cout << "NOUVEAU CLIENT" << std::endl;
			//		char	*buffer = NULL;
					std::vector<char>	buffer(4096);
					std::string			cmd;
					
					int ret = recv(fd_co, &buffer[0], 1000, MSG_DONTWAIT);
					if (ret == 0)
						return (ft_error("[DISCONNECTED"));
					std::cout << "\n\n\n\ncommand  ="<< &buffer[0] << std::endl << std::endl << std::endl << std::endl;
			//		std::string	cmd(buffer);
					cmd.append(buffer.begin(), buffer.end());
					toto._clients = toto.parsing_cmd_co(cmd, ev[k], sockaddr);
				}
				else if (ev[k].events == EPOLLET)
				{
					std::cout << "COMMAND : " << std::endl;
		//			char	*buffer = "" ;
					std::vector<char>	buffer(4096);
					int ret =recv(ev[k].data.fd, &buffer[0], 1000, MSG_DONTWAIT);
					if (ret == 0)
						return (ft_error("[DISCONNECTED]"));
					std::cout << &buffer[0] << std::endl;
					std::string	cmd;
					cmd.append(buffer.begin(), buffer.end());
				//	mais jcomprends pas on en fait quoi derriere ??
				}
				else
				{
					std::vector<char>	buffer(4096);
//	fo turn to char*
					int ret =recv(fd_co, &buffer[0], 1000, MSG_DONTWAIT);
					if (ret > 5){
						std::string	cmd_str;
						cmd_str = string_creator(buffer, ret);
						Commands cmd(cmd_str, fd_co); 
						cmd.launcher();
							
					}
					//	std::cout << "cmd maybe ???? = " << &buffer[0] << "\n";
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
