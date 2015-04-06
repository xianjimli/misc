lib_LTLIBRARIES=libasm-common.la
libasm_common_la_SOURCES=asm-common.h asm-common.c \
	asm-wstr.c asm-wstr.h \
	asm-output-buffer.h asm-output-buffer.c \
	asm-input-buffer.c asm-input-buffer.h \
	asm-stream-socket.c asm-stream-socket.h \
	asm-stream.h \
	asm-handle-process.h  \
	asm-handle-dir.c      asm-handle-file.c     asm-handle.h \
	asm-handle-dir.h      asm-handle-file.h     asm-handle-process.c \
	asm-server.h          asm-server-socket.c  asm-server-socket.h \
	asm-handle-thread.c   asm-handle-thread.h

asmincludedir=${includedir}/asm
asminclude_HEADERS=\
	asm-common.h      asm-handle-file.h     asm-input-buffer.h   asm-server.h         asm-stream-socket.h\
	asm-connection.h  asm-handle.h          asm-macros.h         asm-server-socket.h  asm-types.h\
	asm-handle-dir.h  asm-handle-process.h  asm-output-buffer.h  asm-stream.h         asm-wstr.h \
	asm-handle-thread.h

noinst_PROGRAMS=common_test wstr_test output_buffer_test input_buffer_test buffer_test client_test server_test socket_server_test

common_test_SOURCES=asm-common.c
common_test_CFLAGS=-DASM_COMMON_TEST

wstr_test_SOURCES=asm-wstr.c asm-wstr.h
wstr_test_CFLAGS=-DASM_WSTR_TEST

output_buffer_test_SOURCES=asm-output-buffer.c asm-wstr.c asm-common.c
output_buffer_test_CFLAGS=-DASM_OUTPUT_BUFFER_TEST

input_buffer_test_SOURCES=asm-input-buffer.c asm-common.c
input_buffer_test_CFLAGS=-DASM_INPUT_BUFFER_TEST

buffer_test_SOURCES=buffer_test.c asm-input-buffer.c asm-wstr.c asm-output-buffer.c asm-common.c
buffer_test_CFLAGS=-g

client_test_SOURCES=asm-stream-socket.c asm-common.c
client_test_CFLAGS=-DSOCKET_CLIENT_TEST
server_test_SOURCES=asm-stream-socket.c asm-common.c
server_test_CFLAGS=-DSOCKET_SERVER_TEST

socket_server_test_SOURCES= asm-server-socket.c asm-stream-socket.c asm-common.c
socket_server_test_CFLAGS=-DSERVER_SOCKET_TEST

