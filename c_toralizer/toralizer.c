#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>

#include "toralizer.h"

/*
 * ./toralize 1.2.3.4 80
 */

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <host> <port>\n", argv[0]);
		return EXIT_FAILURE;
	}

	char* host = argv[1];
	int port = atoi(argv[2]);
	int reuse = 1, success = 0;
	Proxy_Request *req = create_request(host, port);
	Proxy_Response *res = NULL;
	char buf[RES_SIZE];

	printf("IP: %s\n", host);
	printf("Port: %d\n", port);

	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_fd < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		fprintf(stderr, "Failed to create socket\n");
		return EXIT_FAILURE;
	} else {
		printf("Socket created\n");
	}

	// Setting REUSE_PORT ensures that we don't run into 'Address already in use' errors
	if (setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &reuse, sizeof(reuse)) < 0) {
		fprintf(stderr, "SO_REUSEPORT failed: %s \n", strerror(errno));
		exit(EXIT_FAILURE);
	} else {
		printf("SO_REUSEPORT set\n");
	}

	struct sockaddr_in sock = {
		.sin_family = AF_INET,
		.sin_port = htons(PROXY_PORT),
		.sin_addr.s_addr = inet_addr(PROXY_IP)
	};

	if (connect(sock_fd, (struct sockaddr *) &sock, sizeof(sock)) < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		fprintf(stderr, "Failed to connect to proxy\n");
		return EXIT_FAILURE;
	} else {
		fprintf(stderr, "Connected to proxy\n");
	}

	memset(buf, 0, RES_SIZE);

	write(sock_fd, req, REQ_SIZE);
	if (read(sock_fd, buf, RES_SIZE) < 1) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		fprintf(stderr, "Failed to read response\n");
		free(req);
		if (close(sock_fd) < 0) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			fprintf(stderr, "Failed to close socket\n");
		}
		return EXIT_FAILURE;
	} else {
		fprintf(stderr, "Response read\n");
	}

	res = (Proxy_Response *) buf;
	success = res->cmd == 90 ? 1 : 0;
	if (!success) {
		fprintf(stderr, "Unable to Traverse Proxy\n");
		fprintf(stderr, "Error Code: %d\n", res->cmd);

		free(req);
		if (close(sock_fd) < 0) {
			fprintf(stderr, "Error: %s\n", strerror(errno));
			fprintf(stderr, "Failed to close socket\n");
		}
		return EXIT_FAILURE;
	} else {
		fprintf(stderr, "Successfully Connected through Proxy to"
				" %s:%d\n", host, port);
		fprintf(stderr, "Response: \n");
		fprintf(stderr, "Version: %d\n", res->ver);
		fprintf(stderr, "Command: %d\n", res->cmd);
		fprintf(stderr, "Port: %d\n", ntohs(res->dst_port));
		fprintf(stderr, "IP: %s\n", inet_ntoa(*(struct in_addr *) &res->dst_ip));
	}

	if(close(sock_fd) < 0) {
		fprintf(stderr, "Error: %s\n", strerror(errno));
		fprintf(stderr, "Failed to close socket\n");
		free(req);
		return EXIT_FAILURE;
	} else {
		printf("Socket closed\n");
	}

	free(req);
	return EXIT_SUCCESS;
}

Proxy_Request *create_request(const char* dst_ip, const int dst_port) {
	Proxy_Request *req = calloc(1, REQ_SIZE);

	req->ver = 4;
	req->cmd = 1;
	req->dst_ip = inet_addr(dst_ip);
	req->dst_port = htons(dst_port);
	strncpy((char* ) req->username, USERNAME, 8);

	return req;
}
