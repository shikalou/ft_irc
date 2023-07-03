/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/03 15:58:45 by ldinaut          ###   ########.fr       */
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
	return (*this);
}

Commands::Commands(std::string cmd_str, int fd_co): _str_rcv(cmd_str), _fd_co(fd_co){
	std::cout << "[COMMAND CONSTRUCTOR]"  << std::endl;
	return ;
}

void	Commands::sender(std::string cmd, std::string args){
	cmd += args;
	send(this->_fd_co, cmd.c_str(), cmd.length(), 0/*MSG_DONTWAIT | MSG_NOSIGNAL*/);
	return ;
}

std::string	Commands::pong(void){
	//this->sender("PONG", " 127.0.0.1");
	return ("PONG 127.0.0.1");
}

std::string	Commands::quit(void){
	std::cout << "[DISCONNECTED]" << std::endl;
//	ne pas faire d'exit ?
	exit (1);
	return ("");
}

std::string regroup_mess(std::vector<std::string> vec, Client *client)
{
	(void)client;
	std::string ret = ":" + client->getNick() + " PRIVMSG ";

	for (size_t i = 0; i < vec.size(); ++i)
	{
		ret += vec[i];
		ret += " ";
	}
	return (ret);
}

std::string	Commands::privmsg(Client *client)
{
	for (size_t i = 0; i < _cmd_args.size(); ++i)
	{
		std::cout << "i = " << i << " arg = " << _cmd_args[i] << "\n";
	}
	std::string arg = regroup_mess(_cmd_args, client);
	arg += "\r\n";
	int f = 0;
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
		for (size_t k = 0; k < (*itrecup)->_clients.size(); ++k)
		{
			std::cout << "arg = " << arg << " sock = " << (*itrecup)->_clients[k]->getNick() << "\n\n\n";
			if (client->_sock != (*itrecup)->_clients[k]->_sock)
			{
				_fd_co = (*itrecup)->_clients[k]->_sock;
				//send((*itrecup)->_clients[k]->_sock, arg.c_str(), arg.size(), 0);
				return (arg);
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
				std::cout << "arg = " << arg << (*it).first << " nick = " << (*it).second->getNick() << std::endl;
				_fd_co = (*it).second->_sock;
				//send((*it).second->_sock, arg.c_str(), arg.size(), 0);
				check++;
				break ;
			}
		}
		if (check == 0){
	// ERR_NOSUCHNICK
			return (err_nosuchnick(_cmd_args[0]));
		}
	}
	//std::cout << (*itrecup)->getTitle() << std::endl;
	return (arg);
}

void	aff_vector(std::vector<Channel *> toto)
{
	std::vector<Channel *>::iterator it = toto.begin();
	for(; it != toto.end(); ++it)
		std::cout << "channel = " << (*it)->getTitle() << "\n";
}

std::string	Commands::join_chan(Client *client)
{
	int f = 0;
	//_cmd_args[0].erase(_cmd_args[0].size() - 2, _cmd_args[0].size());
	if (_cmd_args.size() <= 0)
	{
		return (err_needmoreparams(_cmd));
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
				return ("");
		}
		(*it)->_clients.push_back(client);
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
	std::string ret = "JOIN " + (*itrecup)->getTitle() + "\n";
	ret += "331 " + client->getNick() + (*itrecup)->getTopic() + "\n";
	ret += "353";//+ client->getNick() + (*it)->getTopic() + "\n";
	for(std::vector<Client *>::iterator itdeb = test.begin(); itdeb != test.end(); ++itdeb)
		ret += " " + (*itdeb)->getNick();
	if ((*itrecup)->getInviteOnly())
		ret += " * ";
	else
		ret += " = ";
	ret += (*itrecup)->getTitle();
	ret += ":@" + client->getNick() + "\n";
	ret += "366 " + client->getNick() + " " + (*itrecup)->getTitle() + " :End of /NAMES list\n";

	std::cout << "aaaaaaaaa = " << ret << "\n\n\n";

	return (ret);
	// send(_fd_co, "JOIN #julienlbg\n", 16, MSG_DONTWAIT);
	// send(_fd_co, "331 ldinaut julienlbg :No topic is set\n", 39, MSG_DONTWAIT);
	// send(_fd_co, "353 ldinaut = #julienlbg :@ldinaut\n", 35, MSG_DONTWAIT);
	// send(_fd_co, "366 ldinaut #toto :End of /NAMES list\n", 38, MSG_DONTWAIT);

	//if (this->_str_rcv.length() > (this->_cmd.length()))
	//{
	// INIT
	// 	this->_cmd_args.append(this->_str_rcv, (this->_cmd.length() + 1), ((this->_str_rcv.length() + 1) - (this->_cmd.length())));
	// // PARSING ARGS
	// 	if (this->_cmd_args.length() > 200){
	// 		std::cerr << "[ERROR] CHAN LENGTH TOO LONG" << std::endl;
	// 		return ;
	// 	}
	// 	if (this->_cmd_args[0] != '&' && this->_cmd_args[0] != '#'){
	// 		std::cerr << "[ERROR] BAD FIRST CHAR CHAN NAME ?" << std::endl;
	// 		return ;
	// 	}
	// 	std::size_t found = this->_cmd_args.find(' ');
	// 	if (found != std::string::npos){
	// 		std::cerr << "[ERROR] SPACE CHAR CHAN NAME " << std::endl;
	// 		return ;
	// 	}
	// 	found = this->_cmd_args.find(7);
	// 	if (found != std::string::npos){
	// 		std::cerr << "[ERROR] CTRL G" << std::endl;
	// 		return ;
	// 	}
	// 	found = this->_cmd_args.find(',');
	// 	if (found != std::string::npos){
	// 		std::cerr << "[ERROR] COMA IN CHAN NAME" << std::endl;
	// 		return ;
	// 	}
	
	// END OF PARSING & DEBUG PRINT	
		//std::cout << "[user is joining a chan : " << this->_cmd_args << std::endl;
	//}
	//std::cout << "[ERROR IN JOIN CMD]" << std::endl;
	//return;
}

std::string	Commands::user_cmd(Client *client)
{
	if (_cmd_args.size() <= 0)
	{
		return (err_needmoreparams("[empty]"));
		//NEED_MORE_PARAMS
	}
	client->SetUser(_cmd_args[0]);
	server.network = _cmd_args[2];
	std::string rpl_wel = rpl_welcome(client->getNick(), client->getUser(), server.network);
	std::string	rpl_yoh = rpl_yourhost(client->getNick(), server.network);
	std::string ret = rpl_wel + rpl_yoh;
	client->_register = 1;
	return (ret);
}

std::string	Commands::nick_cmd(Client *client)
{
	std::string ret;
	client->SetNick(_cmd_args[0]);
	ret = ":* NICK " + client->getNick() + "\r\n";
	return (ret);
}

std::string	Commands::launcher(std::map<int, Client *> client_list)
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
		return ("");
	}
	//if (_cmd == "PASS")
	//{
//
//	}
	std::cout << "Not pong nor quit nor privmsg :((( == " << this->_str_rcv << std::endl;
	return "";
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
		ret = launcher(client_list);
		sender(ret, "");
	}
}

Commands::~Commands(void){
	return ;
}
