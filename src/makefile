compila: clean
	@echo COMPILANDO
	mkdir -p exec
	gcc -Wall -DLINUX lib/*.c main.c -o exec/agenda
	@echo COMPILADO

exe: compila
	./exec/agenda

clean:
	-rm -rf exec
