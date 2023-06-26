/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_creator.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 16:20:54 by mcouppe           #+#    #+#             */
/*   Updated: 2023/06/26 19:51:11 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Server.hpp"

std::string	string_creator(std::vector<char> buffer, int ret){
	std::string	str;
	int i = 0;

	while (i < (ret - 2)){
		std::cout << buffer[i];
		str += buffer[i];
		i++;
	}
	return (str);
}
