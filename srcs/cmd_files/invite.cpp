/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 15:56:38 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/05 17:01:14 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

std::vector<std::string>	Commands::invite_cmd(Client *client)
{
	if (_cmd_args.size() != 2)
	{
		reponse.push_back(err_needmoreparams("INVITE"));
		return (reponse);
	}
	Channel *chan = channel_exists(_cmd_args[1]);
	if (!chan)
	{
		reponse.push_back(err_nosuchchannel(client->getNick(), _cmd_args[1]));
		return (reponse);
	}
	std::vector<Client *>::iterator ite = chan->_clients.begin();
	for (; ite != chan->_clients.end(); ++ite)
	{
		std::cout << "|" << (*ite)->getNick() << "|  |" << client->getNick() << "|\n";
		if ((*ite)->getNick() == client->getNick())
			break ;
		if ((*ite)->getNick() == _cmd_args[0])
		{
		//	reponse.push_back(err_useronchannel());
			std::cout << "COMMAND A FAIRE\nERR_USERONCHANNEL\n";
			return (reponse);
		}
	}
	if (ite == chan->_clients.end())
	{
		reponse.push_back(err_notonchannel(client->getNick(), _cmd_args[1]));
		return (reponse);
	}
	std::map<int, Client *>::iterator it = server._clients.begin();
	for (; it != server._clients.end(); ++it)
	{
		if ((*it).second->getNick() == _cmd_args[0])
			break;
	}
	chan->_invites.push_back((*it).second);
	_fd_co = (*it).first;
	std::string ret = ":" + client->getNick() + "!" + client->getNick() + "@localhost INVITE " + _cmd_args[0] + " " + _cmd_args[1] + "\r\n";
	reponse.push_back(ret);
	return (reponse);
}
