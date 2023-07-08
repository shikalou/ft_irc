/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:53:49 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/08 18:16:48 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"


void	Server::kill_cmd(std::map<int, Client *> client_list)
{
	Commands *fin = new Commands();
	fin->reponse.push_back("KILLING SERVER...\r\n");
	fin->sender_all(client_list);
	for (std::map<int, Client *>::iterator it = client_list.begin(); it != client_list.end(); ++it)
		server.deleteClient((*it).second);
	std::vector<Channel *>::iterator itchan = server._channels.begin();
	for (; itchan != server._channels.end(); ++itchan)
		delete *itchan;
	delete fin;
	server._end = 0;
}
