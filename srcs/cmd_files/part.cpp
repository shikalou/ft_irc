/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:05:48 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/06 18:53:35 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

void	Commands::remove_cli_chan(const std::string &chan_title, Client *client){
	std::vector<Channel *>::iterator it_chan = client->_chans.begin();
//	std::vector<Channel *>::iterator it_cli_end = client->_chans.end();
	for (; it_chan != client->_chans.end(); ++it_chan){
		// erasing client from channel users list
		if (chan_title == (*it_chan)->getTitle()){
			// check if client is in client list of channel
			std::vector<Client *>::iterator it_cli = (*it_chan)->_clients.begin();
			for (; it_cli != (*it_chan)->_clients.end(); ++it_cli){
				if ((*it_cli)->getNick() == client->getNick()){
					(*it_chan)->_clients.erase(it_cli);
					break ;
				}
			}
		// erasing channel from client
			client->_chans.erase(it_chan);
			break ;
		}
	}
	std::vector<Channel *>::iterator	it_serv = server._channels.begin();
	for (; it_serv != server._channels.end(); ++it_serv){
		if ((*it_serv)->getTitle() == chan_title){
			// check if client is in client list of channel
			std::vector<Client *>::iterator ite_cli = (*it_serv)->_clients.begin();
			for (; ite_cli != (*it_serv)->_clients.end(); ++ite_cli){
				if ((*ite_cli)->getNick() == client->getNick()){
					(*it_serv)->_clients.erase(ite_cli);
					break;
				}
			}
			break ;
		}
	}
}

std::vector<std::string>	Commands::part(Client *client){
	for (std::vector<Channel *>::iterator it = server._channels.begin(); it != server._channels.end(); ++it){
		std::string	chan_cleaned = "#";
		if (_cmd_args[0][0] == '#')
			chan_cleaned = _cmd_args[0];
		else
			chan_cleaned += _cmd_args[0];
		if ((*it)->getTitle() == chan_cleaned){
			for (std::vector<Client *>::iterator ite = (*it)->_clients.begin(); ite != (*it)->_clients.end(); ++ite){
				if ((*ite)->getNick() == client->getNick()){
					std::string	reason = _cmd_args[1];
					remove_cli_chan((*it)->getTitle(), client);
//			ca il faut send to all
					std::string ret = ":" + client->getNick() + "!" + client->getUser() + "@localhost PART " + (*it)->getTitle() + " "+ reason + "\r\n"; 
					reponse.push_back(ret);
					return (reponse);
				}
			}
			reponse.push_back(err_notonchannel(client->getNick(), (*it)->getTitle()));
			return (reponse);
		}
	}
	reponse.push_back(err_nosuchchannel(client->getNick(), _cmd_args[0]));
	return (reponse);
}
