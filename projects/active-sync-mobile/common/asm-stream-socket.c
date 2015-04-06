/*
 * File:    asm-stream-socket.c
 * Author:  Li XianJing <lixianjing@broncho.org>
 * Brief:   
 *
 * Copyright (c) 2008 topwise, Inc.
 *
 * Licensed under the Academic Free License version 2.1
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * History:
 * ================================================================
 * 2008-01-28 Li XianJing <lixianjing@topwisesz.com> created
 *
 */

#include <errno.h>
#include <sys/select.h>
#include <asm-stream-socket.h>

typedef struct _PrivInfo
{
	int sock_no;
	unsigned int rto_seconds;
	unsigned int wto_seconds;

	AsmHookProgressFunc on_read_progress;
	void*               on_read_progress_ctx;

	AsmHookProgressFunc on_write_progress;
	void*               on_write_progress_ctx;
}PrivInfo;

static AsmRet asm_stream_socket_wait_for_read(AsmStream* thiz)
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);

	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	fd_set readset= {0};
	FD_ZERO(&readset);
	
	struct timeval tv = {0};
	tv.tv_sec = priv->rto_seconds;

	FD_SET(priv->sock_no, &readset);
	int result = select(priv->sock_no + 1, &readset, NULL, NULL, &tv);
	
	if(result <= 0)
	{
		printf("%s:%d select(%d %d) return(%d)\n", __func__, __LINE__, priv->sock_no, priv->rto_seconds, result);
	}

	return result > 0 ? ASM_RET_OK : ASM_RET_FAIL;
}

static AsmRet asm_stream_socket_read(AsmStream* thiz, void* buffer, unsigned int length, unsigned int* real_length)
{
	int ret = 0;
	size_t offset = 0;
	size_t bytes_left = 0;
	
	asm_return_val_if_fail(thiz != NULL && buffer != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	int sock_no = priv->sock_no;
	asm_return_val_if_fail(ASM_IS_SOCKET_VALID(sock_no), ASM_RET_FAIL);

	bytes_left = length;
	
	asm_call_on_progress(priv->on_read_progress, priv->on_read_progress_ctx, length - bytes_left, length);
	do
	{
		if((ret = asm_stream_socket_wait_for_read(thiz)) != ASM_RET_OK)
		{
			*real_length = (length - bytes_left);
			return ret;
		}

		ret = recv(sock_no, buffer+offset, bytes_left, 0);
//		printf("%s:%d sock_no=%d offset=%d bytes_left=%d ret=%d errno=%d\n", 
//			__func__, __LINE__, sock_no, offset, bytes_left, ret, errno);
		if(ret >= 0)
		{
			bytes_left -= ret;
			offset += ret;
		}
		asm_call_on_progress(priv->on_read_progress, priv->on_read_progress_ctx, length - bytes_left, length);

	}while(ret > 0 && bytes_left > 0);

	if(real_length != NULL)
	{
		*real_length = (length - bytes_left);
	}

//	printf("%s: ret=%d length=%d real_length=%d\n", __func__, ret, length, *real_length);
	return ret <= 0 ? ASM_RET_EOF : ASM_RET_OK;
}

static AsmRet asm_stream_socket_write(AsmStream* thiz, void* buffer, unsigned int length, unsigned int* real_length)
{
	int ret = 0;
	size_t offset = 0;
	size_t bytes_left = 0;
	
	asm_return_val_if_fail(thiz != NULL && buffer != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	int sock_no = priv->sock_no;
	asm_return_val_if_fail(ASM_IS_SOCKET_VALID(sock_no), ASM_RET_FAIL);
	
	bytes_left = length;
	asm_call_on_progress(priv->on_read_progress, priv->on_read_progress_ctx, length - bytes_left, length);
	do
	{
		ret = send(sock_no, buffer+offset, bytes_left, 0);
		if(ret >= 0)
		{
			bytes_left -= ret;
			offset += ret;
		}
		asm_call_on_progress(priv->on_read_progress, priv->on_read_progress_ctx, length - bytes_left, length);

	}while(ret > 0 && bytes_left > 0);

	if(real_length != NULL)
	{
		*real_length = (length - bytes_left);
	}

	return ret <= 0 ? ASM_RET_EOF : ASM_RET_OK;
}

static AsmRet asm_stream_socket_flush(AsmStream* thiz )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	return ASM_RET_OK;
}

static int asm_stream_socket_get_fd(AsmStream* thiz)
{
	asm_return_val_if_fail(thiz != NULL, -1);
	PrivInfo* priv = (PrivInfo*)thiz->priv;
	
	return priv->sock_no;
}

static AsmRet asm_stream_socket_set_time_out(AsmStream* thiz, unsigned int rto_seconds, unsigned int wto_seconds )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	if(rto_seconds > 0)
	{
		priv->rto_seconds = rto_seconds;
	}

	if(wto_seconds > 0)
	{
		priv->wto_seconds = wto_seconds;
	}
	
	return ASM_RET_OK;
}

