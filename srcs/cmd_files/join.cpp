/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:30:12 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/05 14:26:22 by ldinaut          ###   ########.fr       */
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
	//_cmd_args[0].erase(_cmd_args[0].size() - 2, _cmd_args[0].size());
	if (_cmd_args.size() <= 0)
	{
		reponse.push_back(err_needmoreparams(_cmd));
		return (reponse);
		// NEED MORE PARAMS
	}
	std::vector<Channel *>::iterator it = server._channels.begin();
	std::vector<Channel *>::iterator ite = server._channels.end();
	for (; it != ite; ++it)
	{
		std::cout << "title = " << (*it)->getTitle() << " and arg[0] = " << _cmd_args[0] << "|" << "\n\n\n";
		if ((*it)->getTitle() == _cmd_args[0])
		{
			break ;
		}
		if (it == ite)
		{
			std::cout << "11111111111\n";
			f = 1;
			server._channels.push_back(new Channel(_cmd_args[0]));
			client->_chans.push_back(new Channel(_cmd_args[0]));
			server._channels.back()->getClients().push_back(client);
		}
	}
	if (it == ite && f == 0)
	{
			std::cout << "222222222222222\n";
		server._channels.push_back(new Channel(_cmd_args[0]));
		client->_chans.push_back(new Channel(_cmd_args[0]));
		server._channels.back()->_clients.push_back(client);
	}
	else
	{
			std::cout << "3333333333333\n";
		for (size_t i = 0; i < (*it)->_clients.size(); ++i)
		{
			if (client->_sock == (*it)->_clients[i]->_sock)
			{
				return (reponse);
			}
		}
		(*it)->_clients.push_back(client);
		// std::vector<Client *>::iterator t = (*it)->_clients.begin();
		// for (;t != (*it)->_clients.end(); ++t)
		// {
		// 	std::cout << (*t)->getNick() << "\n\n\n";
		// }
		client->_chans.push_back(*it);
	}

				/////////////////// DEBUG ///////////////////


	std::cout << "VERIF JOIN\n\n\n";
	std::cout << "serverchan:\n";
	aff_vector(server._channels);
	std::cout << "clientchan:\n";
	aff_vector(client->_chans);
	std::vector<Client *> test = server._channels.back()->_clients;
	for(std::vector<Client *>::iterator itdeb = test.begin(); itdeb != test.end(); ++itdeb)
		std::cout << "Client = " << (*itdeb)->getNick() << "\n";


              /////////////////////  END DEBUG ////////////////////



	std::vector<Channel *> recupname = server._channels;
	std::vector<Channel *>::iterator itrecup = recupname.begin();
	for(; itrecup != recupname.end(); ++itrecup)
	{
		if ((*itrecup)->getTitle() == _cmd_args[0])
			break ;
	}
	//std::string ret = client->getNick() + " has joined the llllllchannel " + strdup(_cmd_args[0].c_str() + 1) + "\r\n";
	std::string ret = ":" + client->getNick() + "!" + client->getNick() + "@localhost JOIN :" + (*itrecup)->getTitle() + "\r\n";
	// std::string ret = "JOIN " + (*itrecup)->getTitle() + "\r\n";
	// ret += "331 " + client->getNick() + (*itrecup)->getTopic() + "\r\n";
	std::string recup = "";
// check if topic is set for rpl
/*	if (((*itrecup)->getTopic()).length() > 1){
		std::cout << ORANGE << "[DEBUG]\nin join = there is already a topic" << RESET << std::endl;
		reponse.push_back(rpl_topic(client->getNick(), (*itrecup)->getTitle(), (*itrecup)->getTopic()));
	}
	else{
		std::cout << GREEN << "no topic" << RESET << std::endl;
	}
*/
//	 ret += "users =";//+ client->getNick() + (*it)->getTopic() + "\n";
	for(std::vector<Client *>::iterator itdeb = test.begin(); itdeb != test.end(); ++itdeb)
	 	recup += (*itdeb)->getNick() + " ";

	// if ((*itrecup)->getInviteOnly())
	// 	ret += " * ";
	// else
	// ret += " = ";
	// ret += (*itrecup)->getTitle();
	// ret += ":@" + client->getNick() + "\r\n";
	// ret += "366 " + client->getNick() + " " + (*itrecup)->getTitle() + " :End of /NAMES list\r\n";
	// ret += client->getNick() + " has join the channel\n\r";
	 std::string res = recup + "has joined the channel " + _cmd_args[0] + "\r\n";
	//_cmd_args[1] = recup;
	//send(client->_sock, res.c_str(), res.length(), 0);
	
	//std::string res = _cmd_args[1] + "has joined the chnnel " + _cmd_args[0] + "\r\n";
	//send(this->_fd_co, res.c_str(), res.length(), 0);
	std::cout << "aaaaaaaaa = " << ret << "\n\n\n";
	reponse.push_back(ret);
	reponse.push_back(res);
	return (reponse);
}
