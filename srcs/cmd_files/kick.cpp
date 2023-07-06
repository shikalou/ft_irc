/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:36:31 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/06 17:49:30 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"

std::vector<std::string>	Commands::kick_cmd(Client *client)
{
	if (_cmd_args.size() < 2)
	{
		reponse.push_back(err_needmoreparams(_cmd));
		return (reponse);
	}
	Channel *chan_tmp = channel_exists(_cmd_args[0]);
	if (chan_tmp == NULL)
	{
		reponse.push_back(err_nosuchchannel(client->getNick(), _cmd_args[0]));
		return (reponse);
	}
	if (isOperator(chan_tmp->_operators, client->getNick()) == NULL)
	{
		reponse.push_back(err_chanoprivsneeded(client->getNick(), _cmd_args[0]));
		return (reponse);
	}
	if (nick_exists(client->getNick(), chan_tmp->_clients) == NULL)
	{
		reponse.push_back(err_notonchannel(client->getNick(), _cmd_args[0]));
		return (reponse);
	}
	Client *client_tmp = nick_exists(_cmd_args[1], chan_tmp->_clients);
	if (client_tmp == NULL)
	{
		reponse.push_back(err_usernotinchannel(client->getNick(), _cmd_args[1], _cmd_args[0]));
		return (reponse);
	}
	std::vector<Client *>::iterator it = chan_tmp->_clients.begin();
	for (; it != chan_tmp->_clients.end(); ++it)
	{
		if ((*it)->getNick() == _cmd_args[1])
		{
			chan_tmp->_clients.erase(it);
			break;
		}
	}
	std::vector<Channel *>::iterator ite = client_tmp->_chans.begin();
	for (; ite != client_tmp->_chans.end(); ++it)
	{
		if ((*ite)->getTitle() == _cmd_args[0])
		{
			client_tmp->_chans.erase(ite);
			break ;
		}
	}
	ite = server._channels.begin();
	for (;ite != server._channels.end(); ++ite)
	{
		if ((*ite)->getTitle() == _cmd_args[0])
		{
			(*ite)->_clients.erase(it);
			std::string res = "You've been kicked from channel " + _cmd_args[0] + "\r\n";
			send(client_tmp->_sock, res.c_str(), res.length(), 0);
			break ;
		}
	}
	std::string ret = ":" + client->getNick() + " KICK " + _cmd_args[0] + " " +  _cmd_args[1];
	if (_cmd_args.size() >= 3)
	{
		for (size_t i = 0; i < _cmd_args.size(); ++i)
		{
			ret += " ";
			ret += _cmd_args[i];
		}
	}
	ret += "\r\n";
	reponse.push_back(ret);
	return (reponse);
}
