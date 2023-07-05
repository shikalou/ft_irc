/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:11:42 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/05 19:45:56 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string title) : _title(title), _invit_only(false)
{
	max_client = -1;
	// _title.erase(_title.size() - 2, _title.size());

}

Channel::Channel(Channel *cpy)
{
	*this = cpy;
}

Channel	Channel::operator=(const Channel *egal)
{
	max_client = egal->max_client;
	_title = egal->_title;
	_topic = egal->_topic;
	_pass = egal->_pass;
	_topic_restrict = egal->_topic_restrict;
	_invit_only = egal->_invit_only;
	_topic_set = egal->_topic_set;
	_pass_set = egal->_pass_set;
	_limit_set = egal->_limit_set;
	_clients = egal->_clients;
	_invites = egal->_invites;
	_operators = egal->_operators;
	return (*this);
}

void	Channel::setTopic(std::string topic){
	this->_topic = topic;
}

Channel::~Channel()
{
}
