CC = gcc
OBJ = 
EXEC = coffcii
FLAGS = -g -Wall 
RM = rm

all: $(EXEC)

$(EXEC):$(OBJ) coffcii.o
	$(CC) $(FLAGS) $(OBJ) coffcii.o -o $(EXEC)

coffcii.o: coffcii.c
	$(CC) $(FLAGS) -c coffcii.c

clean:
	$(RM) $(OBJ) coffcii.o $(EXEC) 