/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:01:28 by mcouppe           #+#    #+#             */
/*   Updated: 2023/06/19 00:52:01 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"
# include "Client.hpp"
/*
int	ft_error(std::string msg, int ret){
	std::cout << RED << msg << RESET << std::endl;
	return (ret);
}
*/
int	main(int ac, char **av){
	if (ac != 3)
		return (ft_error("wrong arg", 1));

// init serv
	Server serv(atoi(av[1]), av[2]);
	serv.sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv.sock == -1)
		return (ft_error("socket oups", 1));
	sockaddr_in	serv_addr;
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(serv.port);


// bind & listen
	if (bind(serv.sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		return (ft_error("bind oups", 1));
	if (listen(serv.sock, 5) < 0)
		return (ft_error("listen oups", 1));

	
// sockaddr et accept() du client
	sockaddr_in	cli_addr;
	int cli_len = sizeof(cli_addr);
	int sock_cli = accept(serv.sock, (struct sockaddr *)&cli_addr, (socklen_t*)&cli_len);
	if (sock_cli < 0)
		return (ft_error("accept sock cli oups", 1));

	
// epoll init
	struct epoll_event	ev[5];
	for (int i = 0; i < 5; i++)
		ev[i].data.fd = 0;
	serv.epoll_fd = epoll_create1(0);
	if (serv.epoll_fd < 0)
		return (ft_error("epoll_create oups", 1));
	/*	on peut remplacer epoll_create1(0) par epoll_create(EPOLL_QUEUE_LEN) qui serait le max number of connections descriptors allowed*/


//	epoll_ctl
	ev->events = EPOLLIN;
	ev->data.fd = sock_cli;
	int check_ctl = epoll_ctl(serv.epoll_fd, EPOLL_CTL_ADD, sock_cli, ev);
	if (check_ctl == -1)
		return (ft_error("epoll_ctl oups", 1));


// while(1) loop
	while (1){
		int nfds = epoll_wait(serv.epoll_fd, ev, 5, 1000);
		if (nfds < 0)
			return (ft_error("epoll_wait oups", 1));
		std::cout << LAVENDER << "[LOG]\tnfds = " << nfds << RESET << std::endl;
		for (int i = 0; i < 6; ++i){
			std::cout << LAVENDER << "[LOG]\tnfds = " << nfds << RESET << std::endl;
			int	fd_main = ev[i].data.fd;
			if ( fd_main == serv.sock){
				std::cout << ORANGE << "[NEW CLIENT INCOMING]" << RESET << std::endl;
				int new_sock_cli = serv.new_connection();
				if (new_sock_cli < 0)
					return (1);
			}
			if (ev[i].events == EPOLLIN){
				if (serv.client_request(fd_main) == -1)
					return (1);
			}
		}
	}
//	delete() with clients *it contained in serv
//	close all fds
	return (0);
}
