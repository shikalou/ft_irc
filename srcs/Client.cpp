/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 16:07:39 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/07 12:23:16 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client(int sock_cli): _sock(sock_cli)
{
	_register = 0;
	_recv = "";
	_cmd = NULL;
	_nick = "";
	_user = "";
}

Client::~Client(void)
{
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
