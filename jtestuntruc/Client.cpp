/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 23:15:20 by mcouppe           #+#    #+#             */
/*   Updated: 2023/06/19 12:43:58 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Client.hpp"

Client::Client(int sock_cli): _sock(sock_cli){
	std::cout << "client constructor with sock :" << this->_sock << std::endl;
	return ;
}

Client::~Client(void){
	std::cout << "Client out" << std::endl;
	return;
}
