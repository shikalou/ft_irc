/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:11:22 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/04 15:11:29 by mcouppe          ###   ########.fr       */
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

		std::vector<Client *> getClients() const {return (_clients);};

		std::string getTitle() const {return (_title);};
		std::string getTopic() const {return (_topic);};
		void		setTopic(std::string topic);

		bool getInviteOnly() const {return (_invit_only);};
		std::vector<Client *>	_clients; // user du chan

	private:
		std::vector<Client *>	_operators; // admins du chan
		std::vector<Client *>	_banned;
		std::string				_title;
		std::string				_topic;
		std::string				_pass;
		bool					_invit_only;

};

#endif
