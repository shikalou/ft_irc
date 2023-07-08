# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldinaut <ldinaut@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/08 14:12:40 by ldinaut           #+#    #+#              #
#    Updated: 2023/07/08 15:45:06 by ldinaut          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	julieng

SRCS_FILES	=	main.cpp Bot.cpp

SRCS	=	$(addprefix srcs/, $(SRCS_FILES))

INC_FILES	=	 Bot.hpp

#SRCS	=	$(addprefix ./, $(SRCS_FILES))

INCS	=	$(addprefix includes/, $(INC_FILES))

CXX	=	c++

CPPFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3 -pedantic -I includes/

OBJS_FILES	=	$(SRCS_FILES:%.cpp=%.o)

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

objs/%.o	: srcs/%.cpp $(INCS)
	mkdir -p objs
	mkdir -p objs/cmd_files
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $<

.PHONY: all clean fclean re