static AsmRet asm_stream_socket_hook_write_progress(AsmStream* thiz, AsmHookProgressFunc on_progress, void* on_progress_ctx )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->on_read_progress = on_progress;
	priv->on_read_progress_ctx = on_progress_ctx;

	return ASM_RET_OK;
}

static AsmRet asm_stream_socket_hook_read_progress(AsmStream* thiz, AsmHookProgressFunc on_progress, void* on_progress_ctx )
{
	asm_return_val_if_fail(thiz != NULL, ASM_RET_FAIL);
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->on_write_progress = on_progress;
	priv->on_write_progress_ctx = on_progress_ctx;

	return ASM_RET_OK;
}

void asm_stream_socket_destroy(AsmStream* thiz)
{
	if(thiz != NULL)
	{
		PrivInfo* priv = (PrivInfo*)thiz->priv;
		if(ASM_IS_SOCKET_VALID(priv->sock_no))
		{
			close(priv->sock_no);
		}

		ASM_FREE(thiz);
	}

	return;
}

AsmStream* asm_stream_socket_create(int sock_no)
{
	asm_return_val_if_fail(ASM_IS_SOCKET_VALID(sock_no), NULL);

	AsmStream* thiz = (AsmStream*)ASM_ALLOC(AsmStream, sizeof(PrivInfo));
	PrivInfo* priv = (PrivInfo*)thiz->priv;

	priv->sock_no = sock_no;
	priv->rto_seconds = 3600;
	priv->wto_seconds = 3600;

	thiz->read         = asm_stream_socket_read;
	thiz->write        = asm_stream_socket_write;
	thiz->flush        = asm_stream_socket_flush;
	thiz->get_fd       = asm_stream_socket_get_fd;
	thiz->destroy      = asm_stream_socket_destroy;
	thiz->set_time_out = asm_stream_socket_set_time_out;
	thiz->hook_write_progress = asm_stream_socket_hook_write_progress;
	thiz->hook_read_progress  = asm_stream_socket_hook_read_progress;

	return thiz;
}

AsmStream* asm_stream_client_socket_create(const char* host, int port)
{
	int sock_no = socket_connect(host, port);

	return asm_stream_socket_create(sock_no);
}

AsmStream* asm_stream_server_socket_create(int listen_sock_no)
{
	int sock_no = socket_accept(listen_sock_no);

	return asm_stream_socket_create(sock_no);
}

#if defined(SOCKET_CLIENT_TEST) || defined(SOCKET_SERVER_TEST)

static void on_progress(void* ctx, int progress, int total)
{
	printf("%s:%d: %d of %d\n", __func__, __LINE__, progress, total);

	return;
}

#define TEST_PORT 9999
#define TEST_NR 100

#endif

#ifdef SOCKET_CLIENT_TEST

static char test_data[1024*1024] = {[1024]='a',};

int main(int argc, char* argv[])
{
	size_t i = 0;
	size_t length = sizeof(test_data);
	char* data_ret = (char*)malloc(length);
	size_t real_length = 0;

	AsmStream* stream = asm_stream_client_socket_create("localhost", TEST_PORT);
	printf("%s:%d socket=%d\n", __func__, __LINE__, asm_stream_get_fd(stream));
	asm_stream_hook_read_progress(stream, on_progress, NULL);
	asm_stream_hook_write_progress(stream, on_progress, NULL);
	
	for(i = 0; i < TEST_NR; i++)
	{
		assert(asm_stream_write(stream, test_data, length, &real_length) == ASM_RET_OK);
		assert(length == real_length);
		assert(asm_stream_read(stream, data_ret, length, &real_length) == ASM_RET_OK);
		assert(length == real_length && memcmp(test_data, data_ret, length) == 0);
	}

	asm_stream_destroy(stream);

	return 0;
}
#endif

#ifdef SOCKET_SERVER_TEST
static char test_data[1024*1024] = {[1024]='a',};

int main(int argc, char* argv[])
{
	size_t i = 0;
	size_t length = sizeof(test_data);
	char* data_ret = (char*)malloc(length);
	size_t real_length = 0;

	int sock_no = socket_listen(TEST_PORT);
	AsmStream* stream = asm_stream_server_socket_create(sock_no);
	printf("%s:%d socket=%d\n", __func__, __LINE__, asm_stream_get_fd(stream));
	asm_stream_hook_read_progress(stream, on_progress, NULL);
	asm_stream_hook_write_progress(stream, on_progress, NULL);

	for(i = 0; i < TEST_NR; i++)
	{
		assert(asm_stream_read(stream, data_ret, length, &real_length) == ASM_RET_OK);
		assert(length == real_length && memcmp(test_data, data_ret, length) == 0);
		assert(asm_stream_write(stream, test_data, length, &real_length) == ASM_RET_OK);
		assert(length == real_length);
	}

	asm_stream_destroy(stream);
	close(sock_no);

	return 0;
}
#endif
