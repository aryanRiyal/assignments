runS: server.o
	gcc server.o -o runS

server.o: server.c
	gcc -c server.c

runC: client.o
	gcc client.o -o runC

client.o: client.c
	gcc -c client.c

clean:
	rm *.o runS runC
