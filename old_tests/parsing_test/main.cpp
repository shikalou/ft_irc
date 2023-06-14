/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 12:31:42 by mcouppe           #+#    #+#             */
/*   Updated: 2023/05/29 16:28:05 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <cstring>

int	parsing_args(char *port, char *pwd){
	if (std::strlen(port) > 12)
		return (int_error("Error: wrong port number"));
	if (std::strlen(pwd) < 5)
		return (int_error("Error: password too short"));
	if (std::strlen(pwd) > 30)
		return (int_error("Error: password too long"));
	int	i = -1;
	while (port && port[++i]){
		if (port[i] != '.' && (port[i] < '0' || port[i] > '9'))
			return (int_error("Error: wrong port number"));
	}
	i = -1;
	while (pwd && pwd[++i]){
		if (pwd[i] <= 32 || pwd[i] == ',' || pwd[i] >= 127)
			return (int_error("Error: unauthorized char in password (NO SPACE, COMA OR NON PRINTABLE)"));
	}
	return (0);
}

int	main(int ac, char **av){
	if (ac != 3){
		std::cerr << "Error: Invalid arguments\n./irc <PORT> <PASSWORD>" << std::endl;
		return (1);
	}
	if (parsing_args(av[1], av[2]) == 1)
		return (1);
	// Ensuite : il va falloir envoyer ces infos ds une struct pr les stocker
	// dc std::atoi(av[1]), std::string(av[2]) 
	launch_server(std::atoi(av[1]), std::string(av[2]));
	return (0);
}
