/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:11:22 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/05 19:45:48 by ldinaut          ###   ########.fr       */
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
		Channel(Channel *cpy);
		~Channel();

		Channel	operator=(const Channel *egal);
		std::vector<Client *> getClients() const {return (_clients);};

		std::string getTitle() const {return (_title);};
		std::string getTopic() const {return (_topic);};
		void		setTopic(std::string topic);


		bool	getInviteOnly() const {return (_invit_only);} 
		void	setInviteOnly(bool mode) {_invit_only = mode;};
		bool	getTopicRestrict() const {return (_topic_restrict);} 
		void	setTopicRestrict(bool mode) {_topic_restrict = mode;};
		std::string	getPass() const {return(_pass);} 
		void	setPass(std::string new_pass) {_pass = new_pass;};
		int		isOperator(Client *client);
		bool	getPassSet() const {return (_pass_set);} 
		void	setPassSet(bool mode) {_pass_set = mode;};
		int		getMaxClient() const {return ( max_client);} 
		void	setMaxClient(int newlimit) { max_client = newlimit;};
		bool	getLimitClient() const {return ( _limit_set);} 
		void	setLimitClient(bool newlimit) { _limit_set = newlimit;};

		std::vector<Client *>	_clients; // user du chan
		std::vector<Client *>	_invites;
		std::vector<Client *>	_operators; // admins du chan

	private:
		int						max_client;
		std::vector<Client *>	_banned;
		std::string				_title;
		std::string				_topic;
		std::string				_pass;
		bool					_topic_restrict;
		bool					_invit_only;
		bool					_topic_set;
		bool					_pass_set;
		bool					_limit_set;
};

#endif
