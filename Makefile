##
## Makefile for make in /home/wawrzy-j/Documents/Projets/PSU/PSU_2015_zappy
## 
## Made by wawrzy-j
## Login   <wawrzy-j@epitech.net>
## 
## Started on  Mon Jun 13 11:30:44 2016 wawrzy-j
## Last update Mon Jun 13 18:17:04 2016 wawrzy-j
##

NAME	=	zappy

all: $(NAME)

$(NAME):
	make -C server/
	make -C client/

zappy_server:
	make -C server/

zappy_ai:
	make -C client/

zappy_graphic:
	make -C graphic/

clean:
	make clean -C server/
	make clean -C client/
	make clean -C graphic/

fclean:
	make fclean -C server/
	make fclean -C client/
	make fclean -C graphic/

re: fclean all
