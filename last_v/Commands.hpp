/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:10:05 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/21 15:53:38 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Server.hpp"
#include <vector>

class Commands
{
	public :
		Commands(std::string cmd_str);
		~Commands(void);

		void	launcher(void);
	//	int		parser(void);
		void	sender(std::string cmd, std::string args);

// CMDS FUNCTIONS
		void	pong(void);
//		void	join(void);
//		void	kick(void);
//		void	invite(void);
//		void	mode(void);
		void	privmsg(void);
/*		void	part(void);
		void	quit(void);
		void	squit(void);// quit only server

		enum CommandList{
			
		};
*/
	private :
		std::string	_str_rcv;
		std::string	_cmd;
		std::string	_cmd_args;
	//	std::string _cmd_send;
	//	std::string	_cmd_send_args;
/*	void	pass_cmd();
	void	user_cmd();
	void	nick_cmd();*/
};
