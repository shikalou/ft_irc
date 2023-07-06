/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/06 21:40:02 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "ft_error.hpp"

Commands::Commands()
{
	// std::cout << "default constructor called" << std::endl;
}

Commands::Commands(std::string cmd_str, int fd_co):  fd_users(), reponse(), _str_rcv(cmd_str), _fd_co(fd_co) {
	isQuit = false;
	this->_check_pass = true;
	std::cout << "[COMMAND CONSTRUCTOR]"  << std::endl;
	return ;
}

Commands::Commands(Commands *cpy)
{
	*this = cpy;
}

Commands	Commands::operator=(const Commands *egal)
{
	this->_cmd = egal->_cmd;
	this->_cmd_args = egal->_cmd_args;
	this->_fd_co = egal->_fd_co;
	this->_str_rcv = egal->_str_rcv;
	this->reponse = egal->reponse;
	this->fd_users = egal->fd_users;
	this->isQuit = egal->isQuit;
	return (*this);
}

void	Commands::sender_all(std::map<int, Client *> client_list)
{
	std::map<int, Client *>::iterator it = client_list.begin();
	for (size_t i = 0; i < reponse.size(); ++i)
	{
		if (client_list.size() > 1)
		{
			for (; it != client_list.end(); ++it)
			{
				send((*it).first, reponse[i].c_str(), reponse[i].length(), 0);
			}
		}
	}
}

void	Commands::sender(std::vector<std::string> cmd, std::string args){
	//cmd += args;
	(void)args;
	//std::cout << "in sener = [" << cmd << "]" << "\n";
	for (size_t i = 0; i < reponse.size(); ++i)
	{
		std::cout << "in sender = [" << cmd[i] << "]" << "\n";
		if (fd_users.size() > 1)
		{
			for (std::vector<int>::iterator it = fd_users.begin(); it != fd_users.end(); ++it)
			{
				if (send(*it, cmd[i].c_str(), cmd[i].length(), 0/*MSG_DONTWAIT | MSG_NOSIGNAL*/) != (ssize_t)cmd[i].length())
					std::cout << "send error : clc" << std::endl;		
			}
		}
		else
		{
			if (send(this->_fd_co, cmd[i].c_str(), cmd[i].length(), 0/*MSG_DONTWAIT | MSG_NOSIGNAL*/) != (ssize_t)cmd[i].length())
				std::cout << "send error : clc" << std::endl;
		}
	}
	return ;
}

std::vector<std::string>	Commands::pong(void){
	reponse.push_back("PONG 127.0.0.1\r\n");
	return (reponse);
}

std::vector<std::string>	Commands::user_cmd(Client *client)
{
	// if (client->_register == 1)
	// {
	// 	reponse.push_back(err_alreadyregistered(client->getNick()));
	// 	return (reponse);
	// }
	if (this->_check_pass == 1)
	{
			return (reponse);
	}
	if (_cmd_args.size() <= 0)
	{
		reponse.push_back(err_needmoreparams("[empty]"));
		return (reponse);
	}
	client->SetUser(_cmd_args[0]);
	server.network = _cmd_args[2];
	std::string rpl_wel = rpl_welcome(client->getNick(), client->getUser(), server.network);
	std::string	rpl_yoh = rpl_yourhost(client->getNick(), server.network);
	std::string ret = rpl_wel + rpl_yoh;
	client->_register = 1;
	reponse.push_back(ret);
	return (reponse);
}

std::vector<std::string>	Commands::nick_cmd(Client *client)
{
	if (_cmd_args[0].size() > 20)
	{
		std::cout << "nick nw = |" << _cmd_args[0] << "|"<< "\n\n\n";
		reponse.push_back(err_erroneusnickname(client->getNick(), _cmd_args[0]));
		send(client->_sock, reponse[0].c_str(), reponse[0].length(), 0);
		close(client->_sock);
		reponse.clear();
		return (reponse);
	}
	std::map<int, Client *>::iterator it = server._clients.begin();
	for (; it != server._clients.end(); ++it)
	{
		if ((*it).second->getNick() == _cmd_args[0])
		{
			reponse.push_back(err_nicknameinuse(client->getNick(), _cmd_args[0]));
			//send(client->_sock, reponse[0].c_str(), reponse[0].length(), 0);
			//close(client->_sock);
			return (reponse);
		}
	}
	std::string ret;
	client->SetNick(_cmd_args[0]);
	ret = ":*!@localhost NICK " + client->getNick() + "\r\n";
	reponse.push_back(ret);
	return (reponse);
}

