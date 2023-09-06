#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <stdint.h>

#define ETHERTYPE_ARP 0x0806
#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_IPV6 0x86DD

// struct etherHeader
// {
//     uint8_t dmac[6];
//     uint8_t smac[6];
//     uint16_t etherType;
// } __attribute__((packed));
// struct etherFrame
// {
//     struct etherHeader *header;
//     uint8_t *payload;
// } __attribute__((packed));
struct etherFrame
{
    uint8_t dmac[6];
    uint8_t smac[6];
    uint16_t etherType;
    uint8_t *payload;
} __attribute__((packed));

struct frameDescriptor
{
    uint16_t protocol;
    struct etherFrame *frame;
};

struct frameDescriptor *frameDescriptorAlloc(uint32_t sizeOfDataFrame);
void frameDescriptorFree(struct frameDescriptor *frame);
#endif /* DATAFRAME_H */