/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 23:19:25 by mcouppe           #+#    #+#             */
/*   Updated: 2023/06/19 00:01:43 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "Colors.hpp"
# include <iostream>

class Client{
	public :
		Client(int sock_cli);
		~Client(void);

	private :	
		int					_sock;
//		struct sockaddr_in	_addr;
};

#endif
