#ifndef ARP_H
#define ARP_H

#include <stdio.h>
#include <string.h>
#include "dataFrame.h"
#include "net.h"

#define ETHERNET 0x0001

#define ARP_REQUEST 0x0001
#define ARP_REPLY 0x0002

void arpHandler(struct frameDescriptor *frame);

#endif /* ARP_H */