std::vector<std::string>	Commands::pass_cmd(Client *client){
	if (server.password != _cmd_args[0]){
		reponse.push_back(err_passwdmismatch(client->getNick()));
		this->_check_pass = false;
		return (reponse);
	}
	return (reponse);
}

std::vector<std::string>	Commands::launcher(std::map<int, Client *> client_list)
{
	std::cout << "DANS LAUNCHER >> " << _cmd << std::endl << _cmd_args[0] << std::endl;
	if (_cmd == "PING")
		return (this->pong());
	if (_cmd == "QUIT")
		return (this->quit(client_list[_fd_co]));
	if (_cmd == "PRIVMSG")
		return (this->privmsg(client_list[_fd_co]));
	if (_cmd == "JOIN")
		return (this->join_chan(client_list[_fd_co]));
	if (_cmd == "USER")
		return (this->user_cmd(client_list[_fd_co]));
	if (_cmd == "NICK")
		return (this->nick_cmd(client_list[_fd_co]));
	if (_cmd == "CAP")
		return (reponse);
	if (_cmd == "MODE")
		return (this->mode(client_list[_fd_co]));
	if (_cmd == "PASS")
		return (this->pass_cmd(client_list[_fd_co]));
	if (_cmd == "INVITE")
		return (this->invite_cmd(client_list[_fd_co]));
// debug en cours
	if (_cmd == "TOPIC")
		return (this->topic_cmd(client_list[_fd_co]));
	if (_cmd == "PART")
		return (this->part(client_list[_fd_co]));
	if (_cmd == "KICK")
		return (this->kick_cmd(client_list[_fd_co]));
	std::cout << "cmd =" << _cmd << "$" << std::endl;

//	WHEN NOT IN DEBUG : 
//	return (err_unknowncommand("Irssi", _cmd));
	return (reponse);
}

std::vector<std::string> split(std::string str, std::string delim)
{
	size_t start = 0;
	size_t pos_delim = str.find(delim);
	std::vector<std::string> ret;
	while (pos_delim != str.npos)
	{
		ret.push_back(str.substr(start, pos_delim - start));
		start = pos_delim + delim.length();
		pos_delim = str.find(delim, start);
	}
	ret.push_back(str.substr(start, str.length() - start));
	return (ret);
}

void	aff_vector(std::vector<std::string> toto)
{
	std::vector<std::string>::iterator it = toto.begin();
	for(; it != toto.end(); ++it)
		std::cout << "channel = " << (*it) << "\n";
}

void	Commands::cmd_manager(std::map<int, Client *> client_list)
{
	std::vector<std::string> split_nl = split(_str_rcv, "\r\n");
	for (size_t i = 0; i < split_nl.size() - 1; ++i)
	{
		_cmd_args = split(split_nl[i], " ");
		_cmd = _cmd_args[0];
		_cmd_args.erase(_cmd_args.begin());
		std::cout << "split [0] = " << _cmd << std::endl;
		for (std::vector<std::string>::iterator it = _cmd_args.begin(); it != _cmd_args.end(); it++)
		{
			std::cout << "split = " << *it << std::endl;
		}
		reponse = launcher(client_list);
		if (isQuit == true)
		{
			sender_all(client_list);
		}
		else
			sender(reponse, "");
		reponse.erase(reponse.begin(), reponse.end());
		reponse.clear();
		if (isQuit == true)
		{
			delete client_list[_fd_co];
			delete this;
		}
	}
}

Commands::~Commands(void)
{
	return ;
}
