/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 17:53:49 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/07 17:02:44 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"


void	Server::kill_cmd(std::map<int, Client *> client_list)
{

	// delete client._cmd;
	Commands *fin = new Commands();
	fin->reponse.push_back("KILLING SERVER...\r\n");
	fin->sender_all(client_list);
	
	// std::map<int, Client *>::iterator itclient = server._clients.begin();
	// for (; itclient != server._clients.end(); ++itclient)
	// {
	// 	std::vector<Channel *>::iterator itchan2 = (*itclient).second->_chans.begin();
	// 	for (; itchan2 != (*itclient).second->_chans.end(); ++itchan2)
	// 	{
	// 		delete *itchan2;
	// 		// (*itclient).second->_chans.erase(itchan2);
	// 	}
	// }
	// std::cout << "size = " <<  server._clients.size() << "\n\n\n";
	// for (size_t i = 0; i < server._clients.size(); ++i)
	// {
	// 	// send((*clicli).second->_sock, fin->reponse[0].c_str(), fin->reponse[0].length(), 0);
	// 	// close(server._clients[i]->_sock);
	// 	delete server._clients[i];
	// 	//server._clients.erase(server._clients[i]->_sock);
	// }
	for (std::map<int, Client *>::iterator it = client_list.begin(); it != client_list.end(); ++it)
		server.deleteClient((*it).second);
	std::vector<Channel *>::iterator itchan = server._channels.begin();
	for (; itchan != server._channels.end(); ++itchan)
	{
		delete *itchan;
		// server._channels.erase(itchan);
	}
	delete fin;
	server._end = 0;
}
