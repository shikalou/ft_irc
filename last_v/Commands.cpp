/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/28 16:29:31 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Commands::Commands(std::string cmd_str, int fd_co, std::string network): _str_rcv(cmd_str), _fd_co(fd_co), _network(network){
	std::cout << "[COMMAND CONSTRUCTOR]"  << std::endl;
	return ;
}

void	Commands::sender(std::string cmd, std::string args){
	cmd += args;
	send(this->_fd_co, cmd.c_str(), cmd.length(), 0);
	return ;
}

void	Commands::pong(void){
	this->sender("PONG", this->_network);
	return ;
}

void	Commands::quit(void){
	std::cout << "[DISCONNECTED]" << std::endl;
//	ne pas faire d'exit ?
	exit (1);
}

void	Commands::privmsg(void){
//	si plsrs destinataires --> separes par ','
	std::cout << "[sending privmsg....]" << std::endl;
	this->_cmd_args.append(this->_str_rcv, (this->_cmd.length() + 1), ((this->_str_rcv.length() + 1) - (this->_cmd.length())));
	// ici -> cmd args ---> vector<std::string>
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
/*		send(_fd_co, "JOIN #julienlbg\n", 16, MSG_DONTWAIT);
		send(_fd_co, "331 ldinaut julienlbg :No topic is set\n", 39, MSG_DONTWAIT);
		send(_fd_co, "353 ldinaut = #julienlbg :@ldinaut\n", 35, MSG_DONTWAIT);
		send(_fd_co, "366 ldinaut #toto :End of /NAMES list\n", 38, MSG_DONTWAIT);*/
		return ;
	}
	std::cout << "[ERROR IN JOIN CMD]" << std::endl;
	return;
}

void	Commands::nick(void){
	//check for args
	this->_cmd_args.append(this->_str_rcv, (this->_cmd.length() + 1), ((this->_str_rcv.length() + 1) - (this->_cmd.length())));
	std::cout << "[DEBUG]\n nick = " << this->_cmd_args << std::endl;
// check NICK
/*
	cest surement le parcours des clients existants et leur nick ki va etre long
	if (structclientS->nickS.find(this->_cmd_args))
		return error nick exist ERR_NICKCOLLISION
	else
		this->_client.setnick(this->_cmd_args);
*/
	return ;
}


void	Commands::launcher(){
	std::cout << "cmd start launcher = " << _str_rcv << "\n\n\n";

	

	std::size_t found =  this->_str_rcv.find("PING");
	if (found != std::string::npos && (found == 0))
		return (this->pong());
	found =  this->_str_rcv.find("QUIT");
	if (found != std::string::npos && (found == 0))
		return (this->quit());
	found =  this->_str_rcv.find("PRIVMSG");
	if (found != std::string::npos && (found == 0))
		return (this->privmsg());
	found =  this->_str_rcv.find("JOIN");
	if (found != std::string::npos && (found == 0)){
		this->_cmd = "JOIN";
		return (this->join_chan());
	}
	found =  this->_str_rcv.find("NICK");
	if (found != std::string::npos && (found == 0)){
		this->_cmd = "NICK";
		return (this->nick());
	}
/*	found =  this->_str_rcv.find("MODE");
	if (found != std::string::npos && (found == 0)){
		this->_cmd = "MODE";
		//--> set le mode qque part --> sert pour CHANNELs
		return ;
	}*/

	std::cout << "Not pong nor quit nor privmsg :((( == " << this->_str_rcv << std::endl;
	return ;
}

Commands::~Commands(void){
	return ;
}
