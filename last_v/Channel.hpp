/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:11:22 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/26 15:58:11 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP
#include "Server.hpp"

class Client;

class Channel
{
	public:
		Channel(std::string title);
		~Channel();

	private:
		std::vector<Client *>	_clients; // user du chan
		std::vector<Client *>	_operators; // admins du chan
		std::vector<Client *>	_banned;
		std::string				_title;
		std::string				_topic;
		std::string				_pass;
		//bool					_invit_only;

};

#endif
