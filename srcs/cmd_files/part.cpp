/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:05:48 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/08 18:17:30 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

void	Commands::remove_cli_chan(const std::string &chan_title, Client *client){
	std::vector<Channel *>::iterator it_chan = client->_chans.begin();
	for (; it_chan != client->_chans.end(); ++it_chan){
		if (chan_title == (*it_chan)->getTitle()){
			std::vector<Client *>::iterator it_cli = (*it_chan)->_clients.begin();
			for (; it_cli != (*it_chan)->_clients.end(); ++it_cli){
				if ((*it_cli)->getNick() == client->getNick()){
					(*it_chan)->_clients.erase(it_cli);
					break ;
				}
			}
//			delete *it_chan;
			//client->_chans.erase(it_chan);
			break ;
		}
	}
	std::vector<Channel *>::iterator	it_serv = server._channels.begin();
	for (; it_serv != server._channels.end(); ++it_serv){
		if ((*it_serv)->getTitle() == chan_title){
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

std::vector<int>	Commands::adding_fd_users(Channel* chan, int client_sock){
	std::vector<Client *>::iterator	it = chan->_clients.begin();
	(void)client_sock;
for (; it != chan->_clients.end(); ++it){
		if ((*it)->_sock != client_sock)
			this->fd_users.push_back((*it)->_sock);
	}
	return (fd_users);
}

std::vector<std::string>	Commands::part(Client *client){
	if ((_cmd_args.size() > 1) && (_cmd_args[1].length() > 1))
		_cmd_args[1] = joining_args(_cmd_args);
	for (std::vector<Channel *>::iterator it = server._channels.begin(); it != server._channels.end(); ++it){
		if ((*it)->getTitle() == _cmd_args[0]){
			std::vector<Channel *>::iterator chan_cli = client->_chans.begin();
			for (; chan_cli != client->_chans.end(); ++chan_cli){
				if ((*chan_cli)->getTitle() == _cmd_args[0]){
					std::string	reason = _cmd_args[1];
					this->fd_users.push_back(client->_sock);
					adding_fd_users((*it), client->_sock);
					remove_cli_chan((*chan_cli)->getTitle(), client);
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
