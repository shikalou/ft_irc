/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:15:45 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/04 12:01:58 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_error.hpp"

// numerics replies
std::string	err_nosuchnick(const std::string &nick){
	return ("401 Irssi " + nick + " :No such nick/channel\r\n");
}

std::string	err_nosuchchannel(std::string &sender, std::string channel){
	return ("403 " + sender + " " + channel + " :No such channel\r\n");
}

std::string	err_cannotsendtochan(std::string &sender, std::string channel){
	return ("404 " + sender + " " + channel + " :Cannot send to channel\r\n");
}

std::string	err_toomanychannels(std::string &sender, std::string channel){
	return ("405 " + sender + " " + channel + " :You have joined too many channels\r\n");
}

std::string err_unknowncommand(std::string sender, std::string command){
	return ("421 " + sender + " " + command + " :Unknown command\r\n");
}

std::string err_nonicknamegiven(const std::string &sender){
	return ("431 " + sender + " :No nickname given\r\n");
}

std::string	err_erroneusnickname(std::string &sender, std::string nick){
	return ("432 " + sender + " " + nick + " :Erroneus nickname\r\n");
}

std::string	err_nicknameinuse(std::string &sender, std::string nick){
	return ("433 " + sender + " " + nick + " :Nickname is already in use\r\n");
}

std::string	err_usernotinchannel(std::string &sender, std::string &nick, std::string &channel){
	return ("441 " + sender + " " + nick + " " + channel + " :They aren't on that channel\r\n");
}

std::string	err_notonchannel(std::string &sender, std::string &channel){
	return ("443 " + sender + " " + channel + " :You're not on that channel\r\n");
}

std::string	err_notregistered(const std::string &sender){
	return ("451 " + sender + " :You have not registered\r\n");
}

std::string	err_alreadyregistered(const std::string &sender){
	return ("462 " + sender + " :You may not reregister\r\n");
}

std::string	err_needmoreparams(std::string command){
	return ("461 Irssi " + command + " :Not enough parameters\r\n");
}

std::string	err_passwdmismatch(const std::string &sender){
	return ("464 " + sender + " :Password incorrect\r\n");
}

// RPL

std::string	rpl_welcome(const std::string &nick, const std::string &user, const std::string &host){
	std::string shortened_user;
	std::size_t	len = user.length();
	
	std::string	host_to_use;
	if (host.length() < 2)
		host_to_use = "localhost";
	else
		host_to_use = host;

	for (std::size_t i = 0; user[i] != ' ' && i < len; i++)
		shortened_user += user[i];
	return ("001 " + nick + " :Welcome to the ircserv Network, " + nick + "!" + shortened_user + "@" + host_to_use + "\r\n");
}

std::string	rpl_yourhost(const std::string &nick, const std::string &host){
		
	std::string	host_to_use;
	if (host.length() < 2)
		host_to_use = "localhost";
	else
		host_to_use = host;

	return ("002 " + nick + " :Your host is " + host_to_use + ", running version 2.4\r\n");
}

std::string	rpl_notopic(const std::string &nick, const std::string &channel){
	return ("331 " + nick + " " + channel + " :No topic is set\r\n");
}

std::string	rpl_topic(const std::string &nick, const std::string &channel, const std::string &topic){
	return ("332 " + nick + " " + channel + " :" + topic + "\r\n");
}
// basic error
int	ft_error(std::string msg){
	std::cerr << "Error : " << msg << std::endl;
	return (1);
}
