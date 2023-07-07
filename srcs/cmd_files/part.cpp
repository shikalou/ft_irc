/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:05:48 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/07 13:20:19 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

void	Commands::remove_cli_chan(const std::string &chan_title, Client *client){
	std::vector<Channel *>::iterator it_chan = client->_chans.begin();
	for (; it_chan != client->_chans.end(); ++it_chan){
		// erasing client from channel users list
		if (chan_title == (*it_chan)->getTitle()){
			// check if client is in client list of channel but in client->_chans->_clients ???
			
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

void						Commands::adding_fd_users(Channel* chan){
	std::vector<Client *>::iterator	it = chan->_clients.begin();
	for (; it != chan->_clients.end(); ++it){
		std::cout << ORANGE << "on envoie part @ " << (*it)->getNick() << RESET << std::endl;
		this->fd_users.push_back((*it)->_sock);
	}
}

std::vector<std::string>	Commands::part(Client *client){
	for (std::vector<Channel *>::iterator it = server._channels.begin(); it != server._channels.end(); ++it){
	// check si chan existe sur server
		if ((*it)->getTitle() == _cmd_args[0]){
			// check si client ds chan
			std::vector<Channel *>::iterator chan_cli = client->_chans.begin();
			for (; chan_cli != client->_chans.end(); ++chan_cli){
				if ((*chan_cli)->getTitle() == _cmd_args[0]){
					std::string	reason = _cmd_args[1];
					adding_fd_users((*it));
					remove_cli_chan((*chan_cli)->getTitle(), client);
					//adding_fd_users((*it));
					std::string ret = ":" + client->getNick() + "!" + client->getUser() + "@localhost PART " + (*it)->getTitle() + " "+ reason + "\r\n"; 
					//isPart = true;
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
