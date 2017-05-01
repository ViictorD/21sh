NAME = 21sh

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MFLAGS = -lft -ltermcap -g

INCLUDE_DIR = ./includes

DIR_OBJ = ./obj/

DIR_LIB = ./libft/

SRC_DIR = ./srcs/

MAIN =	main.c

FILES = add_char.c \
				arrows.c \
				ast_build.c \
				binary.c \
				cd2.c \
				check_brackets.c \
				copy_data.c \
				core.c \
				cursor.c \
				delete_char.c \
				env_utils.c \
				exit.c \
				ft_putcharint.c \
				get_line.c \
				history.c \
				history2.c \
				init_termcap.c \
				lexer.c \
				list.c \
				maj_arrows.c \
				parser.c \
				redirection_parser.c \
				second_prompt.c \
				second_prompt2.c \
				shell_loop.c \
				split_quot.c \
				termcap.c \
				trim_input.c
		#		setenv.c \#

OBJS = $(patsubst %.c, $(DIR_OBJ)%.o, $(FILES)) $(patsubst %.c, $(DIR_OBJ)%.o, $(MAIN))

DEP_OBJ = src_msg \
		  $(OBJS)

RM = /bin/rm -rf

all: mkdirobj $(DEP_OBJ)
		@ make -C $(DIR_LIB)
		@ /bin/echo -n "Archiving object in $(NAME):"
		@ $(CC) -o $(NAME) $(OBJS) $(MFLAGS) -L $(DIR_LIB)
		@ echo " \033[32mAll done!\033[0m"

$(DIR_OBJ)%.o: $(SRC_DIR)%.c
	@ /bin/echo -n "    $(notdir $@)"
	@ $(CC) $(CFLAGS) -c -o $@ $< -I $(INCLUDE_DIR)
	@ echo " \033[32mOK\033[0m"

mkdirobj:
	@ mkdir -p $(DIR_OBJ)

clean:
	@ make clean -C $(DIR_LIB)
	@ /bin/echo -n "Removing object files:"
	@ $(RM) $(DIR_OBJ)
	@ echo " \033[32mdone\033[0m"

fclean: clean
	@ make fclean -C $(DIR_LIB)
	@ /bin/echo -n "Removing library:"
	@ $(RM) $(NAME) 
	@ echo " \033[32mdone\033[0m"

re: fclean all

src_msg:
	@ echo " src functions:"

.PHONY : all clean fclean re
