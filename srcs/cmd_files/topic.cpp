/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 16:17:14 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/06 20:27:53 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"
/*
void	Commands::set_topic_for_all(std::vector<Channel *>::iterator it_chan, std::string topic){
	std::string	chan_name = it_chan.getTitle();

	std::vector<Client *>::iterator it_cli = (it_chan->getClients()).begin();
	for (; it_cli != (it_chan->getClients()).end(); ++it_cli){
		(*it_cli)->_chans
	}

}*/

std::string	Commands::setting_topic(std::vector<Channel *>::iterator it, Client *client){
	if (_cmd_args.size() >= 3 && _cmd_args[2].length() > 1){
		std::cout << GREEN << "[DEBUG]\nsetting topic..." << RESET << std::endl;
	//	set_topic_for_all(it, _cmd_args[2]);
		(*it)->setTopic(_cmd_args[2]);
		(*it)->setTopicBool(true);
		return (rpl_topic(client->getNick(), (*it)->getTitle(), (*it)->getTopic()));
	}
	else {
		std::cout << ORANGE << "[DEBUG]\nno topic provided" << RESET << std::endl;
		if ((*it)->getTopicBool()){
			std::cout << RED << "[DEBUG]\nerasing topic" << RESET << std::endl;
//			set_topic_for_all(it, " ");
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
			for (std::vector<Channel *>::iterator serv_it = server._channels.begin(); serv_it != server._channels.end(); ++serv_it){
				if ((*serv_it)->getTitle() == chan_input){
					if (_cmd_args[1].length() > 1)
						_cmd_args[1].erase(0, 1);
					if (_cmd_args[0][0] == '#'){
						std::string	tmp = _cmd_args[0];
						tmp.erase(0, 1);
						std::cout << GREEN << "\n[DEBUG]\ntmp =" << tmp << "$ et _cmd_args[1] =" << _cmd_args[1] << "$\n"<< RESET << std::endl;
						if (tmp == _cmd_args[1]){
							std::cout << RED << "\n\nSETTING TOPIC\n" << RESET << std::endl;
							return (setting_topic(serv_it, client));
						}
						else{
							if (_cmd_args.size() == 1){
								if ((*serv_it)->getTopicBool())
									return (rpl_topic(client->getNick(), (*serv_it)->getTitle(), (*serv_it)->getTopic()));
								else 
									return (rpl_notopic(client->getNick(), (*serv_it)->getTitle()));
							}
							else {
						//		set_topic_for_all(serv_it, _cmd_args[1]);
								(*serv_it)->setTopic(_cmd_args[1]);
								(*serv_it)->setTopicBool(true);
								return (rpl_topic(client->getNick(), (*serv_it)->getTitle(), (*serv_it)->getTopic()));
							}
						}
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
					return (err_notonchannel(client->getNick(), (*it)->getTitle()));
		}
	}
	return "";
}

std::vector<std::string>	Commands::topic_cmd(Client *client){
/*	std::size_t	i = 0;
	while (i < _cmd_args.size()){
		std::cout << GREEN << _cmd_args[i] << RESET << std::endl;
		i++;
	}*/
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
