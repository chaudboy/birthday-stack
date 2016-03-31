# Author: Lionel Jamaigne
# Creation Date: 10/03/2016
# Last Modified: 15/03/2016
# Last Modification:
# Known Issues:
# Version: 1.0

.SILENT:

OBJS = stack.o birthday.o chaudboy.o

GCC = gcc -std=c99

all: appli

appli:	main.c $(OBJS)
		echo creation de l appli
		$(GCC) -o appli main.c $(OBJS)

stack.o:	stack.c stack.h
			echo creation de stack.o
			$(GCC) -c stack.c

birthday.o:	birthday.c	birthday.h
			echo creation de birthday.o
			$(GCC) -c birthday.c

chaudboy.o:	chaudboy.c chaudboy.h
			echo creation de chaudboy.o
			$(GCC) -c chaudboy.c

clean:	rm *.o
