/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 13:05:18 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/12 17:17:28 by ldinaut          ###   ########.fr       */
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
		if (chan_name == (*it)->getTitle())
			return (*it);
		it++;
	}
	return (NULL);
}

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

void	Commands::mode_o(int mode, Channel *chan, Client *client)
{
	if (mode == 0)
	{
		if (_cmd_args.size() == 2)
		{
			std::vector<Client *>::iterator it = chan->_operators.begin();
			for (; it != chan->_operators.end(); ++it)
			{
				if ((*it)->getNick() == client->getNick())
					break ;
			}
			if (it != chan->_operators.end())
				chan->_operators.erase(it);
			std::string res = ":ircserv MODE " + chan->getTitle() + " -o\r\n";
			reponse.push_back(res);
			reponse.push_back(err_chanoprivsneeded(client->getNick(), chan->getTitle()));
		}
		if (_cmd_args.size() == 3)
		{
			std::vector<Client *>::iterator it = chan->_operators.begin();
			for (; it != chan->_operators.end(); ++it)
			{
				if ((*it)->getNick() == _cmd_args[2])
					break ;
			}
			if (it == chan->_operators.end())
			{
				std::string ret = _cmd_args[2] + " is not an IRC operator\r\n";
				reponse.push_back(ret);
				return ;
			}
			std::vector<Client *>::iterator ite = chan->_operators.begin();
			for (; ite != chan->_operators.end(); ++ite)
			{
				if ((*ite)->getNick() == client->getNick())
					break ;
			}
			if (ite == chan->_operators.end())
			{
				reponse.push_back(err_chanoprivsneeded(client->getNick(), chan->getTitle()));
				return ;
			}
			for (ite = chan->_clients.begin(); ite != chan->_clients.end(); ++ite)
			{
				if ((*ite)->getNick() == _cmd_args[2])
					break ;
			}
			if (ite == chan->_clients.end())
			{
				reponse.push_back(err_nosuchnick(_cmd_args[2]));
				return ;
			}
			_fd_co = (*it)->_sock;
			if (it != chan->_operators.end())
				chan->_operators.erase(it);
			std::string res = ":ircserv MODE " + chan->getTitle() + " -o\r\n";
			reponse.push_back(res);
			reponse.push_back(err_chanoprivsneeded(client->getNick(), chan->getTitle()));
		}
	}
	else if (mode == 1)
	{
		if (_cmd_args.size() == 2)
		{
			std::vector<Client *>::iterator it = chan->_operators.begin();
			for (; it != chan->_operators.end(); ++it)
			{
				if ((*it)->getNick() == client->getNick())
					break ;
			}
			if (it == chan->_operators.end())
				chan->_operators.push_back(client);
			std::string res = ":ircserv MODE " + chan->getTitle() + " +o\r\n";
			reponse.push_back(res);
			reponse.push_back(rpl_youreoper(client->getNick()));
		}
		if (_cmd_args.size() == 3)
		{
			std::vector<Client *>::iterator it = chan->_operators.begin();
			for (; it != chan->_operators.end(); ++it)
			{
				if ((*it)->getNick() == _cmd_args[2])
					break ;
			}
			std::vector<Client *>::iterator ite = chan->_operators.begin();
			for (; ite != chan->_operators.end(); ++ite)
			{
				if ((*ite)->getNick() == client->getNick())
					break ;
			}
			if (ite == chan->_operators.end())
			{
				reponse.push_back(err_chanoprivsneeded(client->getNick(), chan->getTitle()));
				return ;
			}
			for (ite = chan->_clients.begin(); ite != chan->_clients.end(); ++ite)
			{
				if ((*ite)->getNick() == _cmd_args[2])
					break ;
			}
			if (ite == chan->_clients.end())
			{
				reponse.push_back(err_nosuchnick(_cmd_args[2]));
				return ;
			}
			if (it == chan->_operators.end())
				chan->_operators.push_back((*ite));
			_fd_co = (*ite)->_sock;
			std::string res = ":ircserv MODE " + chan->getTitle() + " +o\r\n";
			reponse.push_back(res);
			reponse.push_back(rpl_youreoper(client->getNick()));
		}
	}
}

