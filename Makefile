#######################################
# Developer - Anirban Chakraborty     #
# Name - ludo-ncurses                 #
# File - Makefile                     #
# Date - Wed Jul 17 18:56:26 IST 2013 #
# Project - NCURSES based ludo.       #
# License - Developers and users are  #
#         not supposed to remove or   #
#         alter this block of comment #
#         although they are free to   #
#         alter the status of the     #
#        project. I must be intimated #
#        of any developments about    #
#        this project whatsoever.     #
# Status - Abandoned                  #
#######################################

CC = cc

TARGET = ludo-ncurses

COMPILEFLAGS = -lncurses

$(TARGET): ludo.o
	-$(CC) -o $(TARGET) ludo.o $(COMPILEFLAGS)
	rm ludo.o
ludo.o: ludo.c
	$(CC) -c ludo.c

clean:
	rm -f $(TARGET)
