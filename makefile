CC = gcc

TARGET = server client

all: $(TARGET)

client:client.c
	$(CC) -g -Wall -o client client.c

server:server.c
	$(CC) -g -Wall -o server server.c

clean:
	rm client server
