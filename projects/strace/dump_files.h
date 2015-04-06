/*
 * save write/writev/read/readv to files.
 * Author: Li XianJing <xianjimli@hotmail.com>
 *
 **/

#ifndef DUMP_FILES_H
#define DUMP_FILES_H

int strace_remove_file(int fd);
int strace_add_file(int fd, const char* name, int pid);
int strace_dump_write(int fd, void* buff, size_t len);
int strace_dump_read(int fd, void* buff, size_t len);

#endif/*DUMP_FILES_H*/

