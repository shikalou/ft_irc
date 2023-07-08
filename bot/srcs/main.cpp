/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 14:10:38 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/08 16:54:12 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

Bot bot;

int	ft_error(std::string msg){
	std::cerr << "Error : " << msg << std::endl;
	return (1);
}

void	Bot::add_epoll(int new_fd, int i)
{
	struct epoll_event ev;

	memset(&ev, 0, sizeof(ev));
	ev.data.fd = new_fd;
	ev.events = (EPOLLIN | EPOLLRDHUP);
	epoll_ctl(epoll_fd, EPOLL_CTL_ADD, new_fd, &ev);
	if (i == 1)
		this->fd_co = new_fd;
}

int	Bot::init_bot()
{
	this->epoll_fd = epoll_create1(0);

	this->sock = socket(AF_INET, SOCK_STREAM, 0);
	if (this->sock == -1)
		return (ft_error("socket failed"));
	int	opt = 1;
	if (setsockopt(this->sock, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
		return (ft_error("setsockopt failed"));
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = INADDR_ANY;
	sockaddr.sin_port = htons(this->_port);
	_sockaddr = sockaddr;
	
	connect(sock, (struct sockaddr*)&_sockaddr, sizeof(_sockaddr));
	int flags = fcntl(this->sock, F_GETFL, O_NONBLOCK);
	if (flags == -1)
		return (ft_error("fcntl failed"));
	this->add_epoll(this->sock, 1);
	return (0);
}

void	Bot::log_to_serv()
{
	std::string ret = "PASS " + _pass + "\r\n";
	send(sock, ret.c_str(), ret.length(), 0);
	ret = "NICK bot\r\n";
	send(sock, ret.c_str(), ret.length(), 0);
	ret = "USER bot bot localhost :Mister ROBOT\r\n";
	send(sock, ret.c_str(), ret.length(), 0);
}

std::vector<std::string> split(std::string str, std::string delim)
{
	size_t start = 0;
	size_t pos_delim = str.find(delim);
	std::vector<std::string> ret;
	while (pos_delim != str.npos)
	{
		ret.push_back(str.substr(start, pos_delim - start));
		start = pos_delim + delim.length();
		pos_delim = str.find(delim, start);
	}
	ret.push_back(str.substr(start, str.length() - start));
	return (ret);
}

void	Bot::send_mess(std::string str)
{
	int	random = rand() % 28 + 1;
	std::string ret;
	std::vector<std::string> cmd = split(str, " ");
	int i = cmd[0].find('!');
	std::string truc(cmd[0].c_str(), i);
	truc.erase(0, 1);
	ret = "PRIVMSG " + truc + " :";
	ret += jokes[random] + "\r\n";
	send(sock, ret.c_str(), ret.length(), 0);
}

void	sig_handler(int sig)
{
	if (sig == 2)
	{
		bot._end = false;
		send(bot.sock, "QUIT\r\n", 6, 0);
		exit(130);
	}
}

void	Bot::run()
{
	while (_end)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, sig_handler);
		{
			int ret;
			char buffer[4096];
			ret = recv(sock, buffer, 4096, 0);
			buffer[ret] = '\0';
			std::string str(buffer);
			if (str.find('\n') != str.npos)
			{
				if (str.find("joke") != str.npos)
					send_mess(str);
			}
		}
	}
}

int	main(int argc, char *argv[])
{
	if (argc != 3)
		return (ft_error(" usage [./bot same <port> <password> as ircserv]"));
	std::srand(time(NULL));
	Bot tbot(atoi(argv[1]), argv[2]);
	bot = tbot;
	bot.fill_tab();
	bot.init_bot();
	bot.log_to_serv();
	bot.run();
}
