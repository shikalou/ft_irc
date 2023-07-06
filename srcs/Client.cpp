/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:07:39 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/06 21:38:17 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client(int sock_cli): _sock(sock_cli){
	(void)this->_sock;
	_register = 0;
	_recv = "";
	_cmd = NULL;
	//_cmd = new Commands();
//	std::cout << "[CLIENT CONSTRUCTOR]\nsock_cli = " << this->_sock << std::endl;
	return;
}

Client::~Client(void){
//	std::cout << "[CLIENT DESTRUCTOR]" << std::endl;
	// delete _cmd;
	return ;
}

void	Client::SetNick(std::string new_nick)
{
	this->_nick = new_nick;
}

void	Client::SetUser(std::string new_user)
{
	this->_user = new_user;
}

std::string	Client::getNick() const
{
	return (_nick);
}

std::string	Client::getUser() const
{
	return (_user);
}
