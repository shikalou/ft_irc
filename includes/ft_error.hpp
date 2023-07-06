/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 10:43:51 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/06 14:11:46 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_HPP
# define FT_ERROR_HPP

# include <iostream>

// numerics replies
std::string	err_nosuchnick(const std::string &nick);
std::string	err_nosuchchannel(const std::string &sender, std::string &channel);
std::string	err_cannotsendtochan(const std::string &sender, const std::string &channel);
std::string	err_toomanychannels(const std::string &sender, const std::string &channel);
std::string	err_notexttosend(const std::string &sender);
std::string err_unknowncommand(const std::string &sender, std::string command);
std::string	err_nonicknamegiven(const std::string &sender);
std::string err_erroneusnickname(const std::string &sender, std::string nick);
std::string	err_nicknameinuse(const std::string &sender, std::string nick);
std::string	err_usernotinchannel(const std::string &sender, std::string &nick, std::string &channel);
std::string	err_useronchannel(const std::string &sender, std::string &channel);
std::string	err_notonchannel(const std::string &sender, const std::string &channel);
std::string	err_notregistered(const std::string &sender);
std::string	err_alreadyregistered(const std::string &sender);
std::string	err_needmoreparams(std::string command);
std::string	err_passwdmismatch(const std::string &sender);
std::string	err_noprivileges(const std::string &sender);
std::string	err_chanoprivsneeded(const std::string &sender, const std::string &channel);
std::string	err_usersdontmatch(const std::string &sender);
std::string err_umodeunknownflag(const std::string &sender);

//RPL
std::string	rpl_welcome(const std::string &nick, const std::string &user, const std::string &host);
std::string	rpl_yourhost(const std::string &nick, const std::string &host);
std::string	rpl_notopic(const std::string &nick, const std::string &channel);
std::string	rpl_topic(const std::string &nick, const std::string &channel, const std::string &topic);
std::string	rpl_youreoper(const std::string &nick);
std::string	rpl_channelmodeis(const std::string &chan, const std::string &mode, const std::string &mode_params);
std::string	rpl_umodeis(const std::string &nick, std::string &modes);
std::string	rpl_inviting(const std::string &sender, const std::string &nick, const std::string &chan);
std::string	rpl_invitelist(const std::string &nick, const std::string &chan);
std::string	rpl_endofinvitelist(const std::string &nick);

// basic error
int	ft_error(std::string msg);

#endif
