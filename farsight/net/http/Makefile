CFLAGS=-Wall -g
LDFLAGS=-lstdc++

.cpp.o:
	gcc $(CFLAGS) -c $< -o $@

all: http_util_test http_url_test http_headers_test http_request_test http_response_test http_stream_factory_test http_client_test

http_util_test: http_util.cpp
	gcc $(CFLAGS) $(LDFLAGS) http_util.cpp  -DHTTP_UTIL_TEST -o http_util_test

http_url_test: http_url.cpp
	gcc $(CFLAGS) $(LDFLAGS) http_url.cpp  -DHTTP_URL_TEST -o http_url_test

http_headers_test: http_url.o http_util.o http_headers.cpp
	gcc $(CFLAGS) $(LDFLAGS) http_url.o http_util.o http_headers.cpp  -DHTTP_HEADERS_TEST -o http_headers_test

http_request_test: http_url.o http_util.o http_headers.o http_request.cpp
	gcc $(CFLAGS) $(LDFLAGS) http_url.o http_util.o http_headers.o  http_request.cpp -DHTTP_REQUEST_TEST -o http_request_test

http_response_test: http_url.o http_util.o http_headers.o http_response.cpp
	gcc $(CFLAGS) $(LDFLAGS) http_url.o http_util.o http_headers.o  http_response.cpp -DHTTP_RESPONSE_TEST -o http_response_test

http_stream_factory_test: http_url.o http_util.o http_socket_stream.o http_stream_factory.cpp
	gcc $(CFLAGS) $(LDFLAGS) http_url.o http_util.o http_socket_stream.o http_stream_factory.cpp \
	-DHTTP_STREAM_FACTORY_TEST -o http_stream_factory_test

http_client_test: http_url.o http_util.o http_socket_stream.o http_stream_factory.o http_headers.o http_request.o http_response.o http_client.cpp
	gcc $(CFLAGS) $(LDFLAGS) http_url.o http_util.o http_socket_stream.o http_stream_factory.o \
	http_headers.o http_request.o http_response.o http_client.cpp \
	-DHTTP_CLIENT_TEST -o http_client_test

clean:
	rm -f *test *.o

test:
	for t in *test; do echo "run $$t";./$$t;done
vtest:
	for t in *test; do echo "run $$t ..."; valgrind --tool=memcheck --leak-check=full ./$$t;done
