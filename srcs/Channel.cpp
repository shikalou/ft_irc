/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:11:42 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/12 02:07:16 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string title) : _title(title)
{
	max_client = -1;
	_topic = "";
	_pass = "";
	_topic_restrict = false;
	_invit_only = false;
	_topic_set = false;
	_pass_set = false;
	_limit_set = false;
}

Channel::Channel(Channel *cpy): _clients(cpy->_clients), _invites(cpy->_invites)
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
	_operators = egal->_operators;
	return (*this);
}

void	Channel::setTopic(std::string topic){
	this->_topic = topic;
	this->setTopicBool(1);
}

void	Channel::setTopicBool(bool setter){
	this->_topic_set = setter;
}

bool	Channel::getTopicBool(void) const {
	return (this->_topic_set);
}

Channel::~Channel()
{
}
