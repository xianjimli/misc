#include "client.h"

#ifndef DSH_CLIENT_SOCK_H
#define DSH_CLIENT_SOCK_H

Client* client_sock_create(int sock);
Client* client_sock_connect(const char* host, int port);
Client* client_sock_accept(int port);
Client* client_sock_accept_on_sock(int sock);

#endif/*DSH_CLIENT_SOCK_H*/

