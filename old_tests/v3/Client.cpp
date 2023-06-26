/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:07:39 by mcouppe           #+#    #+#             */
/*   Updated: 2023/06/21 12:44:37 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client(int sock_cli): _sock(sock_cli){
	(void)this->_sock;
//	std::cout << "[CLIENT CONSTRUCTOR]\nsock_cli = " << this->_sock << std::endl;
	return;
}

Client::~Client(void){
//	std::cout << "[CLIENT DESTRUCTOR]" << std::endl;
	return ;
}

void	Client::SetPass(std::string new_pass)
{
	this->_pass = new_pass;
}

void	Client::SetNick(std::string new_nick)
{
	this->_nick = new_nick;
}

void	Client::SetUser(std::string new_user)
{
	this->_user = new_user;
}

std::string	Client::getPass() const
{
	return (_pass);
}

std::string	Client::getNick() const
{
	return (_nick);
}

std::string	Client::getUser() const
{
	return (_user);
}
