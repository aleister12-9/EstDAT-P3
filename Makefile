##########  Variables  ##########
CFLAGS = -Wall -pedantic -ansi 
CC = gcc

##########  General rules  ##########
all: delivery.o file_utils.o vertex.o p3_e1.o p3_e1

p3_e1: delivery.o file_utils.o vertex.o p3_e1.o
	@$(CC) -o p3_e1 delivery.o file_utils.o vertex.o p3_e1.o -lqueue -L./
	@echo "--> executable succesfully created"

##########  Object creation  ##########
delivery.o: delivery.h queue.h types.h vertex.h
	@$(CC) -c delivery.c
	@echo "--> delivery module succesfully compiled"

file_utils.o: file_utils.h types.h
	@$(CC) -c file_utils.c
	@echo "--> file_utils module succesfully compiled"

vertex.o: vertex.h types.h
	@$(CC) -c vertex.c
	@echo "--> vertex module succesfully compiled"

p3_e1.o: delivery.h queue.h types.h vertex.h
	@$(CC) -c p3_e1.c
	@echo "--> p3_e1 succesfully compiled"

##########  Cleaning and execution  ##########
clean:
	@rm -f *.o p3_e1
	@echo "--> all auxiliar files removed"

run_e1:
	@echo "--> running e1"
	@./p3_e1 requests.txt
	

runv_e1:
	@echo "--> running e1"
	@valgrind --leak-check=full ./p3_e1 requests.txt
	


