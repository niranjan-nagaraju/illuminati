
CC = gcc

CFLAGS = -Wall			 	\
	-DG_DISABLE_DEPRECATED 	 	\
	-DGDK_DISABLE_DEPRECATED 	\
	-DGDK_PIXBUF_DISABLE_DEPRECATED \
	-DGTK_DISABLE_DEPRECATED


illuminati: illuminati.o menubar.o toolbar.o colortable.o callbacks.o primitive.o fgbgselect.o
	$(CC)  -g illuminati.o menubar.o toolbar.o colortable.o callbacks.o primitive.o fgbgselect.o -o illuminati  `pkg-config --libs gtk+-2.0`

illuminati.o: illuminati.c illuminati.h
	$(CC) -g -c illuminati.c -o illuminati.o  `pkg-config gtk+-2.0 --cflags`

menubar.o: menubar.c illuminati.h
	$(CC) -g -c menubar.c -o menubar.o  `pkg-config gtk+-2.0 --cflags`

toolbar.o: toolbar.c illuminati.h
	$(CC) -g -c toolbar.c -o toolbar.o  `pkg-config gtk+-2.0 --cflags`

colortable.o: colortable.c illuminati.h
	$(CC) -g -c colortable.c -o colortable.o  `pkg-config gtk+-2.0 --cflags`

callbacks.o: callbacks.c illuminati.h
	$(CC) -g -c callbacks.c -o callbacks.o  `pkg-config gtk+-2.0 --cflags`

primitive.o: primitive.c illuminati.h
	$(CC) -g -c primitive.c -o primitive.o  `pkg-config gtk+-2.0 --cflags`

fgbgselect.o: fgbgselect.c illuminati.h
	$(CC) -g -c fgbgselect.c -o fgbgselect.o  `pkg-config gtk+-2.0 --cflags`


clean: 
	rm -f *.o 
