/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:35:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/12 02:12:26 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"

std::vector<std::string>	Commands::quit(Client *client)
{
	std::vector<std::string> stock(_cmd_args);
	_cmd_args.clear();
	std::size_t	size = client->_chans.size();
	std::size_t	i = 0;
	for (std::vector<Channel *>::iterator it = client->_chans.begin(); it != client->_chans.end(); ++it)
	{
		_cmd_args[0] = (*it)->getTitle();
		part(client);
		sender(reponse, "");
		i++;
		if (i == size)
			break;
	}
	_cmd_args = stock;
	isQuit = true;
	close(client->_sock);
	std::string ret = client->getNick() + ": Quit";
	if (_cmd_args.size() > 0)
	{
		for (size_t i = 0; i < _cmd_args.size(); ++i)
		{
			ret += " ";
			ret += _cmd_args[i];
		}
	}
	ret += "\r\n";
//	reponse.clear();
	reponse.push_back(ret);
	server._clients.erase(client->_sock);
	return (reponse);
}
