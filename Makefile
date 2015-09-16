CC=gcc
CFLAGS=-std=gnu99

uid2user: uid2user.c
	$(CC) $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f uid2user
