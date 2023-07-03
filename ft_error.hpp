/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 10:43:51 by mcouppe           #+#    #+#             */
/*   Updated: 2023/07/03 14:36:44 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_HPP
# define FT_ERROR_HPP

# include <iostream>

// numerics replies
std::string	err_nosuchnick(const std::string &nick);
std::string	err_nosuchchannel(const std::string &sender, const std::string channel);
std::string	err_cannotsendtochan(std::string &sender, std::string channel);
std::string	err_toomanychannels(std::string &sender, std::string channel);
std::string err_unknowncommmand(std::string &sender, std::string command);
std::string	err_nonicknamegiven(std::string &sender);
std::string err_erroneusnickname(std::string &sender, std::string nick);
std::string	err_nicknameinuse(std::string &sender, std::string nick);
std::string	err_usernotinchannel(std::string &sender, std::string &nick, std::string &channel);
std::string	err_notonchannel(std::string &sender, std::string &channel);
std::string	err_notregistered(std::string &sender);
std::string	err_needmoreparams(std::string command);
std::string	err_passwdmismatch(std::string &sender);

//RPL
std::string	rpl_welcome(const std::string &nick, const std::string &user, const std::string &host);
std::string	rpl_yourhost(const std::string &nick, const std::string &host);

// basic error
int	ft_error(std::string msg);

#endif
