# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 11:58:02 by ldinaut           #+#    #+#              #
#    Updated: 2023/06/29 18:57:10 by ldinaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ircserv

SRCS	=	main.cpp Client.cpp Server.cpp Commands.cpp Channel.cpp ft_error.cpp 

INCS	=	 Client.hpp Server.hpp Commands.hpp Channel.hpp

#SRCS	=	$(addprefix ./, $(SRCS_FILES))

#INCS	=	$(addprefix ./, $(INC_FILES))

CXX	=	c++

CPPFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3 -pedantic -I .

OBJS_FILES	=	$(SRCS:%.cpp=%.o)

OBJS	=	$(addprefix objs/, $(OBJS_FILES))

DEP		=	$(OBJS:%.o=%.d)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)

clean	:
	rm -rf $(OBJS) $(DEP)
	rm -rf objs/

fclean	:	clean
	rm -rf $(NAME)

re	:	fclean all

objs/%.o	: %.cpp $(INCS)
	mkdir -p objs
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $<

.PHONY: all clean fclean re
