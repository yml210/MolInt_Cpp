#Makefile for molint

QTLIB=-lqt -lqgl
GLLIB=-lGL -lGLU -lglut
MATHLIB=-lm -llapack -lblas -lf2c

LIB=$(QTLIB) $(GLLIB) $(MATHLIB)

CFLAGS=-DQT_INCLUDE_COMPAT -I/usr/include/qt4 -I/usr/include
LDFLAGS=-L/usr/lib -L/usr/lib/qt4 -L/usr/lib/x86_64-linux-gnu

CC=g++  $(CFLAGS) 
LD=g++ $(LDFLAGS)

OBJ=utility.o atom.o cluster.o moc_clusterView.o mydialog.o moc_mydialog.o \
	moc_dialog1.o dialog1.o moc_dialog2.o dialog2.o clusterView.o \
	moc_dialog3.o dialog3.o moc_canvas.o canvas.o moc_mainWin.o mainWin.o 

molint.exe: $(OBJ)
	$(LD) -o $@ $(OBJ) $(LIB)

atom.o:atom.cpp
	$(CC) -g -c atom.cpp

cluster.o:cluster.cpp
	$(CC) -g -c $?

clusterView.o:clusterView.cpp
	$(CC) -g -c $?

canvas.o:canvas.cpp
	$(CC) -g -c $?

mydialog.o:mydialog.cpp
	$(CC) -g -c $?

moc_mydialog.o:moc_mydialog.cpp
	$(CC) -g -c $?

dialog1.o:dialog1.cpp
	$(CC) -g -c $?

moc_dialog1.o:moc_dialog1.cpp
	$(CC) -g -c $?

dialog2.o:dialog2.cpp
	$(CC) -g -c $?

moc_dialog2.o:moc_dialog2.cpp
	$(CC) -g -c $?

dialog3.o:dialog3.cpp
	$(CC) -g -c $?

moc_dialog3.o:moc_dialog3.cpp
	$(CC) -g -c $?

utility.o:utility.cpp
	$(CC) -g -c $?

mainWin.o:mainWin.cpp
	$(CC) -g -c $?

moc_canvas.o:moc_canvas.cpp
	$(CC) -g -c $?

moc_clusterView.o:moc_clusterView.cpp
	$(CC) -g -c $?

moc_mainWin.o:moc_mainWin.cpp
	$(CC) -g -c $?

moc_canvas.cpp:canvas.h
	moc canvas.h > moc_canvas.cpp

moc_clusterView.cpp:clusterView.h
	moc clusterView.h > moc_clusterView.cpp

moc_mainWin.cpp:mainWin.h
	moc mainWin.h > moc_mainWin.cpp

moc_mydialog.cpp:mydialog.h
	moc $? > $@

moc_dialog1.cpp:dialog1.h
	moc $? > $@

moc_dialog2.cpp:dialog2.h
	moc $? > $@

moc_dialog3.cpp:dialog3.h
	moc $? > $@
