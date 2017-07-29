#ifndef _APPLE_H_
#define _APPLE_H_

#define APPLE_D_PORT    1500
#define APPLE_M_PORT    1509
#define SERVER_IP       "13.124.180.16"

void send_to_daemon(int *sock, char *s_buffer, char *banana_ip);

#endif
