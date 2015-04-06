CFLAGS=-Wall -g
LDFLAGS=-lstdc++

.c.o:
	gcc $(CFLAGS) -c $< -o $@

elfs: elfs-gen elfs-merger elfs-gen-doc
elfs-gen: staticlib
	gcc $(CFLAGS) -I./ elfs-gen.c ./libiniconfig.a  -o elfs-gen
elfs-gen-doc: staticlib
	gcc $(CFLAGS) -I./ elfs-gen-doc.c ./libiniconfig.a  -o elfs-gen-doc

elfs-merger: staticlib
	gcc $(CFLAGS) -I./ elfs-merger.c ./libiniconfig.a -o elfs-merger

all: ini_util_test ini_pairs_test ini_groups_test ini_parser_test ini_config_test so

ini_util_test: ini_util.c
	gcc $(CFLAGS) $(LDFLAGS) ini_util.c  -DINI_UTIL_TEST -o ini_util_test

ini_pairs_test: ini_util.o ini_pairs.c
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.c -DINI_PAIRS_TEST -o ini_pairs_test

ini_groups_test: ini_util.o ini_pairs.o ini_groups.c 
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.o ini_groups.c -DINI_GROUPS_TEST -o ini_groups_test

ini_parser_test: ini_util.o ini_pairs.o ini_groups.o ini_parser.c
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.o ini_groups.o ini_parser.c -DINI_PARSER_TEST -o ini_parser_test

ini_config_test: ini_util.o ini_pairs.o ini_groups.o ini_parser.o
	gcc $(CFLAGS) $(LDFLAGS)  ini_util.o ini_pairs.o ini_groups.o ini_parser.o ini_config.c \
	-DINI_CONFIG_TEST -o ini_config_test

so:
	gcc -g $(LDFLAGS) -shared ini*.c -o libiniconfig.so

staticlib:ini_config.o  ini_groups.o  ini_pairs.o  ini_parser.o  ini_util.o
	ar cr  libiniconfig.a ini*.o

app: so
	gcc $(CFLAGS) -L./ -liniconfig zoneinfo.c -o zoneinfo_test

clean:
	rm -f *test *.o *.so *.a
	
test:
	for t in *test; do echo "run $$t";./$$t;done
vtest:
	for t in *test; do echo "run $$t ..."; valgrind --tool=memcheck --leak-check=full ./$$t;done
