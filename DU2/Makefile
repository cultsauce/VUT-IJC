CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra
DEPEND = htab.h struct_htab.h
CC=gcc
LIBS_FUNC = htab_init.o htab_size.o htab_bucket_count.o htab_hash_function.o htab_lookup_add.o htab_resize.o htab_clear.o htab_erase.o htab_find.o htab_for_each.o htab_free.o   

all: wordcount wordcount-dynamic tail libhtab.a libhtab.so

wordcount: wordcount.o libhtab.a 
	$(CC) $(CFLAGS) $^ -o $@

wordcount-dynamic: wordcount.c libhtab.so 
	$(CC) -L. $(CFLAGS) wordcount.c -o $@ -lhtab

tail: tail.c
	$(CC) $(CFLAGS) tail.c -o $@

libhtab.a: $(LIBS_FUNC)
	ar rcs $@ $^

libhtab.so: $(LIBS_FUNC)
	$(CC) -shared -fPIC $^ -o $@ 

%.o : %.c $(DEPEND)
	$(CC) $(CFLAGS) -c -fPIC $<

clear:
	rm *.o tail wordcount wordcount-dynamic libhtab.a libhtab.so
