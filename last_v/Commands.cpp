/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 14:09:45 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/21 16:40:02 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Commands.hpp"

Commands::Commands(std::string cmd_str): _str_rcv(cmd_str){
	std::cout << "[COMMAND CONSTRUCTOR]"  << std::endl;
	return ;
}

void	Commands::sender(std::string cmd, std::string args){

}

void	Commands::pong(void){

}

void	Commands::privmsg(void){
	std::cout << "commande privmsg" << std::endl;
	return;
}
void	Commands::launcher(void){
	if (_str_rcv.find("PONG", 0) != std::string::npos)
		this->pong();
}

Commands::~Commands(void){
	return ;
}
