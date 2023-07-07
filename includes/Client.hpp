/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:47:29 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/07 12:23:55 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include "Channel.hpp"
# include "Commands.hpp"

class Commands;

class Client{
	public :
		Client(int sock_cli);
		Client(Client *cpy)
		{
			_nick = cpy->_nick;
			_user = cpy->_user;
			_chans = cpy->_chans;
			_cmd = cpy->_cmd;
			_sock = cpy->_sock;
			_register = cpy->_register;
			_recv = cpy->_recv;
		}
		~Client(void);

		void	SetNick(std::string new_nick);
		void	SetUser(std::string new_user);
		
		std::string	getNick() const;
		std::string	getUser() const;

		std::vector<Channel *>	_chans;
		Commands				*_cmd;
		int						_sock;
		int						_register;
		std::string				_recv;
	private :
		std::string	_nick;
		std::string	_user;
		
};

#endif
