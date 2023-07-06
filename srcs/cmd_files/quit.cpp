/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 12:35:07 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/06 13:17:49 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"

std::vector<std::string>	Commands::quit(Client *client)
{
	client->_recv.erase();
	isQuit = true;
	server._clients.erase(client->_sock);
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
	reponse.push_back(ret);
	return (reponse);
}
