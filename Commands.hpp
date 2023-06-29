/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:10:05 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/29 15:56:29 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Server.hpp"
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>


class Commands
{
	public :
		Commands();
		Commands(std::string cmd_str, int fd_co);
		~Commands(void);
		Commands(Commands *cpy);
		Commands operator=(const Commands *egal);

		void	cmd_manager(std::map<int, Client *> clients);
		void	launcher(void);
	//	int		parser(void);
		void	sender(std::string cmd, std::string args);

// CMDS FUNCTIONS
		void	pong(void);
		void	join_chan(void);
//		void	kick(void);
//		void	invite(void);
//		void	mode(void);
		void	privmsg(void);
	//	void	part(void);
		void	quit(void);
	//	void	squit(void);// quit only server
	//	void	user_cmd();
	//	void	pass_cmd();
	private :
/*
	explications :
		_str_rcv est la string brute envoyée par irssi
		_cmd est la commande identifiee (ex: "JOIN") 
		_cmd_args est ce qui suit apres "JOIN " par exemple
*/
		std::string	_str_rcv;
		std::string	_cmd;
		std::vector<std::string>	_cmd_args;
		int			_fd_co;
	//	std::string _cmd_send;
	//	std::string	_cmd_send_args;
	//	void	nick_cmd();
};
std::vector<std::string> split(std::string str, std::string delim);

#endif
