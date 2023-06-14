/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mgmt.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:15:37 by mcouppe           #+#    #+#             */
/*   Updated: 2023/05/29 16:35:55 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>

int	int_error(char *message){
	if (message != NULL)
		std::cerr << message << std::endl;
	return (1);
}

void	error(char *message){
	if (message != NULL)
		std::cerr << message << std::endl;
	return ;
}
