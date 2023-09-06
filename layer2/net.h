#ifndef NET_H
#define NET_H

#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>

#include "dataFrame.h"
#include "../tap/tap.h"
#include "arp.h"

#define FRAME_LENGTH 1600

struct netdev
{
    uint32_t addr;
    uint8_t addr_len;
    uint8_t hwaddr[6];
    uint32_t mtu;
};

void netInit(void);
void *netRxLoop(void);
int netTxHandler(struct frameDescriptor *frameDes, uint8_t *desMAC);

#endif /* NET_H */