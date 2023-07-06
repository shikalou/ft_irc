/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:53:49 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/06 18:29:40 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"

std::vector<std::string>	Commands::kill_cmd(Client *client)
{
	(void)client;
	return (reponse);
}


// std::vector<std::string>	Commands::kill_cmd2(std::map<int, Client *> client_list, Client *client)
// {
// 	delete client->_cmd;
// 	reponse.push_back("KILLING SERVER...\r\n");
// 	sender_all(client_list);
// 	std::vector<Channel *>::iterator itchan = server._channels.begin();
// 	for (; itchan != server._channels.end(); ++itchan)
// 	{
// 		delete *itchan;
// 	}
// 	std::map<int, Client *>::iterator itclient = server._clients.begin();
// 	for (; itclient != server._clients.end(); ++itclient)
// 	{
// 		std::vector<Channel *>::iterator itchan2 = (*itclient).second->_chans.begin();
// 		for (; itchan2 != (*itclient).second->_chans.end(); ++itchan2)
// 			delete *itchan2;
// 	}
// 	std::map<int, Client *>::iterator clicli = server._clients.begin();
// 	for (; clicli != server._clients.end(); ++clicli)
// 	{
// 		send((*clicli).second->_sock, reponse[0].c_str(), reponse[0].length(), 0);
// 		close((*clicli).second->_sock);
// 		delete (*clicli).second;
// 	}
// 	exit(0);
// 	return (reponse);
// }
