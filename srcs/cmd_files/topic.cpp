/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:17:14 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/06 15:25:36 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

std::string	Commands::setting_topic(std::vector<Channel *>::iterator it, Client *client){
	if (_cmd_args.size() >= 3 && _cmd_args[2].length() > 1){
		std::cout << GREEN << "[DEBUG]\nsetting topic..." << RESET << std::endl;
		(*it)->setTopic(_cmd_args[2]);
		(*it)->setTopicBool(true);
		return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));
	}
	else {
		std::cout << ORANGE << "[DEBUG]\nno topic provided" << RESET << std::endl;
		if ((*it)->getTopicBool()){
			std::cout << RED << "[DEBUG]\nerasing topic" << RESET << std::endl;
			(*it)->setTopic(" ");
			(*it)->setTopicBool(false);
			return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));
		}
	}
	return (rpl_notopic(client->getNick(), (*it)->getTitle()));
}

std::string	Commands::topic_from_client(Client *client, std::string chan_input){
	for (std::vector<Channel *>::iterator it = client->_chans.begin(); it != client->_chans.end(); ++it){
		if (chan_input == (*it)->getTitle()){
			if (_cmd_args[1].length() > 1)
				_cmd_args[1].erase(0, 1);
// si on est deja dans un channel
			if (_cmd_args[0][0] == '#'){
				std::string	tmp = _cmd_args[0];
				tmp.erase(0, 1);
			//	_cmd_args[1].erase(0, 1);
//				std::size_t	found = tmp.find(_cmd_args[1]);
//				if (found != std::string::npos && found == 0){
				if (tmp == _cmd_args[1]){
					std::cout << LAVENDER << "on cherche a interagir avec le topic de ce channel" << RESET << std::endl;
				// s'il y a un topic en arg
					return (setting_topic(it, client));
				}
				else{
					std::cout << ORANGE << "on cherche a interagir avec un autre channel" << RESET << std::endl;
					// _cmd_arg[0] --> nom du chan donc si pas de _cmd_arg[1] --> afficher juste le topic avec rpl
					if (_cmd_args.size() == 1){
						if ((*it)->getTopicBool())
							return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));
						else 
							return (rpl_notopic(client->getNick(), (*it)->getTitle()));
					}
					else {
						(*it)->setTopic(_cmd_args[1]);
						(*it)->setTopicBool(true);
						return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));
					}
				}
			}
		}
	}
	return ("");
}

std::string	Commands::topic_from_server(Client *client, std::string chan_input){
	for (std::vector<Channel *>::iterator it = server._channels.begin(); it != server._channels.end(); ++it){
		if (chan_input == (*it)->getTitle()){
		/*	if (_cmd_args[1].length() > 1)
				_cmd_args[1].erase(0, 1);
			if (_cmd_args[0][0] == '#'){
				std::string	tmp = _cmd_args[0];
				tmp.erase(0, 1);
				if (tmp == _cmd_args[1]){
					std::cout << RED << "[DEBUG]\n GROS PBLM ICI AIEAIEAIE" << RESET << std::endl;
					return "";
				}
				else {*/
					return (err_notonchannel(client->getNick(), (*it)->getTitle()));
		//		}
		//	}
		}
	}
	return "";
}

std::vector<std::string>	Commands::topic_cmd(Client *client){
//	std::size_t	size_args = _cmd_args.size();
	std::size_t	i = 0;
	while (i < _cmd_args.size()){
		std::cout << GREEN << _cmd_args[i] << RESET << std::endl;
		i++;
	}
//	error not param
	if ((_cmd_args[0]).length() <= 1){
		reponse.push_back(err_needmoreparams(this->_cmd));
		return (reponse);
	}
	std::string	chan_input;
	if (_cmd_args[0][0] == '#')
		chan_input = _cmd_args[0];
	else{
		chan_input = "#";
		chan_input += _cmd_args[0];
	}
	std::string	rep_from_client = this->topic_from_client(client, chan_input);
	if (rep_from_client.length() > 1){
		reponse.push_back(rep_from_client);
		return (reponse);
	}
	std::string rep_from_server = this->topic_from_server(client, chan_input);
	if (rep_from_server.length() > 1){
		reponse.push_back(rep_from_server);
		return (reponse);
	}
	reponse.push_back(err_nosuchchannel(client->getNick(), chan_input));
	return reponse;
}
