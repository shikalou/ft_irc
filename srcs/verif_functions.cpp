/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_functions.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:44:14 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/06 16:33:23 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"

Client	*Commands::isOperator(std::vector<Client *> operators, std::string client)
{
	std::vector<Client *>::iterator ite = operators.begin();
	for (; ite != operators.end(); ++ite)
	{
		if ((*ite)->getNick() == client)
			break ;
	}
	if (ite == operators.end())
	{
		return (NULL);
	}
	return (*ite);
}

Channel *Commands::channel_exists(std::string chan_name)
{
	std::vector<Channel *>::iterator it = server._channels.begin();
	while (it != server._channels.end())
	{
		std::cout << "|"<< chan_name << "|  |" << (*it)->getTitle() << "|\n";
		if (chan_name == (*it)->getTitle())
			return (*it);
		it++;
	}
	return (NULL);
}

Client	*Commands::nick_exists(std::string nick_name, std::vector<Client *> clients)
{
	std::vector<Client *>::iterator it = clients.begin();
	while (it != clients.end())
	{
		std::cout << "|"<< nick_name << "|  |" << (*it)->getNick() << "|\n";
		if (nick_name == (*it)->getNick())
			return (*it);
		it++;
	}
	return (NULL);
}