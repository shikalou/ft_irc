/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/29 11:49:07 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Commands::Commands()
{
	// std::cout << "default constructor called" << std::endl;
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

void	Commands::join_chan(void)
{
	if (this->_str_rcv.length() > (this->_cmd.length()))
	{
	// INIT
		this->_cmd_args.append(this->_str_rcv, (this->_cmd.length() + 1), ((this->_str_rcv.length() + 1) - (this->_cmd.length())));
	// PARSING ARGS
		if (this->_cmd_args.length() > 200){
			std::cerr << "[ERROR] CHAN LENGTH TOO LONG" << std::endl;
			return ;
		}
		if (this->_cmd_args[0] != '&' && this->_cmd_args[0] != '#'){
			std::cerr << "[ERROR] BAD FIRST CHAR CHAN NAME ?" << std::endl;
			return ;
		}
		std::size_t found = this->_cmd_args.find(' ');
		if (found != std::string::npos){
			std::cerr << "[ERROR] SPACE CHAR CHAN NAME " << std::endl;
			return ;
		}
		found = this->_cmd_args.find(7);
		if (found != std::string::npos){
			std::cerr << "[ERROR] CTRL G" << std::endl;
			return ;
		}
		found = this->_cmd_args.find(',');
		if (found != std::string::npos){
			std::cerr << "[ERROR] COMA IN CHAN NAME" << std::endl;
			return ;
		}
	
	// END OF PARSING & DEBUG PRINT	
		std::cout << "[user is joining a chan : "<< this->_cmd_args << std::endl;
		send(_fd_co, "JOIN #julienlbg\n", 16, MSG_DONTWAIT);
		send(_fd_co, "331 ldinaut julienlbg :No topic is set\n", 39, MSG_DONTWAIT);
		send(_fd_co, "353 ldinaut = #julienlbg :@ldinaut\n", 35, MSG_DONTWAIT);
		send(_fd_co, "366 ldinaut #toto :End of /NAMES list\n", 38, MSG_DONTWAIT);
		return ;
	}
	std::cout << "[ERROR IN JOIN CMD]" << std::endl;
	return;
}

// void	Commands::pass_cmd()
// {

// }

void	Commands::launcher(){
	std::cout << "cmd start launcher = " << _str_rcv << "\n\n\n";
	std::size_t found =  this->_str_rcv.find("PING");
	if (found != std::string::npos && (found == 0))
		return (this->pong());
	found =  this->_str_rcv.find("QUIT");
	if (found != std::string::npos)
		return (this->quit());
	found =  this->_str_rcv.find("PRIVMSG");
	if (found != std::string::npos)
		return (this->privmsg());
	found =  this->_str_rcv.find("JOIN");
	if (found != std::string::npos && (found == 0)){
		this->_cmd = "JOIN";
		return (this->join_chan());
	}
	std::cout << "Not pong nor quit nor privmsg :((( == " << this->_str_rcv << std::endl;
	return ;
}

Commands::~Commands(void){
	return ;
}