void	Commands::mode_k(int mode, Channel *chan)
{
	if (mode == 1)
	{
		if (_cmd_args.size() == 2)
		{
			chan->setPassSet(true);
			std::string res = ":ircserv MODE " + chan->getTitle() + " +k\r\n";
			reponse.push_back(res);

		}
		else if (_cmd_args.size() == 3)
		{
			chan->setPassSet(true);
			chan->setPass(_cmd_args[2]);
			std::string res = ":ircserv MODE " + chan->getTitle() + " +k\r\n";
			std::string ret = "Password was changed for : " + _cmd_args[0] + " -> " + _cmd_args[2] + "\r\n";
			reponse.push_back(res);
			reponse.push_back(ret);
		}
	}
	else
	{
		chan->setPassSet(false);
		std::string res = ":ircserv MODE " + chan->getTitle() + " -k\r\n";
		reponse.push_back(res);
	}
}

void	Commands::mode_l(int mode, Channel *chan)
{
	if (mode == 1)
	{
		if (_cmd_args.size() >= 3)
		{
			chan->setMaxClient(atoi(_cmd_args[2].c_str()));
			chan->setLimitClient(true);
			std::string res = ":ircserv MODE " + chan->getTitle() + " +l\r\n";
			std::string ret = "Number of max clients for " + chan->getTitle() + " was changed to " + _cmd_args[2] + "\r\n";
			reponse.push_back(res);
			reponse.push_back(ret);
		}
		else
		{
			reponse.push_back(err_needmoreparams(_cmd));
			return ;
		}
	}
	else
	{
			chan->setLimitClient(false);
	}
}

void	Commands::mode_t(int mode, Channel *chan)
{
	if (mode > 0)
	{
		chan->setTopicRestrict(true);
		std::string ret = ":ircserv MODE " + chan->getTitle() + " +t\r\n";
		reponse.push_back(ret);
	}
	else
	{
		chan->setTopicRestrict(false);
		std::string ret = ":ircserv MODE " + chan->getTitle() + " -t\r\n";
		reponse.push_back(ret);
	}
}

std::string	regroup_mode(Channel *channel)
{
	std::string ret = "+";
	if (channel->getTopicRestrict() == true)
		ret += "t";
	if (channel->getInviteOnly() == true)
		ret += "i";
	if (channel->getPassSet() == true)
		ret += "k";
	if (channel->getLimitClient() == true)
		ret += "l";
	return (ret);
}

std::vector<std::string>	Commands::mode(Client *client)
{
	if (_cmd_args.size() < 1)
	{
		reponse.push_back(err_needmoreparams(_cmd));
		return (reponse);
	}
	if (_cmd_args[0][0] == '#')
	{
		Channel *chan = channel_exists(_cmd_args[0]);
		if (!chan)
		{
			reponse.push_back(err_nosuchchannel(client->getNick(), _cmd_args[0]));
			return (reponse);
		}
		if (_cmd_args.size() == 1)
		{
			std::string mode = regroup_mode(chan);
			reponse.push_back(rpl_channelmodeis(client->getNick(), _cmd_args[0], mode, ""));
			return (reponse);
		}
		if (_cmd_args[1][0] == '+')
		{
			if (_cmd_args[1][1] == 'i')
				mode_i(1, chan);
			else if (_cmd_args[1][1] == 't')
				mode_t(1, chan);
			else if (_cmd_args[1][1] == 'l')
				mode_l(1, chan);
			else if (_cmd_args[1][1] == 'o')
				mode_o(1, chan, client);
			else if (_cmd_args[1][1] == 'k')
				mode_k(1, chan);
			else
				reponse.push_back(err_unknownmode(_cmd_args[0], _cmd_args[1]));
		}
		else if (_cmd_args[1][0] == '-')
		{
			if (_cmd_args[1][1] == 'i')
				mode_i(0, chan);
			else if (_cmd_args[1][1] == 't')
				mode_t(0, chan);
			else if (_cmd_args[1][1] == 'k')
				mode_k(0, chan);
			else if (_cmd_args[1][1] == 'l')
				mode_l(0, chan);
			else if (_cmd_args[1][1] == 'o')
				mode_o(0, chan, client);
			else
				reponse.push_back(err_unknownmode(_cmd_args[0], _cmd_args[1]));
		}
	}
	return (reponse);
}
