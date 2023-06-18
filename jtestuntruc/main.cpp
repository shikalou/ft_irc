/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 19:01:28 by mcouppe           #+#    #+#             */
/*   Updated: 2023/06/18 19:24:54 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

int	error(std::string msg){
	std::cout << RED << msg << RESET << std::endl;
	return (1);
}

int	main(int ac, char **av){
	if (ac != 3)
		return (error("wrong arg"));

// init serv

	Server serv(atoi(av[1]), av[2]);
	serv.sock = socket(AF_INET, SOCK_STREAM, 0);
	if (serv.sock == -1)
		return (error("socket oups"));
	sockaddr_in	serv_addr;
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(serv.port);
	if (bind(serv.sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
		return (error("bind oups"));

//	voir retour de listen...
	listen(serv.sock, 5);
	
// sockaddr et accept() du client
	sockaddr_in	cli_addr;
	int cli_len = sizeof(cli_addr);
	int sock_cli = accept(serv.sock, (struct sockaddr *)&cli_addr, (socklen_t*)&cli_len);
	if (sock_cli < 0)
		return (error("accept sock cli oups"));
	

//	buffer reading
	char	buffer[600];
	bzero(buffer, 600);
	int check = read(sock_cli, buffer, 600);
	if (check < 0)
		return (error("reading socket oups"));
	std::cout << GREEN << "buffer is : \n" << buffer << RESET << std::endl;
	return (0);
}
