/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_server.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 16:28:22 by mcouppe           #+#    #+#             */
/*   Updated: 2023/05/29 17:51:33 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <iostream>
# include <sys/socket.h>

// AF_INET : ipv4
// sin_addr.s_addr : set addresse IP de l'host
// INADDR_ANY : constant qui recup l'IP de la machine
void	launch_server(int port, std::string passwd){
//	ds tout les cas il faut : recup socket qque part parce que 
//	ca va etre outil number one

	int	socket;
	struct	sockaddr_in	addr;

	socket = socket(AF_INET, SOCK_STREAM, 0);
	if (socket <= 0)
		return (error("Error: socket"));

//	set les variables qui correspondent au sein de la structure sockaddr

	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_nbr);
	addr.sin_addr.s_addr = INADDR_ANY;
	

// ici on a set les premiers trucs essentiels avant de continuer

//	sur mon tuto y'avait aussi un bzero de addr avaant de le remplir mais jsp ?

//	la prochaine étape : bind() 
//	c'est le syscall qui va permettre de binder la socket à l'addresse
//	donc le but là, c'est de bind l'addr de l'host au port sur lequel 
//	le server va run (en gros c un peu etablir une identification
//	de la connexion qu'on va mettre en place 
//	genre TELLE ADDRESSE sur TEL PORT etc)

// il faut proteger bind car si la socket est deja use sur la machine c DEAD
	if (bind(socket, (struct sockaddr *) &addr, sizeof(addr)) < 0)
		return (error("Error: binding"));

//	du coup ici ce que bryce fait c'est qu'il cree un std::ostringstream
//	et il utilise aussi une fonction avec une seed de temps pour genre
//	envoyer des messages [Server][Info] blabla  et la du coup il donne le port 
//	sur lequel il va ecouter ensuite

//	donc tout ca c'est pas forcement essentiel de le faire tt de suite parce
//	que c genre des messages de log

//	du coup on arrive sur la partie listen()

	if (listen(socket, 5) < 0)
		return (error("Error: listen() error"));

// le listen(SOCKET_NAME, 5) -- > le 5 c'est la size max 
//	derriere il lance sa fonction _run qui fait fenre de la gestion de socket
//	mais du coup la je suis perdue jcomprends plus rien a ce qu'il se passe 
//	a part qu'il init son CommandManager avec le registre des commandes IRC
//	qui je crois est un map parce qu'il fait des find dans son registre
}
