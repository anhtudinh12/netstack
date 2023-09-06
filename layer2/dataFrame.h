#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAC_LENGTH 6

#define ETH_HEADER_SIZE 14
#define ETHERTYPE_ARP 0x0806
#define ETHERTYPE_IPV4 0x0800
#define ETHERTYPE_IPV6 0x86DD

#define ARP_HEADER_SIZE 28
#define ARP_HW_ETHERNET 0x0001
#define ARP_IPV4 0x0800

#define ARP_OPCODE_REQUEST 0x0001
#define ARP_OPCODE_REPLY 0x0002

struct etherHeader
{
    /* Ethernet header */
    uint8_t desMAC[6];
    uint8_t srcMAC[6];
    uint16_t etherType;
    /* Ethernet payload*/
    uint8_t *payload;
} __attribute__((packed));

struct arpHeader
{
    uint16_t hwType;
    uint16_t protocol;
    uint8_t hwAddrLength;
    uint8_t protocolAddrLength;
    uint16_t opcode;
    uint8_t senderHwAddr[6];
    uint32_t senderProtocolAddr;
    uint8_t targetHwAddr[6];
    uint32_t targetProtocolAddr;
} __attribute__((packed));

struct frameDescriptor
{
    uint16_t protocol;
    uint16_t frameLength;
    struct netdev *net;
    uint8_t *frame;
};

struct frameDescriptor *frameDescriptorAlloc(uint32_t sizeOfDataFrame);
void frameDescriptorFree(struct frameDescriptor *frame);
#endif /* DATAFRAME_H */