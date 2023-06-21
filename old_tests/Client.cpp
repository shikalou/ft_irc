/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 18:09:53 by mcouppe           #+#    #+#             */
/*   Updated: 2023/06/18 18:34:30 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client(int fd): _fd_co(fd){
	std::cout << LILAC << "New User is Connected !" << RESET << std::endl;
	return;
} 

Client::~Client(void){
	std::cout << LILAC << "client on fd : " << this->_fd_co << " is disconnected" << RESET << std::endl;
	return ;
}
