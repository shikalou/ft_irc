/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/29 19:21:15 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"
#include "Client.hpp"

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
	send(this->_fd_co, cmd.c_str(), cmd.length(), 0);
	return ;
}

void	Commands::pong(void){
	this->sender("PONG", " 127.0.0.1");
	return ;
}

void	Commands::quit(void){
	std::cout << "[DISCONNECTED]" << std::endl;
//	ne pas faire d'exit ?
	exit (1);
}

void	Commands::privmsg(void){
	std::cout << "[sending privmsg....]" << std::endl;
	return;
}

void	aff_vector(std::vector<Channel *> toto)
{
	std::vector<Channel *>::iterator it = toto.begin();
	for(; it != toto.end(); ++it)
		std::cout << "channel = " << (*it)->getTitle() << "\n";
}

void	Commands::join_chan(Client *client)
{
	int f = 0;
	if (_cmd_args.size() <= 0)
	{
		// NEED MORE PARAMS
	}
	std::vector<Channel *>::iterator it = server._channels.begin();
	std::vector<Channel *>::iterator ite = server._channels.end();
	for (; it != ite; ++it)
	{
		if (it == ite)
		{
			f = 1;
			server._channels.push_back(new Channel(_cmd_args[0]));
			client->_chans.push_back(new Channel(_cmd_args[0]));
			server._channels.back()->getClients().push_back(client);
		}
	}
	if (it == ite && f == 0)
	{
		server._channels.push_back(new Channel(_cmd_args[0]));
		client->_chans.push_back(new Channel(_cmd_args[0]));
		server._channels.back()->_clients.push_back(client);
	}

				/////////////////// DEBUG ///////////////////


	std::cout << "VERIF JOIN\n\n\n";
	aff_vector(server._channels);
	aff_vector(client->_chans);
	std::vector<Client *> test = server._channels.back()->_clients;
	for(std::vector<Client *>::iterator itdeb = test.begin(); itdeb != test.end(); ++itdeb)
		std::cout << "Client = " << (*itdeb)->getNick() << "\n";


              /////////////////////  END DEBUG ////////////////////


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
	send(_fd_co, "JOIN #julienlbg\n", 16, MSG_DONTWAIT);
	send(_fd_co, "331 ldinaut julienlbg :No topic is set\n", 39, MSG_DONTWAIT);
	send(_fd_co, "353 ldinaut = #julienlbg :@ldinaut\n", 35, MSG_DONTWAIT);
	send(_fd_co, "366 ldinaut #toto :End of /NAMES list\n", 38, MSG_DONTWAIT);
	return ;
	//}
	//std::cout << "[ERROR IN JOIN CMD]" << std::endl;
	//return;
}

void	Commands::user_cmd(Client *client)
{
	if (_cmd_args.size() <= 0)
	{
		//NEED_MORE_PARAMS
	}
	client->SetUser(_cmd_args[0]);
	server.network = _cmd_args[2];
}

void	Commands::launcher(std::map<int, Client *> client_list){

	std::cout << "cmd start launcher = " << _str_rcv << "\n\n\n";
	std::size_t found = this->_str_rcv.find("PING");
	if (found != std::string::npos && (found == 0))
		return (this->pong());
	found =  this->_str_rcv.find("QUIT");
	if (found != std::string::npos)
		return (this->quit());
	found =  this->_str_rcv.find("PRIVMSG");
	if (found != std::string::npos)
		return (this->privmsg());
	//found =  this->_cmd.find("JOIN");
	//if (found != std::string::npos && (found == 0)){
	if (_cmd == "JOIN")
	{
		return (this->join_chan(client_list[_fd_co]));
	}
	if (_cmd == "USER")
	{
		return (this->user_cmd(client_list[_fd_co]));
	}
	std::cout << "Not pong nor quit nor privmsg :((( == " << this->_str_rcv << std::endl;
	return ;
}

std::vector<std::string> split(std::string str, std::string delim)
{
	size_t start = 0;
	size_t pos_delim = str.find(delim);
	std::vector<std::string> ret;
	while (pos_delim != str.npos)
	{
		ret.push_back(str.substr(start, pos_delim - start));
		start = pos_delim + 1;
		pos_delim = str.find(delim, start);
	}
	ret.push_back(str.substr(start, str.length() - start));
	return (ret);
}

void	Commands::cmd_manager(std::map<int, Client *> client_list)
{
	(void)client_list;
	_cmd_args = split(_str_rcv, " ");
	_cmd = _cmd_args[0];
	_cmd_args.erase(_cmd_args.begin());
	for (std::vector<std::string>::iterator it = _cmd_args.begin(); it != _cmd_args.end(); it++)
	{
		std::cout << "split = " << *it << std::endl;
	}
	// puis launcher de commands pour remplir une reply qu'on send a la fin au client IRC
	launcher(client_list);
}

Commands::~Commands(void){
	return ;
}
