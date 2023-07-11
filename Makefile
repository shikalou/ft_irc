# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mcouppe <mcouppe@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/23 11:58:02 by ldinaut           #+#    #+#              #
#    Updated: 2023/07/06 19:10:12 by mcouppe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ircserv

SRCS_FILES	=	main.cpp Client.cpp Server.cpp cmd_files/Commands.cpp cmd_files/join.cpp \
				cmd_files/privmsg.cpp cmd_files/mode.cpp cmd_files/invite.cpp \
				Channel.cpp ft_error.cpp cmd_files/topic.cpp cmd_files/quit.cpp \
				cmd_files/kick.cpp verif_functions.cpp cmd_files/kill.cpp	cmd_files/part.cpp \

SRCS	=	$(addprefix srcs/, $(SRCS_FILES))

INC_FILES	=	 Client.hpp Server.hpp Commands.hpp Channel.hpp Colors.hpp ft_error.hpp

#SRCS	=	$(addprefix ./, $(SRCS_FILES))

INCS	=	$(addprefix includes/, $(INC_FILES))

CXX	=	c++

CPPFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3 -pedantic -I includes/

OBJS_FILES	=	$(SRCS_FILES:%.cpp=%.o)

OBJ_DIR =	objs/
OBJS	=	$(addprefix $(OBJ_DIR), $(OBJS_FILES))

DEP		=	$(OBJS:%.o=%.d)

all	:	$(NAME)

$(NAME)	:	$(OBJS)
	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS)


clean	:
	rm -rf $(OBJ_DIR)

fclean	:	clean
	rm -rf $(NAME)

re	:	fclean all

-include $(DEP)

objs/%.o	: srcs/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) -MMD -o $@ -c $<

$(OBJ_DIR):
	mkdir -p objs/cmd_files

.PHONY: all clean fclean re
