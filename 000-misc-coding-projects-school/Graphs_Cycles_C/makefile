#Aman Hogan-Bailey 1001830469 Coding Assignment 7

SRC1 = Code7_1001830469.c
SRC2 = DrawTool.c
SRC3 = ListLib.c
SRC4 = FileLib.c


OBJ1 = $(SRC1:.c=.o)
OBJ2 = $(SRC2:.c=.o)
OBJ3 = $(SRC3:.c=.o)
OBJ4 = $(SRC4:.c=.o)


EXE = $(SRC1:.c=.e)

CFLAGS = -g

all : $(EXE)
 
$(EXE): $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) 
	gcc $(CFLAGS) $(OBJ1) $(OBJ2) $(OBJ3) $(OBJ4) -o $(EXE) 

$(OBJ1) : $(SRC1)
	gcc -c $(CFLAGS) $(SRC1) -o $(OBJ1)
	
$(OBJ2) : $(SRC2)
	gcc -c $(CFLAGS) $(SRC2) -o $(OBJ2)
	
$(OBJ3) : $(SRC3)
	gcc -c $(CFLAGS) $(SRC3) -o $(OBJ3)
	
$(OBJ4) : $(SRC4)
	gcc -c $(CFLAGS) $(SRC4) -o $(OBJ4)