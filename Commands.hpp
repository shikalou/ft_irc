/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:10:05 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/20 17:44:40 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "Server.hpp"
#include <vector>

class Commands
{
	public:
		Commands(std::string cmd_str);
		~Commands(void);

		void	launcher(void);
		void	parser(void);


	private:
		std::string	_str_rcv;
		std::string	_cmd_to_exec;
		std::string	_cmd_args;
/*	void	pass_cmd();
	void	user_cmd();
	void	nick_cmd();*/
};
