/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:05:48 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/12 15:56:11 by jtaravel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

void	Commands::remove_cli_chan(const std::string &chan_title, Client *client){
//	from client->_chans
	std::cout << "11111 = " << _cmd_args[0] << "\n\n\n";
	std::vector<Channel *>::iterator it_chan = server._channels.begin();
	if (client->_chans.size() > 0){
	std::cout << "22222 = " << _cmd_args[0] << "\n\n\n";
		for (; it_chan != server._channels.end(); ++it_chan){
			if (chan_title == (*it_chan)->getTitle()){
	std::cout << "3333 = " << _cmd_args[0] << "\n\n\n";
				std::vector<Client *>::iterator it_cli = (*it_chan)->_clients.begin();
	//			if ((*it_chan)->_clients.size()){
						std::cout << RED << "cb de fois ici ? + it_chan->_clients size ="<< (*it_chan)->_clients.size() << RESET << std::endl;
					for (; it_cli != (*it_chan)->_clients.end(); ++it_cli){
						std::cout << RED << "salut salut = " << (*it_cli)->getNick() << RESET << std::endl;
						if ((*it_cli)->getNick() == client->getNick()){
							(*it_chan)->_clients.erase(it_cli);
							break ;
						}
				//		std::cout << ORANGE << "cb de fois ici ?" << RESET << std::endl;
					}
	//			}
			//	std::cout << LIGHT_PINK << "cb de fois ici ?" << RESET << std::endl;
				break ;
			}
		}
	}
//from server._channels
			
	std::vector<Channel *>::iterator capi = client->_chans.begin();
	for (; capi != client->_chans.end(); ++capi)
	{
		if ((*it_chan)->getTitle() == (*capi)->getTitle())
		{
			delete *capi;
			client->_chans.erase(capi);
			break ;
		}
	}

	std::map<int, Client *>::iterator	all_cli = server._clients.begin();
	for (; all_cli != server._clients.end(); ++all_cli){
		
	}
}

void	Commands::remove_operators(const std::string &chan, Client *client){
	std::vector<Channel *>::iterator	it = server._channels.begin();
	for (; it != server._channels.end(); ++it){
		if ((*it)->getTitle() == chan && (isOperator((*it)->_operators, client->getNick()) != NULL)){
			std::vector<Client *>::iterator	it_cli = (*it)->_operators.begin();
			for (; it_cli != (*it)->_operators.end(); ++it_cli){
				if ((*it_cli)->getNick() == client->getNick()){
					(*it)->_operators.erase(it_cli);
					return ;
				}
			}
		}
	}
	return ;
}

void	Commands::adding_fd_users(Channel* chan, int client_sock){
	(void)client_sock; 
	std::vector<Client *>::iterator	it = chan->_clients.begin();
	if (chan->_clients.size() == 0)
		return ;
	for (; it != chan->_clients.end(); ++it){
	//	if ((*it)->_sock != client_sock)
		this->fd_users.push_back((*it)->_sock);
	}
	return ;
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
					std::vector<Channel *>::iterator test(chan_cli);
					remove_operators((*chan_cli)->getTitle(), client);
					remove_cli_chan((*test)->getTitle(), client);
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
