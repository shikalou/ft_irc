/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 23:30:25 by mcouppe           #+#    #+#             */
/*   Updated: 2023/05/05 12:31:24 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/types.h>
# include <sys/socket.h>
// netinet with constants and strucs for internet domain addr
# include <netinet/in.h>

//func for err msgs
void	error(char *msg){
	perror(msg);
	exit (1);
}

int	check_message(char *buffer){
	if (buffer == NULL || buffer[0] == '\0' || strlen(buffer) > 510)
		return (1);
	
}
int	main(int ac, char **av){
	int	sock_fd;
	int	new_sock_fd;
	int port_nbr;
	socklen_t	cli_length;
	int	check;
	char	buffer[600];
	struct	sockaddr_in	serv_addr;
	struct	sockaddr_in	cli_addr;

/*
struct sockaddr_in
{
  short   sin_family; * must be AF_INET *
  u_short sin_port;
  struct  in_addr sin_addr;
  char    sin_zero[8]; * Not used, must be zero *
};
*/
	
	if (ac < 2){
		fprintf(stderr, "ERROR, no port provided");
		exit (1);
	}
// AF_INET --> ipv4
// SOCK_STREAM --> "Support de dialogue garantissant l'intégrité, fournissant un flux de données binaires, et intégrant un mécanisme pour les transmissions de données hors-bande. "
//	en gros il s'agit du socket type, here --> continuous stream as from a file or pipe 
//	the other option would be SOCK_DGRAM, msgs read in chunks
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
		error("ERROR opening socket");
//	setting buffer to 0
	bzero((char *) &serv_addr, sizeof(serv_addr));
//	retrieves the port number on which the server will listen for connections
	port_nbr = atoi(av[1]);
//	setting sin_family var to ipv4 (AF_INET)
	serv_addr.sin_family = AF_INET;
//	htons convert values between host and network byte order
	serv_addr.sin_port = htons(port_nbr);
//	in_addr is another struct with only one field : the IP addr of host
//	INADDR_ANY is the constant that gets the IP of the machine on which server runs
	serv_addr.sin_addr.s_addr = INADDR_ANY;
//	bind() is a syscall that bind a sock to an addr 
//	here we bind current host addr to port number on which server will run
//	it can fail for example if the chosen socket is already used on machine
	if (bind(sock_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
//	listen() syscall that allows process to listen on socket for connections
//	5 is the max size for most systems
	listen(sock_fd, 5);
//	accept() syscall that blocks process until client connects to server
//	when connection is successful, it wakes up process and return a new fd
//	that will be use for all communications on this connection
	cli_length = sizeof(cli_addr);
	new_sock_fd = accept(sock_fd, (struct sockaddr *) &cli_addr, &cli_length);
	if (new_sock_fd < 0)
		error("ERROR on accept");

	bzero(buffer, 600);
	check = read(new_sock_fd, buffer, 600);
	if (check < 0)
		error("ERROR reading from socket");
	if (check_message(buffer) == 1)
		error("Error in message")
	printf("The message is : %s", buffer);
	check = write(new_sock_fd, "I got your message", 18);
	if (check < 0)
		error("ERROR writing to socket");
	return (0);
}
