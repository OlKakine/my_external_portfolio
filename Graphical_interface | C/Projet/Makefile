# Variable definitions.

PLATFORM	= $(shell uname)
CC		= gcc
OBJDIR		= ./objs
TESTS		= ./tests
INCLUDES	= ./include
SRC 		= ./src
INCFLAGS	:= -I${INCLUDES} -I${TESTS}
#OPTFLAGS	:= -Os -DNDEBUG
OPTFLAGS	:= -g
CCFLAGS		:= -c ${OPTFLAGS} -Wall -std=c99

# The list of objects to include in the library

LIBEIOBJS	:= 	



# Platform specific definitions (OS X, Linux)

ifeq (${PLATFORM},Darwin)

# Building for Mac OS X

	PLATDIR		= _osx
	INCFLAGS	:= ${INCFLAGS} -I/opt/local/include/SDL
	LINK		= ${CC}
	LIBEI		= ${OBJDIR}/libei.a
	LIBEIBASE	= ${PLATDIR}/libeibase.a
	LIBS		= ${LIBEIBASE} -L/opt/local/lib -lSDL -lSDL_ttf -lSDL_image -framework AppKit
	CCFLAGS		:= ${CCFLAGS} -D__OSX__

else

# Building for Linux

	PLATDIR		= _x11
	INCFLAGS	:= ${INCFLAGS} -I/usr/include/SDL
	LINK		= ${CC}
#	ARCH	        = 32
	ARCH	        = 64
	LIBEI		= ${OBJDIR}/libei.a
	LIBEIBASE	= ${PLATDIR}/libeibase${ARCH}.a
	LIBS		= ${LIBEIBASE} -lSDL -lSDL_ttf -lSDL_image -lm
	CCFLAGS		:= ${CCFLAGS} -D__LINUX__ -m${ARCH}
	LDFLAGS		= -m${ARCH} -g

endif

# principal common .c used to compile

ALL_DRAWS=${OBJDIR}/ei_event.o ${OBJDIR}/ei_application.o ${OBJDIR}/ei_draw.o ${OBJDIR}/ei_placer.o ${OBJDIR}/ei_widget.o ${OBJDIR}/ei_widgetclass.o 

# Main target of the makefile. To build specific targets, call "make <target_name>"

TARGETS		=	${LIBEI} \
			minimal lines frame button hello_world puzzle two048 polyline draw_button draw_toplevel
all : ${TARGETS}



########## Test-programs

# polyline

polyline : ${OBJDIR}/polyline.o ${OBJDIR}/ei_draw.o ${LIBEIBASE}
	${LINK} -o polyline ${LDFLAGS} ${OBJDIR}/ei_draw.o ${OBJDIR}/polyline.o ${LIBS}

${OBJDIR}/polyline.o : ${TESTS}/polyline.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/polyline.c -o ${OBJDIR}/polyline.o

# minimal

minimal : ${OBJDIR}/minimal.o ${LIBEIBASE}
	${LINK} -o minimal ${LDFLAGS} ${OBJDIR}/minimal.o ${LIBS}

${OBJDIR}/minimal.o : ${TESTS}/minimal.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/minimal.c -o ${OBJDIR}/minimal.o

# lines

lines : ${OBJDIR}/lines.o ${OBJDIR}/ei_draw.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o lines ${OBJDIR}/lines.o ${OBJDIR}/ei_draw.o ${LIBEI} ${LIBS}


${OBJDIR}/lines.o : ${TESTS}/lines.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/lines.c -o ${OBJDIR}/lines.o



# frame

frame : ${OBJDIR}/frame.o ${OBJDIR}/ei_application.o ${OBJDIR}/ei_event.o ${OBJDIR}/ei_draw.o ${OBJDIR}/ei_placer.o ${OBJDIR}/ei_widget.o ${OBJDIR}/ei_widgetclass.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o frame ${LDFLAGS} ${OBJDIR}/frame.o ${OBJDIR}/ei_event.o ${OBJDIR}/ei_application.o ${OBJDIR}/ei_draw.o ${OBJDIR}/ei_placer.o ${OBJDIR}/ei_widget.o ${OBJDIR}/ei_widgetclass.o ${LIBEI} ${LIBS}

