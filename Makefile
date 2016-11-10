C = gcc
C_FLAGS = -g -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
DEFAULT = TPLista
OBJ_LISTA = lista
OBJ_PILA = pila
OBJ_COLA = cola
OBJ_TESTING  = testing
OBJS =  $(OBJ_LISTA).o $(OBJ_PILA).o $(OBJ_COLA).o $(OBJ_TESTING).o
VALGRIND = valgrind
V_FLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

all: clean $(DEFAULT)

$(DEFAULT): $(OBJS)
		$(CC) $(C_FLAGS) main.c $(OBJS) pruebas_alumno.c  -o $(DEFAULT)

$(OBJ_LISTA).o: $(OBJ_LISTA).c $(OBJ_LISTA).h
		$(CC) $(C_FLAGS) $(OBJ_LISTA).c -c

$(OBJ_TESTING): $(OBJ_TESTING).c $(OBJ_TESTING).h
		$(CC) $(C_FLAGS) $(OBJ_TESTING).c -c

$(OBJ_COLA).o: $(OBJ_COLA).c $(OBJ_COLA).h
		$(CC) $(C_FLAGS) $(OBJ_COLA).c -c

$(OBJ_PILA).o: $(OBJ_PILA).c $(OBJ_PILA).h
		$(CC) $(C_FLAGS) $(OBJ_PILA).c -c

run: $(DEFAULT)
		$(VALGRIND) $(V_FLAGS) ./$(DEFAULT)

clean_obj:
		rm -f *.o

clean: clean_obj
		rm -f $(DEFAULT)
