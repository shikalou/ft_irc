/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:47:29 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/27 16:01:30 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include "Channel.hpp"

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

		std::vector<Channel> _chans;

		int			_sock;
	private :
		std::string	_pass;
		std::string	_nick;
		std::string	_user;
};

#endif
