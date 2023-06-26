/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:30:46 by ldinaut           #+#    #+#             */
/*   Updated: 2023/06/26 19:16:21 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Client.hpp"

Server::Server(int port, std::string pass):password(pass), port(port)
{
}

Server::~Server()
{
}

int	Server::set_clients_info(std:: string cmd, Client *client)
{
	size_t i = 0;
	size_t n = cmd.find("PASS");
	if (n != cmd.npos)
	{
		i = cmd.find("\n", n);
		
		client->SetPass(cmd.substr(n + 5, i-(n + 5) - 1));
	}
	n = cmd.find("NICK");
	if (n != cmd.npos)
	{
		i = cmd.find_first_of("\n", n);
		int r = i-(n + 5) - 1;
		if (r > 9)
		{
			//send(fd_co, "432: nickname too long\n", )
			return (0);
		}
		client->SetNick(cmd.substr(n + 5, i-(n + 5) - 1));
	}
	else
	{
		send(fd_co, "431 : no nickname given\n", 24, MSG_DONTWAIT);
		return (0);
	}
	n = cmd.find("USER");
	if (n != cmd.npos)
	{
		i = cmd.find_first_of('\n', n);
		client->SetUser(cmd.substr(n + 5, i - (n + 5) - 1));
		size_t l = cmd.find_first_of(' ', n + 5);
		size_t l2 = cmd.find_first_of(' ', l + 1);
		size_t l3 = cmd.find_first_of(' ', l2 + 1);
		this->network = cmd.substr(l2 + 1, l3- 1 - l2 );
	}
	return (1);
}

void	Server::finish_connection(Client *client)
{
	std::string tmp_pass = "PASS " + client->getPass() + "\n";
	std::string tmp_nick = ":* NICK " + client->getNick() + "\n";
	std::string rpl_wel = "001 " + client->getNick() + " :Welcome to the " + network + " Network, " + client->getNick() + "\n";
	std::string	rpl_yoh = "002 " + client->getNick() + " :Your host is " + network + ", running version 2.4\n";
	send(fd_co, tmp_pass.c_str(), tmp_pass.length(), 0);
	send(fd_co, tmp_nick.c_str(), tmp_nick.length(), 0);
	send(fd_co, rpl_wel.c_str(), rpl_wel.length(), 0);
	send(fd_co, rpl_yoh.c_str(), rpl_yoh.length(), 0);
}

int	Server::parsing_cmd_co(std::string cmd, struct epoll_event ev, sockaddr_in sockaddr, int mode, int clfd)
{
	if (mode == 1)
	{
	int addrlen = sizeof(sockaddr);
	(void)addrlen;
	//int new_fd = accept(this->sock, 0,0);
	//fcntl(this->sock, F_SETFL, fcntl(this->sock, F_GETFL, 0) | O_NONBLOCK);
	int new_fd;
	if ((new_fd = accept(this->sock, (struct sockaddr*)&sockaddr, (socklen_t*)&addrlen)) < 0)
	{
		std::cout << "ERROR ACCEPT LOOOOL " << strerror(errno) << std::endl;;
	}

	fcntl(new_fd, F_GETFL, O_NONBLOCK);
	ev.data.fd = new_fd;
	ev.events = (EPOLLIN | EPOLLRDHUP);
	epoll_ctl(this->epoll_fd, EPOLL_CTL_ADD, new_fd, &ev);
	return (new_fd);
	}
	else
	{
	_clients[NICK_TOOBIG] = new Client(clfd);

	if (!set_clients_info(cmd, _clients[NICK_TOOBIG]))
	{
		
		// return error kill la connexion ?? jsais po
	}
	std::string nick_tmp = _clients[NICK_TOOBIG]->getNick();

	_clients.insert(std::make_pair(nick_tmp, new Client(0)));
	_clients[nick_tmp] = _clients[NICK_TOOBIG];
	_clients.erase(NICK_TOOBIG);
	finish_connection(_clients[nick_tmp]);
	return (clfd);
	}
}

void	Server::new_client(struct epoll_event ev, int k, sockaddr_in sockaddr)

{
	(void)k;
	(void)ev;
	(void)sockaddr;
	// std::cout << "NOUVEAU CLIENT" << std::endl;
	// std::vector<char>	buffer(4096);
	// std::string			cmd;
	
	// int ret = recv(fd_co, &buffer[0], 1000, MSG_DONTWAIT);
	// if (ret == 0)
	// {
	// 	exit(0);
	// 	//return (ft_error("[DISCONNECTED"));
	// }
	// std::cout << "\n\n\n\ncommand  ="<< &buffer[0] << std::endl << std::endl << std::endl << std::endl;
	// cmd.append(buffer.begin(), buffer.end());
	// this->_clients = this->parsing_cmd_co(cmd, ev, sockaddr);
	
}