${OBJDIR}/frame.o : ${TESTS}/frame.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/frame.c -o ${OBJDIR}/frame.o

#draw_toplevel

draw_toplevel : ${OBJDIR}/draw_toplevel.o ${OBJDIR}/ei_event.o ${OBJDIR}/ei_application.o ${OBJDIR}/ei_draw.o ${OBJDIR}/ei_placer.o ${OBJDIR}/ei_widget.o ${OBJDIR}/ei_widgetclass.o ${LIBEIBASE} ${LIBEI}
	${LINK} -o draw_toplevel ${LDFLAGS} ${OBJDIR}/ei_event.o ${OBJDIR}/draw_toplevel.o ${OBJDIR}/ei_application.o ${OBJDIR}/ei_draw.o ${OBJDIR}/ei_placer.o ${OBJDIR}/ei_widget.o ${OBJDIR}/ei_widgetclass.o ${LIBEI} ${LIBS}

${OBJDIR}/draw_toplevel.o : ${TESTS}/draw_toplevel.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/draw_toplevel.c -o ${OBJDIR}/draw_toplevel.o

# draw_button

draw_button : ${OBJDIR}/draw_button.o ${OBJDIR}/ei_event.o ${LIBEIBASE} ${LIBEI} ${OBJDIR}/ei_draw.o ${OBJDIR}/ei_placer.o ${OBJDIR}/ei_widget.o ${OBJDIR}/ei_widgetclass.o ${OBJDIR}/ei_application.o
	${LINK} -o draw_button ${LDFLAGS} ${OBJDIR}/draw_button.o ${OBJDIR}/ei_event.o ${OBJDIR}/ei_placer.o ${OBJDIR}/ei_draw.o ${OBJDIR}/ei_widgetclass.o ${OBJDIR}/ei_widget.o ${OBJDIR}/ei_application.o ${LIBEI} ${LIBS}

${OBJDIR}/draw_button.o : ${TESTS}/draw_button.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/draw_button.c -o ${OBJDIR}/draw_button.o

# button

button : ${OBJDIR}/button.o ${ALL_DRAWS} ${LIBEIBASE} ${LIBEI}
	${LINK} -o button ${LDFLAGS} $< ${ALL_DRAWS} ${LIBEI} ${LIBS}

${OBJDIR}/button.o : ${TESTS}/button.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/button.c -o ${OBJDIR}/button.o

# hello_world

hello_world : ${OBJDIR}/hello_world.o ${ALL_DRAWS} ${LIBEIBASE} ${LIBEI}
	${LINK} -o hello_world ${LDFLAGS} ${ALL_DRAWS} ${OBJDIR}/hello_world.o ${LIBEI} ${LIBS}

${OBJDIR}/hello_world.o : ${TESTS}/hello_world.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/hello_world.c -o ${OBJDIR}/hello_world.o

# puzzle

puzzle : ${OBJDIR}/puzzle.o ${ALL_DRAWS} ${LIBEIBASE} ${LIBEI}
	${LINK} -o puzzle ${LDFLAGS} ${ALL_DRAWS} ${OBJDIR}/puzzle.o ${LIBEI} ${LIBS}

${OBJDIR}/puzzle.o : ${TESTS}/puzzle.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/puzzle.c -o ${OBJDIR}/puzzle.o


# two048

two048 : ${OBJDIR}/two048.o ${ALL_DRAWS} ${LIBEIBASE} ${LIBEI}
	${LINK} -o two048 ${LDFLAGS} ${ALL_DRAWS} ${OBJDIR}/two048.o ${LIBEI} ${LIBS}

${OBJDIR}/two048.o : ${TESTS}/two048.c
	${CC} ${CCFLAGS} ${INCFLAGS} ${TESTS}/two048.c -o ${OBJDIR}/two048.o


${OBJDIR}/%.o : ${SRC}/%.c
	${CC} ${CCFLAGS} ${INCFLAGS} $< -o $@

# Building of the library libei

${LIBEI} : ${LIBEIOBJS}
	ar rcs ${LIBEI} ${LIBEIOBJS}



# Building of the doxygen documentation.

doc :
	doxygen docs/doxygen.cfg



# Removing all built files.

clean:
	rm -f ${TARGETS}
	rm -f *.exe
	rm -f ${OBJDIR}/*
