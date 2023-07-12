/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 16:05:48 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/12 18:55:40 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Commands.hpp"
# include "Client.hpp"
# include "ft_error.hpp"

void	Commands::remove_cli_chan(const std::string &chan_title, Client *client)
{
//	from client->_chans
	std::vector<Channel *>::iterator it_chan = server._channels.begin();
	for (; it_chan != server._channels.end(); ++it_chan)
	{
		std::cout << "111 chantitle |" << chan_title << "|     it title: |" << (*it_chan)->getTitle() << "|" << "\n\n\n";
		if (chan_title == (*it_chan)->getTitle())
		{
			std::cout << GREEN << "JJJJJJ: " << (*it_chan)->getTitle() << "\n\n\n" << RESET;
			break ;
		}
	}
	std::vector<Client *>::iterator it_cli = (*it_chan)->_clients.begin();
	for (; it_cli != (*it_chan)->_clients.end(); ++it_cli)
	{
		if ((*it_cli)->getNick() == client->getNick())
		{
			(*it_chan)->_clients.erase(it_cli);
			break ;
		}
	}
//from server._channels
	std::cout << GREEN << "hhhhhhhhhh: " << (*it_chan)->getTitle() << "\n\n\n" << RESET;
	std::vector<Channel *>::iterator capi = client->_chans.begin();
	for (; capi != client->_chans.end(); ++capi)
	{
		std::cout << "222           chantitle |" << chan_title << "|     it title: |" << (*it_chan)->getTitle() << "|" << "\n\n\n";
		if ((*it_chan)->getTitle() == (*capi)->getTitle())
		{
			delete *capi;
			client->_chans.erase(capi);
			break ;
		}
	}
	(void)client;
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

void	Commands::remove_invited(const std::string &chan, Client *client){
	std::vector<Channel *>::iterator	it = server._channels.begin();
	for (; it != server._channels.end(); ++it){
		if ((*it)->getTitle() == chan && (isInvited((*it)->_invites, client->getNick()) != NULL)){
			std::vector<Client *>::iterator	it_cli = (*it)->_invites.begin();
			for (; it_cli != (*it)->_invites.end(); ++it_cli){
				if ((*it_cli)->getNick() == client->getNick()){
					(*it)->_invites.erase(it_cli);
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

	std::cout << "NAMEMMMEMEMEMEM = |" << _cmd_args[0] << "|\n\n\n";
	if ((_cmd_args.size() > 1) && (_cmd_args[1].length() > 1))
		_cmd_args[1] = joining_args(_cmd_args);
	//for (std::vector<Channel *>::iterator it = server._channels.begin(); it != server._channels.end(); ++it){
		//if ((*it)->getTitle() == _cmd_args[0]){
			std::vector<Channel *>::iterator chan_cli = client->_chans.begin();
			for (; chan_cli != client->_chans.end(); ++chan_cli){
				if ((*chan_cli)->getTitle() == _cmd_args[0]){
					std::string	reason = _cmd_args[1];

				//	std::vector<Client *>::iterator	it = (*chan_cli)->_clients.begin();
					this->fd_users.push_back(client->_sock);
					// for (; it != (*chan_cli)->_clients.end(); ++it)
					// {
					// 	fd_users.push_back((*it)->_sock);
					// }
					// adding_fd_users((*chan_cli), client->_sock);
					remove_operators((*chan_cli)->getTitle(), client);
					remove_invited((*chan_cli)->getTitle(), client);
					remove_cli_chan((*chan_cli)->getTitle(), client);
					std::string ret = ":" + client->getNick() + "!" + client->getUser() + "@localhost PART " + _cmd_args[0] + " "+ reason + "\r\n"; 
					reponse.push_back(ret);
					return (reponse);
				}
			}
			reponse.push_back(err_notonchannel(client->getNick(), _cmd_args[0]));
			return (reponse);
		//}
//	}
	reponse.push_back(err_nosuchchannel(client->getNick(), _cmd_args[0]));
	return (reponse);
}
