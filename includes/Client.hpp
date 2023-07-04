/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:47:29 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/04 16:42:35 by mcouppe          ###   ########.fr       */
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
		~Client(void);

		void	SetPass(std::string new_pass);
		void	SetNick(std::string new_nick);
		void	SetUser(std::string new_user);
		
		std::string	getPass() const;
		std::string	getNick() const;
		std::string	getUser() const;

		std::vector<Channel *>	_chans;
		Commands				*_cmd;
		int						_sock;
		int						_register;
		std::string				_recv;
//	if mode == 
		int						_priv_mode;
	private :
		std::string	_pass; // A VIRER
		std::string	_nick;
		std::string	_user;
		
};

#endif
