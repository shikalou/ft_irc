/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:30:12 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/12 15:56:05 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

void	aff_vector(std::vector<Channel *> toto)
{
	std::vector<Channel *>::iterator it = toto.begin();
	for(; it != toto.end(); ++it)
		std::cout << "channel = " << (*it)->getTitle() << "\n";
}

std::vector<std::string>	Commands::join_chan(Client *client)
{
	int f = 0;
	if (_cmd_args.size() <= 0)
	{
		reponse.push_back(err_needmoreparams(_cmd));
		return (reponse);
	}
	std::vector<Channel *>::iterator it = server._channels.begin();
	std::vector<Channel *>::iterator ite = server._channels.end();
	for (; it != ite; ++it)
	{
		if ((*it)->getTitle() == _cmd_args[0])
		{
			break ;
		}
		if (it == ite)
		{
			f = 1;
			Channel *chan = new Channel(_cmd_args[0]);
			if (_cmd_args.size() > 1)
			{
				chan->setPassSet(true);
				chan->setPass(_cmd_args[1]);
			}
			server._channels.push_back(chan);
			client->_chans.push_back(new Channel(chan));
			server._channels.back()->getClients().push_back(client);

		}
	}
	if (it == ite && f == 0)
	{
		Channel *chan = new Channel(_cmd_args[0]);
		if (_cmd_args.size() > 1)
		{
			chan->setPassSet(true);
			chan->setPass(_cmd_args[1]);
		}
		server._channels.push_back(chan);
		client->_chans.push_back(new Channel(chan));
		server._channels.back()->_clients.push_back(client);
	}
	else
	{
		for (size_t i = 0; i < (*it)->_clients.size(); ++i)
		{
			if (client->_sock == (*it)->_clients[i]->_sock)
				return (reponse);
		}
		if ((*it)->getInviteOnly() == true)
		{
			std::vector<Client *>::iterator ita = (*it)->_invites.begin();
			for (;ita != (*it)->_invites.end(); ++ita)
			{
				if (client->getNick() == (*ita)->getNick())
					break;
			}
			if (ita == (*it)->_invites.end())
			{
				reponse.push_back(err_inviteonlychan(client->getNick(), _cmd_args[0]));
				return (reponse);
			}
			
		}
		if ((*it)->getPassSet() == true)
		{
			if (_cmd_args[1] != (*it)->getPass())
			{
				reponse.push_back(err_badchannelkey(client->getNick(), _cmd_args[0]));
				return (reponse);
			}
		}
		if ((*it)->getLimitClient() == true)
		{
			if ((*it)->_clients.size() >= (size_t)(*it)->getMaxClient())
			{
				reponse.push_back(err_channelisfull(client->getNick(), _cmd_args[0]));
				return (reponse);
			}
		}
		(*it)->_clients.push_back(client);
		client->_chans.push_back(new Channel(*it));
	}
	std::vector<Client *> test = server._channels.back()->_clients;
	std::vector<Channel *> recupname = server._channels;
	std::vector<Channel *>::iterator itrecup = recupname.begin();
	for(; itrecup != recupname.end(); ++itrecup)
	{
		if ((*itrecup)->getTitle() == _cmd_args[0])
			break ;
	}
	std::string ret = ":" + client->getNick() + "!" + client->getNick() + "@localhost JOIN :" + (*itrecup)->getTitle() + "\r\n";
	std::string recup = "";
	for(std::vector<Client *>::iterator itdeb = test.begin(); itdeb != test.end(); ++itdeb)
	 	recup += (*itdeb)->getNick() + " ";
	std::string	rpl_top;
	if ((*itrecup)->getTopicBool() == true)
		rpl_top = rpl_topic(client->getNick(), (*itrecup)->getTitle(), (*itrecup)->getTopic());
	else
		rpl_top = rpl_notopic(client->getNick(), (*itrecup)->getTitle());
	std::string res = recup + "has joined the channel " + _cmd_args[0] + "\r\n";
	reponse.push_back(ret);
	reponse.push_back(res);
	reponse.push_back(rpl_top);
	return (reponse);
}
