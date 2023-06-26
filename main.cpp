/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/26 19:18:02 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Commands.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3)
		return (ft_error(" usage [./ircserv <port> <password>]"));
	struct epoll_event ev[5];
	memset(&ev, 0, sizeof(ev));

	Server toto(atoi(argv[1]), argv[2]);
	toto.epoll_fd = epoll_create1(0);

	toto.sock = socket(AF_INET, SOCK_STREAM, 0);
	int	opt = 1;
	if (setsockopt(toto.sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		std::cout << "ERROR SETSOCKOPT loooool\n";
		exit(0);
	}
	// int flags = fcntl(toto.sock, F_GETFL, 0);
	int flags = fcntl(toto.sock, F_GETFL, O_NONBLOCK);
	if (flags == -1)
	{
		std::cout << "ERRRRRORORR IN fcntl looll\n\n\n";
		exit (0);
	}
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
	ev->events = (EPOLLIN | EPOLLRDHUP);
	epoll_ctl(toto.epoll_fd, EPOLL_CTL_ADD, toto.sock, ev);
	//std::cout << "toto sock = " << toto.sock << " ev et tout = " << ev[0].data.fd << std::endl<< std::endl<< std::endl;
	while (1)
	{	
		int event = epoll_wait(toto.epoll_fd, ev, 5, -1);
		if (event < 0)
			return (ft_error(std::string(strerror(errno))));
		for (int k = 0; k < event; k++)
		{
			if (toto.sock == ev[k].data.fd)
			{
				std::cout << "NOUVEAU CLIENT" << std::endl;
				std::vector<char>	buffer(4096);
				std::string			cmd;
				
				toto.parsing_cmd_co(cmd, ev[k], sockaddr, 1, 0);
				int ret = recv(fd_co, &buffer[0], 1024, MSG_DONTWAIT);
				if (ret == 0)
				 	return (ft_error("[DISCONNECTED"));
				std::cout << "\n\n\n\ncommand  ="<< &buffer[0] << std::endl << std::endl << std::endl << std::endl;
				cmd.append(buffer.begin(), buffer.end());
				toto.parsing_cmd_co(cmd, ev[k], sockaddr, 2, ev[k].data.fd);

			}
			else if (ev[k].data.fd)
			{
				std::vector<char>	buffer(4096);
				int ret =recv(fd_co, &buffer[0], 1024, MSG_DONTWAIT);
				if (ret > 5)
				{
					std::string	cmd_str;
					cmd_str.append(buffer.begin(), buffer.end());
					Commands cmd(cmd_str, fd_co); 
					cmd.launcher();
				}
			}
		}
	}

// 	std::string rep = "je reponds hihi ca va et toi\n";
// 	send(toto.fd_co, rep.c_str(), rep.length(), 0);

// 	close(toto.fd_co);
// 	close(toto.sock);
}
