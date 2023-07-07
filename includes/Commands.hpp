/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:10:05 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/07 14:48:09 by mcouppe          ###   ########.fr       */
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
#include "Colors.hpp"


class Commands
{
	public :
		Commands();
		Commands(std::string cmd_str, int fd_co);
		~Commands(void);
		Commands(Commands *cpy);
		Commands operator=(const Commands *egal);

		void						cmd_manager(std::map<int, Client *> clients);
		std::vector<std::string>	launcher(std::map<int, Client *> client_list);
		void						sender(std::vector<std::string> cmd, std::string args);
		void						sender_all(std::map<int, Client *> client_list);

// CMDS FUNCTIONS
		void	mode_i(int mode, Channel *chan);
		void	mode_t(int mode, Channel *chan);
		void	mode_o(int mode, Channel *chan, Client *client);
		void	mode_k(int mode, Channel *chan);
		void	mode_l(int mode, Channel *chan);

		std::vector<std::string>	pong(void);
		std::vector<std::string>	join_chan(Client *client);
		std::vector<std::string>	mode(Client *client);
		std::vector<std::string>	privmsg(Client *client);
		std::vector<std::string>	part(Client *client);
		void						remove_cli_chan(const std::string &chan_title, Client *client);
		void						adding_fd_users(Channel* chan);
		std::vector<std::string>	quit(Client *client);
		std::vector<std::string>	nick_cmd(Client *client);
		std::vector<std::string>	user_cmd(Client *client);
		std::vector<std::string>	pass_cmd(Client *client);
		std::vector<std::string>	kick_cmd(Client *client);
		std::vector<std::string>	topic_cmd(Client *client);
		std::vector<std::string>	invite_cmd(Client *client);
		std::string					joining_args(std::vector<std::string> args_vec);
		std::string					setting_topic(std::vector<Channel *>::iterator it, Client *client);
		std::string					topic_from_client(Client *client, std::string chan_input);
		std::string					topic_from_server(Client *client, std::string chan_input);

		std::vector<int>			fd_users;
		bool						isQuit;
		std::vector<std::string>	reponse;

		// VERIF FUNCTIONS
		Client	*isOperator(std::vector<Client *> operators, std::string client);
		Channel	*channel_exists(std::string chan_name);
		Client	*nick_exists(std::string nick_name, std::vector<Client *> clients);

	private :
		std::string					_str_rcv;
		std::string					_cmd;
		int							_fd_co;
		std::vector<std::string>	_cmd_args;
		bool						_check_pass;
};
std::vector<std::string> split(std::string str, std::string delim);
Channel	*channel_exists(std::string chan_name);

#endif
