/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 15:11:42 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/05 14:44:55 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(std::string title) : _title(title), _invit_only(false)
{
	max_client = -1;
	// _title.erase(_title.size() - 2, _title.size());
	this->_topic_set = 0;
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
