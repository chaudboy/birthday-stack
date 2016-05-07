# Author: Lionel Jamaigne
# Creation Date: 10/03/2016
# Last Modified: 06/05/2016
# Last Modification:
# Known Issues:
# Version: 1.0

.SILENT:

OBJS = stack.o person.o chaudboy.o date.o aes256.o

# -w enlève les warnings
# -g ajoute des informations de debugging

GCC = gcc -g -std=c99

all: appli

appli:	main.c $(OBJS)
		echo creation de l appli
		$(GCC) -o appli main.c $(OBJS)

stack.o:	stack.c stack.h
			echo creation de stack.o
			$(GCC) -c stack.c

person.o:	person.c	person.h
			echo creation de person.o
			$(GCC) -c person.c

chaudboy.o:	chaudboy.c chaudboy.h
			echo creation de chaudboy.o
			$(GCC) -c chaudboy.c

date.o:		date.c date.h
			echo creation de date.o
			$(GCC) -c date.c

aes256.o:	aes256.c aes256.h
			echo creation de aes256.o
			$(GCC) -c aes256.c

licence.o:	licence.c licence.h
			echo creation de licence.o
			$(GCC) -c licence.c

clean:
		rm -f $(OBJS)

run:
	appli
