/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/07 20:33:12 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Commands.hpp"

Server server;

int main(int argc, char *argv[])
{
	if (argc != 3)
		return (ft_error(" usage [./ircserv <port> <password>]"));
	server = Server(atoi(argv[1]), argv[2]);
	if (server.init_serv())
		return (1);
	// server.initBot();
	server.run_serv();
}
