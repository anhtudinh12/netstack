#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <stdint.h>

#define ETHERTYPE_ARP 0x0806
#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_IPV6 0x86DD

struct recvFrame
{
    uint16_t protocol;
    uint8_t *frame;
};

struct etherFrame
{
    uint8_t dmac[6];
    uint8_t smac[6];
    uint16_t etherType;
    uint8_t payload[];
} __attribute__((packed));

struct recvFrame *recvFrameAlloc(uint32_t sizeOfDataFrame);
void recvFrameFree(struct recvFrame *frame);
#endif /* DATAFRAME_H */