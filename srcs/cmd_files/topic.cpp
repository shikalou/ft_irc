/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:17:14 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/11 18:37:30 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

std::string	Commands::setting_topic(std::vector<Channel *>::iterator it, Client *client){
	if (_cmd_args.size() >= 2 && _cmd_args[1].length() > 1){
		std::cout << LIGHT_PINK << "PREMIERE BOUCLE" << RESET << std::endl;
		(*it)->setTopic(_cmd_args[1]);
		(*it)->setTopicBool(true);
		std::vector<Channel *>::iterator serv_it = server._channels.begin();
		for (; serv_it != server._channels.end(); ++serv_it){
			if ((*serv_it)->getTitle() == (*it)->getTitle()){
				(*serv_it)->setTopic(_cmd_args[1]);
				(*serv_it)->setTopicBool(true);
			}
		}
		return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));
	}
	else {
		std::cout << LIGHT_PINK << "DEUXIEME BOUCLE" << RESET << std::endl;
		if ((*it)->getTopicBool()){
			(*it)->setTopic(" ");
			(*it)->setTopicBool(false);
			std::vector<Channel *>::iterator serv_it = server._channels.begin();
			for (; serv_it != server._channels.end(); ++serv_it){
				if ((*serv_it)->getTitle() == (*it)->getTitle()){
					(*serv_it)->setTopic(_cmd_args[1]);
					(*serv_it)->setTopicBool(true);
				}
			}
			return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));
		}
	}
	std::cout << LIGHT_PINK << "SORTIE EN RPL ?" << RESET << std::endl;
	return (rpl_notopic(client->getNick(), (*it)->getTitle()));
}

bool	Commands::check_topic_mode(Client *client, const std::string &chan){
	std::vector<Channel *>::iterator	it = server._channels.begin();
	for (; it != server._channels.end(); ++it){
		if ((*it)->getTitle() == chan && (*it)->getTopicRestrict() == true){
			if (isOperator((*it)->_operators, client->getNick()) != NULL){
				return (true);
			}
			return (false);
		}
	} 
	return (true);
}

std::string	Commands::topic_from_client(Client *client, std::string chan_input){

	for (std::vector<Channel *>::iterator it = client->_chans.begin(); it != client->_chans.end(); ++it){
		if (chan_input == (*it)->getTitle()){
			if (_cmd_args.size() == 0){
				if ((*it)->getTopicBool())
					return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));
				else 
					return (rpl_notopic(client->getNick(), (*it)->getTitle()));
			}
			else {
				std::cout << RED << "DANS LE ELSE DE TOPIC FROM CLIENT" << RESET << std::endl;
				if (check_topic_mode(client, (*it)->getTitle()) == false)
					return (err_chanoprivsneeded(client->getNick(), (*it)->getTitle()));
				setting_topic(it, client);
				std::map<int, Client *>::iterator	all_cli = server._clients.begin();
				for (; all_cli != server._clients.end(); ++all_cli){
					std::vector<Channel *>::iterator	chan_cli = (*all_cli).second->_chans.begin();
					for (;chan_cli != (*all_cli).second->_chans.end(); ++chan_cli){
						if (chan_input == (*chan_cli)->getTitle()){
							std::cout << RED << "dans la allcli loop cli =" << (*all_cli).second->getNick() << RESET << std::endl;
							setting_topic(chan_cli, (*all_cli).second);
					/*		all_cli = server._clients.end();
							all_cli--;
							it = chan_cli;
							*/
							break ;
						}
					}
				}
		//		this->fd_users.push_back(client->_sock);
				adding_fd_users((*it), client->_sock);
				/*for (std::vector<int>::iterator o = fd_users.begin(); o != fd_users.end(); ++o)
{
}*/

				return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));	
			}
		}
	}
	return ("");
}

std::string	Commands::topic_from_server(Client *client, std::string chan_input){
	for (std::vector<Channel *>::iterator it = server._channels.begin(); it != server._channels.end(); ++it){
		if (chan_input == (*it)->getTitle()){
					return (err_notonchannel(client->getNick(), (*it)->getTitle()));
		}
	}
	return "";
}

std::vector<std::string>	Commands::topic_cmd(Client *client){
	if ((_cmd_args[0]).length() <= 1){
		reponse.push_back(err_needmoreparams(this->_cmd));
		return (reponse);
	}
	if ((_cmd_args.size() > 1))
		_cmd_args[1] = joining_args(_cmd_args);
	std::string	rep_from_client = this->topic_from_client(client, _cmd_args[0]);
	if (rep_from_client.length() > 1){
		reponse.push_back(rep_from_client);
		return (reponse);
	}
	std::string rep_from_server = this->topic_from_server(client, _cmd_args[0]);
	if (rep_from_server.length() > 1){
		reponse.push_back(rep_from_server);
		return (reponse);
	}
	reponse.push_back(err_nosuchchannel(client->getNick(), _cmd_args[0]));
	return reponse;
}
