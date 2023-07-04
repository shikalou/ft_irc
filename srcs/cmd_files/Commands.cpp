/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/04 13:01:35 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"
#include "ft_error.hpp"

Commands::Commands()
{
	// std::cout << "default constructor called" << std::endl;
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
	return (*this);
}

Commands::Commands(std::string cmd_str, int fd_co):  fd_users(), reponse(), _str_rcv(cmd_str), _fd_co(fd_co) {
	std::cout << "[COMMAND CONSTRUCTOR]"  << std::endl;
	return ;
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
	//this->sender("PONG", " 127.0.0.1");
	reponse.push_back("PONG 127.0.0.1\r\n");
	return (reponse);
}

std::vector<std::string>	Commands::quit(void){
	std::cout << "[DISCONNECTED]" << std::endl;
//	ne pas faire d'exit ?
	exit (1);
	return (reponse);
}

std::vector<std::string>	Commands::user_cmd(Client *client)
{
	if (client->_register == 1)
	{
		reponse.push_back(err_alreadyregistered(client->getNick()));
		return (reponse);
	}
	if (_cmd_args.size() <= 0)
	{
		reponse.push_back(err_needmoreparams("[empty]"));
		return (reponse);
		//NEED_MORE_PARAMS
	}
	client->SetUser(_cmd_args[0]);
	server.network = _cmd_args[2];
	if (server.password != client->getPass())
	{
		std::cout << "\n\n\n[DEBUG]\npureeee " << server.password << " et client pass = " << client->getPass() << "\n\n" << std::endl;
		std::string err_tmp = err_passwdmismatch(client->getNick());
		send(this->_fd_co, err_tmp.c_str(), err_tmp.length(), 0);
	}
	else {
		std::string rpl_wel = rpl_welcome(client->getNick(), client->getUser(), server.network);
		std::string	rpl_yoh = rpl_yourhost(client->getNick(), server.network);
		std::string ret = rpl_wel + rpl_yoh;
		client->_register = 1;
		reponse.push_back(ret);
		return (reponse);
	}
	reponse.push_back(err_notregistered(client->getNick()));
	return (reponse);
}
/*
std::vector<std::string>	Commands::topic_cmd(Client *client){
	// if no parameter : ERR_NEEDMOREPARAMS
	//	parcourir client->_chans --> if _cmd_args[0] == _chans.getTitle() --> access topic de ce chan (RPL_TOPIC or RPL NOTOPIC) if TOPIC existe mais == "" (length < 1) --> NO_TOPIC (clear topic)
	// pour CLEAR TOPIC --> peut etre un topic checker ? --> if topic_check == 1 --> topic else pas topic ?
	// if client l'a pas ds ses _chans --> ERR_NOTONCHANNEL
}
*/
std::vector<std::string>	Commands::nick_cmd(Client *client)
{
	std::string ret;
	client->SetNick(_cmd_args[0]);
	ret = ":*!@localhost NICK " + client->getNick() + "\r\n";
	reponse.push_back(ret);
	return (reponse);
}

std::string	Commands::pass_cmd(Client *client){
	if (client->_register == 1)
		return (err_alreadyregistered(client->getNick()));
	else
		client->SetPass(_cmd_args[0]);
	return "";
}

std::vector<std::string>	Commands::launcher(std::map<int, Client *> client_list)
{
	std::cout << "DANS LAUNCHER >> " << _cmd << std::endl << _cmd_args[0] << std::endl;
	if (_cmd == "PING")
		return (this->pong());
	if (_cmd == "QUIT")
		return (this->quit());
	if (_cmd == "PRIVMSG")
		return (this->privmsg(client_list[_fd_co]));
	if (_cmd == "JOIN")
	{
		return (this->join_chan(client_list[_fd_co]));
	}
	if (_cmd == "USER")
	{
		return (this->user_cmd(client_list[_fd_co]));
	}
	if (_cmd == "NICK")
	{
		return (this->nick_cmd(client_list[_fd_co]));
	}
	if (_cmd == "CAP")
	{
		return (reponse);
	}
	if (_cmd == "MODE")
		return (reponse);
	if (_cmd == "PASS")
	{
		reponse.push_back(this->pass_cmd(client_list[_fd_co]));
		return (reponse);
	}
//	if (_cmd == "TOPIC")
//		return (this->topic_cmd(client_list[_fd_co]));
	std::cout << "cmd =" << _cmd << "$" << std::endl;
//	std::cout << "Not pong nor quit nor privmsg :((( == " << this->_str_rcv << std::endl;

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
		std::string ret;
		reponse = launcher(client_list);
		sender(reponse, "");
		reponse.clear();
	}
}

Commands::~Commands(void){
	return ;
}
