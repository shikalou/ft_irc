/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:10:05 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/04 13:10:46 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include "Server.hpp"
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <string>
#include "ft_error.hpp"


class Commands
{
	public :
		Commands();
		Commands(std::string cmd_str, int fd_co);
		~Commands(void);
		Commands(Commands *cpy);
		Commands operator=(const Commands *egal);

		void	cmd_manager(std::map<int, Client *> clients);
		std::vector<std::string>	launcher(std::map<int, Client *> client_list);
	//	int		parser(void);
		void	sender(std::vector<std::string> cmd, std::string args);

// CMDS FUNCTIONS
		std::vector<std::string>	pong(void);
		std::vector<std::string>	join_chan(Client *client);
//		void	kick(void);
//		void	invite(void);
		std::vector<std::string>	mode(Client *client);
		std::vector<std::string>	privmsg(Client *client);
	//	void	part(void);
		std::vector<std::string>	quit(void);
	//	void	squit(void);// quit only server
		std::vector<std::string>	nick_cmd(Client *client);
		std::vector<std::string>	user_cmd(Client *client);
		std::string	pass_cmd(Client *client);


		std::vector<int>			fd_users;
	//	void	pass_cmd();
	private :
/*
	explications :
		_str_rcv est la string brute envoyée par irssi
		_cmd est la commande identifiee (ex: "JOIN") 
		_cmd_args est ce qui suit apres "JOIN " par exemple
*/
		std::vector<std::string> reponse;
		std::string	_str_rcv;
		std::string	_cmd;
		std::vector<std::string>	_cmd_args;
		int			_fd_co;
	//	std::string _cmd_send;
	//	std::string	_cmd_send_args;
};
std::vector<std::string> split(std::string str, std::string delim);

#endif
