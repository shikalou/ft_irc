/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 14:47:29 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/18 18:29:02 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <sys/types.h>
# include <sys/socket.h>
# include "Colors.hpp"

class Client {
	public :
		Client(int fd);
		~Client();

	private:
		int _fd_co;
};

#endif
