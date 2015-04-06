CFLAGS=-Wall -g
LDFLAGS=-lstdc++

.cpp.o:
	gcc $(CFLAGS) -c $< -o $@

all: ini_util_test ini_pairs_test ini_groups_test ini_parser_test ini_config_test

ini_util_test: ini_util.cpp *.h
	gcc $(CFLAGS) $(LDFLAGS) ini_util.cpp  -DINI_UTIL_TEST -o ini_util_test

ini_pairs_test: ini_util.o ini_pairs.cpp *.h
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.cpp -DINI_PAIRS_TEST -o ini_pairs_test

ini_groups_test: ini_util.o ini_pairs.o ini_groups.cpp *.h
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.o ini_groups.cpp -DINI_GROUPS_TEST -o ini_groups_test

ini_parser_test: ini_util.o ini_pairs.o ini_groups.o ini_parser.cpp *.h
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.o ini_groups.o ini_parser.cpp -DINI_PARSER_TEST -o ini_parser_test

ini_config_test: ini_util.o ini_pairs.o ini_groups.o ini_parser.o ini_config.cpp *.h
	gcc $(CFLAGS) $(LDFLAGS)  ini_util.o ini_pairs.o ini_groups.o ini_parser.o ini_config.cpp \
	-DINI_CONFIG_TEST -o ini_config_test

clean:
	rm -f *test *.o

test:
	for t in *test; do echo "run $$t";./$$t;done
