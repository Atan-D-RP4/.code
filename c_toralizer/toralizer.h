#ifndef TORALIZER_H_
#define TORALIZER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PROXY_IP	"127.0.0.1"
#define PROXY_PORT 	9050
#define BUF_SIZE 	1024

#define USERNAME 	"toraliz"

#define REQ_SIZE 	sizeof(Proxy_Request)
#define RES_SIZE 	sizeof(Proxy_Response)

typedef struct {
	uint8_t 	ver; 			// SOCKS version - VD
	uint8_t 	cmd;			// Command - CD
	uint16_t 	dst_port;		// Destination port
	uint32_t 	dst_ip;			// Destination IP
	uint8_t 	username[8];	// Username
} Proxy_Request;

typedef struct {
	uint8_t 	ver; 			// SOCKS version - VD
	uint8_t 	cmd;			// Command - CD
	uint16_t 	dst_port;		// Destination port
	uint32_t 	dst_ip;			// Destination IP
} Proxy_Response;

Proxy_Request *create_request(const char* dst_ip, const int dst_port);

#endif /* TORALIZER_H_ */
