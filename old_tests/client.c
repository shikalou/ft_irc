/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcouppe <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 01:44:48 by mcouppe           #+#    #+#             */
/*   Updated: 2023/05/25 17:34:28 by mcouppe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <netdb.h>
# include <string.h>

void	error(char *msg){
	perror(msg);
	exit (0);
}

int	main(int ac, char **av){
	int	sock_fd;
	int	port_nbr;
	int	check;
	char	buffer[256];
	struct sockaddr_in	serv_addr;
	struct hostent	*server;

/*
struct  hostent
{
  char    *h_name;        * official name of host *
  char    **h_aliases;    * alias list *
  int     h_addrtype;     * host address type--> ipv4 w AF_INET *
  int     h_length;       * length of address in bytes*
  char    **h_addr_list;  * list of addresses from name server *
  #define h_addr  h_addr_list[0]  * address, for backward compatiblity *
};
*/

	if (ac < 3){
		fprintf(stderr, "usage %s hostname port", av[0]);
		exit (0);
	}
	port_nbr = atoi(av[2]);
	sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0)
		error("ERROR opening socket");

//	av[1] contains name of a host on the internet which info can be retrieved and stored
//	by gethostbyname() function that will fill the hostent struct w all infos
// if it returns NULL, the host couldn't be located by this name
	server = gethostbyname(av[1]);
	if (server == NULL){
		fprintf(stderr, "ERROR no sush host");
		exit (0);
	}

//	to sets fields in struct serv_addr
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port_nbr);
//	creates connection
	if (connect(sock_fd, &serv_addr, sizeof(serv_addr)) < 0)
		error("Error connecting");
	
	printf("Please enter a message : ");
	bzero(buffer, 256);
	fgets(buffer, 255, stdin);
	check = write(sock_fd, buffer, strlen(buffer));
	if (check < 0)
		error("ERROR writing to socket");
	bzero(buffer, 256);
	check = read(sock_fd, buffer, 256);
	if (check < 0)
		error("ERROR reading from socket");
	printf("%s", buffer);
	return (0);
}
