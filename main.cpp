/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/28 17:09:43 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Commands.hpp"

int main(int argc, char *argv[])
{
	if (argc != 3)
		return (ft_error(" usage [./ircserv <port> <password>]"));

	Server toto(atoi(argv[1]), argv[2]);
	
	if (toto.init_serv())
		return (1);
	toto.run_serv();
	// toto.epoll_fd = epoll_create1(0);

	// toto.sock = socket(AF_INET, SOCK_STREAM, 0);
	// int	opt = 1;
	// if (setsockopt(toto.sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	// {
	// 	std::cout << "ERROR SETSOCKOPT loooool\n";
	// 	exit(0);
	// }
	// if (toto.sock == -1)
	// 	return (ft_error("socket failed"));
	// sockaddr_in sockaddr;
	// sockaddr.sin_family = AF_INET;
	// sockaddr.sin_addr.s_addr = INADDR_ANY;
	// sockaddr.sin_port = htons(toto.port);
		
	// if (bind(toto.sock, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0)
	// 	return (ft_error("bind failed"));
	// if (listen(toto.sock, 5) < 0)
	// 	return (ft_error("listen failed"));
	// // int fd_co = accept(toto.sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen);
	// int flags = fcntl(toto.sock, F_GETFL, O_NONBLOCK);
	// if (flags == -1)
	// {
	// 	std::cout << "ERRRRRORORR IN fcntl looll\n\n\n";
	// 	exit (0);
	// }
	// toto.add_epoll(toto.sock, 1);
	// while (1)
	// {	
	// 	int event = epoll_wait(toto.epoll_fd, ev.data(), 5, 1000);
	// 	if (event < 0)
	// 		return (ft_error(std::string(strerror(errno))));
	// 	for (int k = 0; k < event; k++)
	// 	{
	// 		if (toto.sock == ev[k].data.fd)
	// 		{
	// 			std::cout << "NOUVEAU CLIENT" << std::endl;
	// 			toto.accept_newclient(sockaddr);
	// 		}
	// 		else if (ev[k].data.fd)
	// 		{
	// 			std::vector<char>	buffer(4096);
	// 			int ret;
	// 			if ((ret = recv(ev[k].data.fd, &buffer[0], 4096, MSG_DONTWAIT)) <= 0)
	// 			{
	// 				ft_error("error recv\n");
	// 				continue ;
	// 			}
	// 			std::string	cmd_str(&buffer[0], ret);
	// 			Commands cmd(cmd_str, ev[k].data.fd);
				
	// 			cmd.launcher();
	// 			// std::size_t found;
	// 			// found = cmdtest.find("CAP");
	// 			// if (found != std::string::npos && (found == 0))
	// 			// {
	// 			// 	std::cout << cmdtest << "\n";
	// 			// 	toto.parsing_cmd_co(cmdtest, ev[k].data.fd);
	// 			// }
	// 		}
	// 	}
	// }

// 	close(toto.fd_co);
// 	close(toto.sock);
}
