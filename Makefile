##
## Makefile for nmobjdump in /home/nicolas/nmobjdump/
## 
## Made by Nicolas Guillon
## Login   <nicolas@epitech.net>
## 
## Started on  Wed Feb 22 10:55:02 2017 Nicolas Guillon
## Last update Mon Feb 27 10:15:13 2017 Nicolas Guillon
##

NAMENM	=	my_nm
NAMEOBJ	=	my_objdump

SRCSNM	=	./nm/nm.c \
		./nm/nm2.c \
		./nm/nm3.c \
		./nm/check_size.c \
		./nm/nm32/nm2_32.c \
		./nm/nm32/check_size_32.c \
		./nm/nm32/nm3_32.c \

SRCSOBJ	=	./objdump/objdump.c \
		./objdump/objdump2.c \
		./objdump/objdump3.c \
		./objdump/check_size.c \
		./objdump/objdump32/objdump2_32.c \
		./objdump/objdump32/check_size_32.c \
		./objdump/objdump32/objdump3_32.c \

CFLAGS	+=	-W -std=gnu11
CFLAGS	+=	-I includes

CC	=	gcc

RM	=	rm -f

OBJSNM	=	$(SRCSNM:.c=.o)
OBJSOBJ	=	$(SRCSOBJ:.c=.o)

all:		nm objdump

nm:		$(NAMENM)

objdump:	$(NAMEOBJ);

$(NAMENM):	$(OBJSNM)
		$(CC) $(OBJSNM) -o $(NAMENM) $(LDFLAGS)

$(NAMEOBJ):	$(OBJSOBJ)
		$(CC) $(OBJSOBJ) -o $(NAMEOBJ) $(LDFLAGS)

clean:
		$(RM) $(OBJSNM)
		$(RM) $(OBJSOBJ)

fclean:		clean
		$(RM) $(NAMENM)
		$(RM) $(NAMEOBJ)

re:		fclean all

.PHONY: all clean fclean re
