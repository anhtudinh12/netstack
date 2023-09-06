#include "arp.h"

static struct etherHeader *header;
static struct arpHeader *arp;

static void arpReply(struct frameDescriptor *frame)
{
    /*Segment Fault?
    struct arpHeader *arp = (struct arpHeader *)(header->payload);
    */
    /* Ethernet header */
    memcpy(header->desMAC, header->srcMAC, MAC_LENGTH);
    memcpy(header->srcMAC, frame->net->hwaddr, MAC_LENGTH);
    header->etherType = htons(header->etherType);

    /* ARP header */
    arp->opcode = htons(ARP_OPCODE_REPLY);
    memcpy(arp->targetHwAddr, arp->senderHwAddr, MAC_LENGTH);
    arp->targetProtocolAddr = arp->senderProtocolAddr;
    memcpy(arp->senderHwAddr, header->srcMAC, MAC_LENGTH);
    arp->senderProtocolAddr = htonl(frame->net->addr);

    frame->frameLength = ETH_HEADER_SIZE + ARP_HEADER_SIZE;
    netTxHandler(frame, 0);
}

static void arpUpdateTable(struct frameDescriptor *frame)
{
}
void arpHandler(struct frameDescriptor *frame)
{
    header = (struct etherHeader *)frame->frame;
    arp = (struct arpHeader *)(frame->frame + ETH_HEADER_SIZE);

    if (arp->hwType != htons(ETHERNET))
    {
        printf("Unsupported hardware\n");
        return;
    }
    if (arp->protocol != htons(ARP_IPV4))
    {
        printf("Unsupported protocol\n");
        return;
    }

    switch (ntohs(arp->opcode))
    {
    case ARP_OPCODE_REQUEST:
        arpReply(frame);
        break;
    case ARP_OPCODE_REPLY:
        arpUpdateTable(frame);
        break;
    default:
        break;
    }
}
