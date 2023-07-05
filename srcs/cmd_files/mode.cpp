/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:18 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/05 16:03:54 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"

Channel *channel_exists(std::string chan_name)
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

// int	Channel::isOperator(Client *client)
// {
	
// }

void	Commands::mode_i(int mode, Channel *chan)
{
	if (mode > 0)
	{
		chan->setInviteOnly(true);
		std::string ret = ":ircserv MODE " + chan->getTitle() + " +i\r\n";
		reponse.push_back(ret);
	}
	else
	{
		chan->setInviteOnly(false);
		std::string ret = ":ircserv MODE " + chan->getTitle() + " -i\r\n";
		reponse.push_back(ret);

	}
	
}

// void	Commands::mode_o(int mode, Channel *chan)
// {
	
// }

// void	Commands::mode_k(int mode, Channel *chan)
// {
	
// }

// void	Commands::mode_l(int mode, Channel *chan)
// {
	
// }

// void	Commands::mode_t(int mode, Channel *chan)
// {
	
// }

std::vector<std::string>	Commands::mode(Client *client)
{
	// if (_cmd_args.size() == 1)
	// 	return (rpl_channelmodeis());
	Channel *chan = channel_exists(_cmd_args[0]);
	if (!chan)
	{
		reponse.push_back(err_nosuchchannel(client->getNick(), _cmd_args[0]));
		return (reponse);
	}
	// if (_cmd_args.size() == 2 && chan.isOperator(client))
	// {
		
	// }
	if (_cmd_args[1][0] == '+')
	{
		if (_cmd_args[1][1] == 'i')
			mode_i(1, chan);
	}
	else if (_cmd_args[1][0] == '-')
	{
		if (_cmd_args[1][1] == 'i')
			mode_i(0, chan);
	}
	return (reponse);
}
