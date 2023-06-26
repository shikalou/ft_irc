/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_creator.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:20:54 by mcouppe           #+#    #+#             */
/*   Updated: 2023/06/26 16:27:25 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

std::string	string_creator(std::vector<char> buffer){
	std::vector<char>::iterator	it;

	it  = buffer.begin();
	std::cout << "[DEBUG]\ncoucou:" << std::endl;
	while (it != buffer.end())
		std::cout << *it ;
	std::cout << std::endl;

	std::string cmd_str;
	cmd_str.append(buffer.begin(), buffer.end());
	return (cmd_str);
}
