/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:14:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/29 11:49:46 by ldinaut          ###   ########.fr       */
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
}
