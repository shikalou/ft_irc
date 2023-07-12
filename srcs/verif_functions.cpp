/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_functions.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:44:14 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/12 15:51:14 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"

std::string	Commands::joining_args(std::vector<std::string> args_vec){
	std::string	result = "";
	for (std::size_t i = 1; i < args_vec.size(); ++i){
		result += args_vec[i];
		if (i + 1 < args_vec.size())
			result += " ";
	}
	return (result);
}

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

Client	*Commands::isInvited(std::vector<Client *> invited, std::string client)
{
	std::vector<Client *>::iterator ite = invited.begin();
	for (; ite != invited.end(); ++ite)
	{
		if ((*ite)->getNick() == client)
			break ;
	}
	if (ite == invited.end())
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
		if (nick_name == (*it)->getNick())
			return (*it);
		it++;
	}
	return (NULL);
}
