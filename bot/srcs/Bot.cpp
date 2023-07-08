/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 15:44:44 by ldinaut           #+#    #+#             */
/*   Updated: 2023/07/08 16:10:40 by ldinaut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <Bot.hpp>


Bot::Bot(int port, std::string pass): _port(port), _pass(pass)
{
	_end = true;
}

Bot::~Bot()
{
}

void	Bot::fill_tab()
{
	jokes.push_back("Qu'est-ce qu'un steak qui parle ? Un steak-tille !");
	jokes.push_back("Pourquoi les plongeurs plongent-ils toujours en arrière du bateau ? Parce que sinon ils tombent dans l'eau !");
	jokes.push_back("Comment appelle-t-on un chien magicien ? Un toutou-llusionniste !");
	jokes.push_back("Pourquoi est-ce que les plongeurs plongent toujours en arrière et jamais en avant ? Parce que sinon ils tombent dans le bateau !");
	jokes.push_back("Qu'est-ce qu'un éclair qui tombe dans la mer ? Un poisson électrique !");
	jokes.push_back("Qu'est-ce qu'un chat dit quand il est surpris ? Miaou-ment !");
	jokes.push_back("Comment appelle-t-on un chat tombé dans un pot de peinture ? Un chat coloré !");
	jokes.push_back("Pourquoi les plongeurs plongent-ils toujours en arrière du bateau ? Parce que sinon ils tombent dans l'océan !");
	jokes.push_back("Qu'est-ce qu'un petit pois qui court dans un champ ? Un petit pois-son !");
	jokes.push_back("Qu'est-ce qu'une abeille qui fait du yoga ? Une abeille zen !");
	jokes.push_back("Comment appelle-t-on un chat qui aime la musique ? Un DJat !");
	jokes.push_back("Qu'est-ce qu'un ordinateur qui chante ? Un Dell-phin !");
	jokes.push_back("Pourquoi est-ce que les plongeurs plongent toujours en arrière du bateau ? Parce que sinon ils tombent à l'eau !");
	jokes.push_back("Qu'est-ce qu'un crocodile qui se fait arracher une dent ? Un croco-dentiste !");
	jokes.push_back("Qu'est-ce qu'un chien qui parle ? Un chien-tille !");
	jokes.push_back("Pourquoi les plongeurs plongent-ils toujours en arrière du bateau ? Parce que sinon ils tombent dans le bateau !");
	jokes.push_back("Qu'est-ce qu'un petit pois qui court dans un champ ? Un petit pois-son !");
	jokes.push_back("Qu'est-ce qu'une chauve-souris avec une bombe ? Une bom-bat !");
	jokes.push_back("Qu'est-ce qu'un chien qui fait du karaté ? Un chien-chop !");
	jokes.push_back("Pourquoi est-ce que les poissons n'aiment pas jouer au tennis ? Parce qu'ils ont peur des filets !");
	jokes.push_back("Qu'est-ce qu'un chien qui parle deux langues ? Un polyglotte !");
	jokes.push_back("Pourquoi est-ce que les plongeurs plongent toujours en arrière du bateau ? Parce que sinon ils tombent dans le bateau !");
	jokes.push_back("Qu'est-ce qu'un chat dit quand il est surpris ? Miaou-lignant !");
	jokes.push_back("Qu'est-ce qu'un éclair qui tombe dans la mer ? Un poisson pané !");
	jokes.push_back("Comment appelle-t-on un chat tombé dans un pot de peinture ? Un chat-peint !");
	jokes.push_back("Qu'est-ce qu'un chien qui aime la paix ? Un chien pacifiste !");
	jokes.push_back("Qu'est-ce qu'un petit pois qui court dans un champ ? Un petit pois-son !");
	jokes.push_back("Qu'est-ce qu'un oiseau qui adore les jeux vidéo ? Un Pékinois !");
	jokes.push_back("Pourquoi les plongeurs plongent-ils toujours en arrière du bateau ? Parce que sinon ils tombent dans l'océan !");
}
