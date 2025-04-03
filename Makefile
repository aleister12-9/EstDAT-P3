##########  Variables  ##########
CFLAGS = -Wall -pedantic -ansi 
CC = gcc

##########  General rules  ##########
all: p3_e1 p3_e2a p3_e2b p3_e3

p3_e1: delivery.o vertex.o p3_e1.o
	@$(CC) $(CFLAGS) -o p3_e1 delivery.o vertex.o p3_e1.o -lqueue -L./
	@echo "--> p3_e1 executable succesfully created"

p3_e2a: delivery.o vertex.o p3_e2a.o queue.o
	@$(CC) $(CFLAGS) -o p3_e2a delivery.o vertex.o queue.o p3_e2a.o
	@echo "--> p3_e2a executable succesfully created"

p3_e2b: delivery.o vertex.o p3_e2b.o queue.o graph.o vertex.o stack.o
	@$(CC) $(CFLAGS) -o p3_e2b delivery.o queue.o p3_e2b.o graph.o vertex.o stack.o
	@echo "--> p3_e2b executable succesfully created"

p3_e3: list.o file_utils.o p3_e3.o
	@$(CC) $(CFLAGS) -o p3_e3 list.o file_utils.o p3_e3.o 
	@echo "--> p3_e3 executable succesfully created"

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

graph.o: graph.h vertex.h types.h stack.h queue.h
	@$(CC) $(CFLAGS) -c graph.c
	@echo "--> graph module succesfully compiled"

stack.o: stack.h types.h
	@$(CC) $(CFLAGS) -c stack.c
	@echo "--> stack module succesfully compiled"

list.o: list.h types.h
	@$(CC) $(CFLAGS) -c list.c
	@echo "--> list module succesfully compiled"

file_utils.o: file_utils.h
	@$(CC) $(CFLAGS) -c file_utils.c
	@echo "--> file_utils module succesfully compiled"

p3_e1.o: delivery.h queue.h types.h vertex.h
	@$(CC) $(CFLAGS) -c p3_e1.c
	@echo "--> p3_e1 succesfully compiled"

p3_e2a.o: delivery.h queue.h types.h vertex.h
	@$(CC) $(CFLAGS) -c p3_e2a.c
	@echo "--> p3_e2a succesfully compiled"

p3_e2b.o: delivery.h queue.h types.h graph.h vertex.h
	@$(CC) $(CFLAGS) -c p3_e2b.c
	@echo "--> p3_e2b succesfully compiled"

p3_e3.o: list.o
	@$(CC) $(CFLAGS) -c p3_e3.c
	@echo "--> p3_e3 succesfully compiled"

##########  Cleaning and execution  ##########
clean:
	@rm -f *.o
	@echo "--> object files removed"
	@rm -f p3_e1 p3_e2a p3_e2b p3_e3
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

