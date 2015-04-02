CFLAGS = -O -Wall -W -g

PORT = 30101
PORTFLAG = -DPORT=$(PORT)

battle: battle_server.c set_up_server.o client_handle.o
	gcc $(CFLAGS) -o $@ $^

game_control.o: game_control.c game_control.h
	gcc $(CFLAGS) -o $@ game_control.c

client_handle.o: client_handle.c client_handle.h
	gcc $(CFLAGS) -c client_handle.c

set_up_server.o: set_up_server.c set_up_server.h
	gcc $(CFLAGS) $(PORTFLAG) -c set_up_server.c

clean:
	rm battle *.o 
