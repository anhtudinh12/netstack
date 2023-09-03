#ifndef NET_H
#define NET_H

#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
struct netdev
{
    uint32_t addr;
    uint8_t addr_len;
    uint8_t hwaddr[6];
    uint32_t mtu;
};

void net_init(void);
struct netdev *net_alloc(char *addr, char *hwaddr, uint32_t mtu);

#endif /* NET_H */