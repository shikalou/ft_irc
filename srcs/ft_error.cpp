/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 12:15:45 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/06 13:28:01 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_error.hpp"

// numerics replies
std::string	err_nosuchnick(const std::string &nick){
	return ("401 " + nick + " :No such nick/channel\r\n");
}

std::string	err_nosuchchannel(const std::string &sender, const std::string &channel){
	if (channel[0] != '#')
	{
		std::string	tmp = "#";
		tmp.append(channel);
		return ("403 " + sender + " " + tmp + " :No such channel\r\n");
	}
	return ("403 " + sender + " " + channel + " :No such channel\r\n");
}

std::string	err_cannotsendtochan(const std::string &sender, const std::string &channel){
	return ("404 " + sender + " " + channel + " :Cannot send to channel\r\n");
}

std::string	err_toomanychannels(const std::string &sender, const std::string &channel){
	return ("405 " + sender + " " + channel + " :You have joined too many channels\r\n");
}

std::string	err_notexttosend(const std::string &sender){
	return ("412 " + sender + " :No text to send\r\n");
}

std::string err_unknowncommand(const std::string &sender, std::string command){
	return ("421 " + sender + " " + command + " :Unknown command\r\n");
}

std::string err_nonicknamegiven(const std::string &sender){
	return ("431 " + sender + " :No nickname given\r\n");
}

std::string	err_erroneusnickname(const std::string &sender, std::string nick){
	return ("432 " + sender + " " + nick + " :Erroneus nickname\r\n");
}

std::string	err_nicknameinuse(const std::string &sender, std::string nick){
	return ("433 " + sender + " " + nick + " :Nickname is already in use\r\n");
}

std::string	err_usernotinchannel(const std::string &sender, std::string &nick, std::string &channel){
	return ("441 " + sender + " " + nick + " " + channel + " :They aren't on that channel\r\n");
}

std::string	err_notonchannel(const std::string &sender, std::string &channel){
	return ("442 " + sender + " " + channel + " :You're not on that channel\r\n");
}

std::string	err_useronchannel(const std::string &sender, std::string &channel){
	return ("443 " + sender + " " + channel + " :is already on channel\r\n");
}

std::string	err_notregistered(const std::string &sender){
	return ("451 " + sender + " :You have not registered\r\n");
}

std::string	err_needmoreparams(std::string command){
	return ("461 Irssi " + command + " :Not enough parameters\r\n");
}

std::string	err_alreadyregistered(const std::string &sender){
	return ("462 " + sender + " :You may not reregister\r\n");
}

std::string	err_passwdmismatch(const std::string &sender){
	return ("464 " + sender + " :Password incorrect\r\n");
}

std::string	err_channelisfull(const std::string sender, const std::string channel)
{
	return ("471 " + sender + " " + channel + " :Cannot join channel (+l)\r\n");
}

std::string	err_unknownmode(const std::string &sender, const std::string modechar)
{
	return ("472 " + sender + " " + modechar + " :is unknown mode char to me\r\n");
}

std::string err_inviteonlychan(const std::string &sender, const std::string &channel)
{
	return ("473 " + sender + " " + channel + " :Cannot join channel (+i)\r\n");
}

std::string	err_badchannelkey(const std::string &sender, const std::string &channel)
{
	return ("475 " + sender + " " + channel + " :Cannot join channel (+k)\r\n");
}

std::string	err_noprivileges(const std::string &sender){
	return ("481 " + sender + " :Permission Denied- You're not an IRC operator\r\n");
}

std::string	err_chanoprivsneeded(const std::string &sender, const std::string &channel){
	return ("482 " + sender + " " + channel + " :You're not channel operator\r\n");
}

std::string	err_usersdontmatch(const std::string &sender){
	return ("502 " + sender + " :Cant change mode for other users\r\n");
}

std::string err_umodeunknownflag(const std::string &sender){
	return ("501 " + sender + " :Unknown MODE flag\r\n");
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
	return ("332 " + nick + " " + channel + " " + topic + "\r\n");
}

std::string	rpl_youreoper(const std::string &nick){
	return ("381 " + nick + " :You are now an IRC operator\r\n");
}

std::string	rpl_channelmodeis(const std::string &chan, const std::string &mode, const std::string &mode_params){
	return ("324 " + chan + " " + mode + " " + mode_params + "\r\n");
}

std::string	rpl_umodeis(const std::string &nick, std::string &modes){
	return ("221 " + nick + " " + modes + "\r\n");
}

std::string	rpl_inviting(const std::string &sender, const std::string &nick, const std::string &chan){
	return ("341 " + sender + " " + nick + " " + chan + "\r\n");
}

std::string	rpl_invitelist(const std::string &nick, const std::string &chan){
	return ("336 " + nick + " " + chan + "\r\n");
}

std::string	rpl_endofinvitelist(const std::string &nick){
	return ("337 " + nick + " :End of /INVITE list\r\n");
}

// basic error
int	ft_error(std::string msg){
	std::cerr << "Error : " << msg << std::endl;
	return (1);
}
