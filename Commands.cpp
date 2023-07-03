/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/03 19:55:05 by ldinaut          ###   ########.fr       */
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

std::string regroup_mess(std::vector<std::string> vec, Client *client, int mode)
{
	(void)client;
	std::string ret;
	if (mode == 0)
		ret = ":" + client->getNick() + "!~" + client->getNick() + "@localhost PRIVMSG ";
	else
		ret = ":" + client->getNick() + " PRIVMSG ";

	for (size_t i = 0; i < vec.size(); ++i)
	{
		ret += vec[i];
		ret += " ";
	}
	return (ret);
}

std::vector<std::string>	Commands::privmsg(Client *client)
{
	for (size_t i = 0; i < _cmd_args.size(); ++i)
	{
		std::cout << "i = " << i << " arg = " << _cmd_args[i] << "\n";
	}
	int f = 0;
	std::string arg;
	std::vector<Channel *> recupname = server._channels;
	std::vector<Channel *>::iterator itrecup = recupname.begin();
	for(; itrecup != recupname.end(); ++itrecup)
	{
		if ((*itrecup)->getTitle() == _cmd_args[0])
		{
			f = 1;
			break ;
		}
	}
	if (f == 1)
	{
		int j = 0;
		for (size_t k = 0; k < (*itrecup)->_clients.size(); ++k)
		{
			std::cout << "arg = " << arg << " sock = " << (*itrecup)->_clients[k]->getNick() << "\n\n\n";
			if (client->_sock != (*itrecup)->_clients[k]->_sock)
			{
				arg = regroup_mess(_cmd_args, client, 0);
				arg += "\r\n";
				if (j == 0)
					reponse.push_back(arg);
				j = 1;
				_fd_co = (*itrecup)->_clients[k]->_sock;
				fd_users.push_back(_fd_co);
				//send((*itrecup)->_clients[k]->_sock, arg.c_str(), arg.size(), 0);
				//return (reponse);
			}
		}
	}
	else
	{
		int	check = 0;
		std::map<int, Client *>::iterator it = server._clients.begin();
		for (; it != server._clients.end(); ++it) 
		{
			if ((*it).second->getNick() == _cmd_args[0])
			{
				arg = regroup_mess(_cmd_args, client, 1);
				arg += "\r\n";
				reponse.push_back(arg);
				std::cout << "arg = " << arg << (*it).first << " nick = " << (*it).second->getNick() << std::endl;
				_fd_co = (*it).second->_sock;
				check++;
				break ;
			}
		}
		if (check == 0){
	// ERR_NOSUCHNICK
			reponse.push_back(err_nosuchnick(_cmd_args[0]));
			return (reponse);
		}
	}
	//std::cout << (*itrecup)->getTitle() << std::endl;
	return (reponse);
}

void	aff_vector(std::vector<Channel *> toto)
{
	std::vector<Channel *>::iterator it = toto.begin();
	for(; it != toto.end(); ++it)
		std::cout << "channel = " << (*it)->getTitle() << "\n";
}

std::vector<std::string>	Commands::join_chan(Client *client)
{
	int f = 0;
	//_cmd_args[0].erase(_cmd_args[0].size() - 2, _cmd_args[0].size());
	if (_cmd_args.size() <= 0)
	{
		reponse.push_back(err_needmoreparams(_cmd));
		return (reponse);
		// NEED MORE PARAMS
	}
	std::vector<Channel *>::iterator it = server._channels.begin();
	std::vector<Channel *>::iterator ite = server._channels.end();
	for (; it != ite; ++it)
	{
		std::cout << "title = " << (*it)->getTitle() << " and arg[0] = " << _cmd_args[0] << "|" << "\n\n\n";
		if ((*it)->getTitle() == _cmd_args[0])
		{
			break ;
		}
		if (it == ite)
		{
			std::cout << "11111111111\n";
			f = 1;
			server._channels.push_back(new Channel(_cmd_args[0]));
			client->_chans.push_back(new Channel(_cmd_args[0]));
			server._channels.back()->getClients().push_back(client);
		}
	}
	if (it == ite && f == 0)
	{
			std::cout << "222222222222222\n";
		server._channels.push_back(new Channel(_cmd_args[0]));
		client->_chans.push_back(new Channel(_cmd_args[0]));
		server._channels.back()->_clients.push_back(client);
	}
	else
	{
			std::cout << "3333333333333\n";
		for (size_t i = 0; i < (*it)->_clients.size(); ++i)
		{
			if (client->_sock == (*it)->_clients[i]->_sock)
			{
				return (reponse);
			}
		}
		(*it)->_clients.push_back(client);
		// std::vector<Client *>::iterator t = (*it)->_clients.begin();
		// for (;t != (*it)->_clients.end(); ++t)
		// {
		// 	std::cout << (*t)->getNick() << "\n\n\n";
		// }
		client->_chans.push_back(*it);
	}

				/////////////////// DEBUG ///////////////////


	std::cout << "VERIF JOIN\n\n\n";
	std::cout << "serverchan:\n";
	aff_vector(server._channels);
	std::cout << "clientchan:\n";
	aff_vector(client->_chans);
	std::vector<Client *> test = server._channels.back()->_clients;
	for(std::vector<Client *>::iterator itdeb = test.begin(); itdeb != test.end(); ++itdeb)
		std::cout << "Client = " << (*itdeb)->getNick() << "\n";


              /////////////////////  END DEBUG ////////////////////



	std::vector<Channel *> recupname = server._channels;
	std::vector<Channel *>::iterator itrecup = recupname.begin();
	for(; itrecup != recupname.end(); ++itrecup)
	{
		if ((*itrecup)->getTitle() == _cmd_args[0])
			break ;
	}
	//std::string ret = client->getNick() + " has joined the llllllchannel " + strdup(_cmd_args[0].c_str() + 1) + "\r\n";
	std::string ret = ":" + client->getNick() + "!" + client->getNick() + "@localhost JOIN :" + (*itrecup)->getTitle() + "\r\n";
	//ret += rpl_notopic(client->getNick(), (*itrecup)->getTopic());
	// std::string ret = "JOIN " + (*itrecup)->getTitle() + "\r\n";
	// ret += "331 " + client->getNick() + (*itrecup)->getTopic() + "\r\n";
	std::string recup = "";
//	 ret += "users =";//+ client->getNick() + (*it)->getTopic() + "\n";
	for(std::vector<Client *>::iterator itdeb = test.begin(); itdeb != test.end(); ++itdeb)
	 	recup += (*itdeb)->getNick() + " ";

	// if ((*itrecup)->getInviteOnly())
	// 	ret += " * ";
	// else
	// ret += " = ";
	// ret += (*itrecup)->getTitle();
	// ret += ":@" + client->getNick() + "\r\n";
	// ret += "366 " + client->getNick() + " " + (*itrecup)->getTitle() + " :End of /NAMES list\r\n";
	// ret += client->getNick() + " has join the channel\n\r";
	 std::string res = recup + "has joined the chnnel " + _cmd_args[0] + "\r\n";
	//_cmd_args[1] = recup;
	//send(client->_sock, res.c_str(), res.length(), 0);
	
	//std::string res = _cmd_args[1] + "has joined the chnnel " + _cmd_args[0] + "\r\n";
	//send(this->_fd_co, res.c_str(), res.length(), 0);
	std::cout << "aaaaaaaaa = " << ret << "\n\n\n";
	reponse.push_back(ret);
	reponse.push_back(res);
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
