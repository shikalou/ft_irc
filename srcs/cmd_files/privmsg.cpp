/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 12:31:55 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/06 17:44:08 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

std::string regroup_mess(std::vector<std::string> vec, Client *client, int mode)
{
	(void)client;
	std::string ret;
	if (mode == 0)
		ret = ":" + client->getNick() + "!~" + client->getNick() + "@localhost PRIVMSG ";
	else
		ret = ":" + client->getNick() + " PRIVMSG ";

	for (size_t i = 0; i < vec.size(); ++i)
	{
		ret += vec[i];
		ret += " ";
	}
	return (ret);
}


std::vector<std::string>	Commands::privmsg(Client *client)
{
	for (size_t i = 0; i < _cmd_args.size(); ++i)
	{
		std::cout << "i = " << i << " arg = " << _cmd_args[i] << "\n";
	}
	int f = 0;
	std::string arg;
	std::vector<Channel *> recupname = server._channels;
	std::vector<Channel *>::iterator itrecup = recupname.begin();
	for(; itrecup != recupname.end(); ++itrecup)
	{
		if ((*itrecup)->getTitle() == _cmd_args[0])
		{
			f = 1;
			break ;
		}
	}
	if (f == 1)
	{
		int j = 0;
		for (size_t k = 0; k < (*itrecup)->_clients.size(); ++k)
		{
			std::cout << "arg = " << arg << " sock = " << (*itrecup)->_clients[k]->getNick() << "\n\n\n";
			if (client->_sock != (*itrecup)->_clients[k]->_sock)
			{
				arg = regroup_mess(_cmd_args, client, 0);
				arg += "\r\n";
				if (j == 0)
					reponse.push_back(arg);
				j = 1;
				_fd_co = (*itrecup)->_clients[k]->_sock;
				fd_users.push_back(_fd_co);
				//send((*itrecup)->_clients[k]->_sock, arg.c_str(), arg.size(), 0);
				//return (reponse);
			}
		}
	}
	else
	{
		int	check = 0;
		std::map<int, Client *>::iterator it = server._clients.begin();
		for (; it != server._clients.end(); ++it) 
		{
			if ((*it).second->getNick() == _cmd_args[0])
			{
				arg = regroup_mess(_cmd_args, client, 1);
				arg += "\r\n";
				reponse.push_back(arg);
				//std::cout << "arg = " << arg << (*it).first << " nick = " << (*it).second->getNick() << std::endl;
				_fd_co = (*it).second->_sock;
				check++;
				break ;
			}
		}
		if (check == 0){
	// ERR_NOSUCHNICK
			reponse.push_back(err_nosuchnick(_cmd_args[0]));
			return (reponse);
		}
	}
	//std::cout << (*itrecup)->getTitle() << std::endl;
	return (reponse);
}