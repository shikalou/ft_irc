/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/21 18:27:22 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

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

void	Commands::join_chan(void){
	std::cout << "[user is joining a channel]" << std::endl;
	return;
}
void	Commands::launcher(void){
	std::size_t found =  this->_str_rcv.find("PING");
	if (found != std::string::npos)
		return (this->pong());
	found =  this->_str_rcv.find("QUIT");
	if (found != std::string::npos)
		return (this->quit());
	found =  this->_str_rcv.find("PRIVMSG");
	if (found != std::string::npos)
		return (this->privmsg());
	found =  this->_str_rcv.find("JOIN");
	if (found != std::string::npos)
		return (this->join_chan());


	std::cout << "Not pong nor quit nor privmsg :((( == " << this->_str_rcv << std::endl;
	return ;
}

Commands::~Commands(void){
	return ;
}
