CFLAGS=-Wall -g
LDFLAGS=-lstdc++

.cpp.o:
	gcc $(CFLAGS) -c $< -o $@

all: ini_util_test ini_pairs_test ini_groups_test ini_parser_test ini_default_builder_test ini_tr2xml_builder_test ini_config_test

ini_util_test: ini_util.cpp
	gcc $(CFLAGS) $(LDFLAGS) ini_util.cpp  -DINI_UTIL_TEST -o ini_util_test

ini_pairs_test: ini_util.o ini_pairs.cpp
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.cpp -DINI_PAIRS_TEST -o ini_pairs_test

ini_groups_test: ini_util.o ini_pairs.o ini_groups.cpp 
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.o ini_groups.cpp -DINI_GROUPS_TEST -o ini_groups_test

ini_parser_test: ini_util.o ini_pairs.o ini_groups.o ini_default_builder.o ini_parser.cpp
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.o ini_groups.o ini_default_builder.o ini_parser.cpp \
	-DINI_PARSER_TEST -o ini_parser_test

ini_default_builder_test: ini_util.o ini_pairs.o ini_groups.o ini_default_builder.cpp
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_pairs.o ini_groups.o ini_default_builder.cpp \
	-DINI_DEFAULT_BUILDER_TEST -o ini_default_builder_test

ini_tr2xml_builder_test: ini_util.o ini_parser.o ini_tr2xml_builder.cpp
	gcc $(CFLAGS) $(LDFLAGS) ini_util.o ini_parser.o ini_tr2xml_builder.cpp \
	-DINI_TR2XML_BUILDER_TEST -o ini_tr2xml_builder_test

ini_config_test: ini_util.o ini_pairs.o ini_groups.o ini_default_builder.o ini_parser.o
	gcc $(CFLAGS) $(LDFLAGS)  ini_util.o ini_pairs.o ini_groups.o ini_default_builder.o ini_parser.o ini_config.cpp \
	-DINI_CONFIG_TEST -o ini_config_test

clean:
	rm -f *test *.o

test:
	for t in *test; do echo "run $$t";./$$t;done
vtest:
	for t in *test; do echo "run $$t ..."; valgrind --tool=memcheck --leak-check=full ./$$t;done
