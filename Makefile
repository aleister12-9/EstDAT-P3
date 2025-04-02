##########  Variables  ##########
CFLAGS = -Wall -pedantic -ansi 
CC = gcc

##########  General rules  ##########
all: p3_e1 p3_e2a

p3_e1: delivery.o vertex.o p3_e1.o
	@$(CC) $(CFLAGS) -o p3_e1 delivery.o vertex.o p3_e1.o -lqueue -L./
	@echo "--> p3_e1 executable succesfully created"

p3_e2a: delivery.o vertex.o p3_e2a.o queue.o
	@$(CC) $(CFLAGS) -o p3_e2a delivery.o vertex.o queue.o p3_e2a.o
	@echo "--> p3_e2a executable succesfully created"

##########  Object creation  ##########
delivery.o: delivery.h queue.h types.h vertex.h
	@$(CC) $(CFLAGS) -c delivery.c
	@echo "--> delivery module succesfully compiled"

vertex.o: vertex.h types.h
	@$(CC) $(CFLAGS) -c vertex.c
	@echo "--> vertex module succesfully compiled"

queue.o: queue.h
	@$(CC) $(CFLAGS) -c queue.c
	@echo "--> queue module succesfully compiled"

p3_e1.o: delivery.h queue.h types.h vertex.h
	@$(CC) $(CFLAGS) -c p3_e1.c
	@echo "--> p3_e1 succesfully compiled"

p3_e2a.o: delivery.h queue.h types.h vertex.h
	@$(CC) $(CFLAGS) -c p3_e2a.c
	@echo "--> p3_e2a succesfully compiled"

##########  Cleaning and execution  ##########
clean:
	@rm -f *.o
	@echo "--> all auxiliar files removed"
	@rm -f p3_e1 p3_e2a
	@echo "--> all executable files removed"

run_e1:
	@echo "--> running e1"
	@./p3_e1 requests.txt
	
runv_e1:
	@echo "--> running e1 with valgrind"
	@valgrind --leak-check=full ./p3_e1 requests.txt

run_e2a:
	@echo "--> running e2a"
	@./p3_e2a requests.txt

runv_e2a: 
	@echo "--> running e2a with valgrind"
	@valgrind --leak-check=full ./p3_e2a requests.txt