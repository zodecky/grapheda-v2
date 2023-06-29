# Treat NT and non-NT windows the same
ifeq ($(OS),Windows_NT)
	OS = Windows
endif

ifeq ($(OS),Windows)
	EXE = .exe
	DEL = del
else	#assume Linux/Unix
	EXE =
	DEL = rm -f
endif


run: grapheda$(EXE)
	./grapheda$(EXE)

grapheda$(EXE):	grapheda.o priorityqueue.o
	gcc grapheda.o priorityqueue.o -o grapheda$(EXE) -g

grapheda.o:	grapheda.c
	gcc -c grapheda.c -g 

priorityqueue.o: priorityqueue.c
	gcc -c priorityqueue.c -g

clean:
	$(DEL) *.o
	$(DEL) main$(EXE)
