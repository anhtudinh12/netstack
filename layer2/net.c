#include "net.h"

struct netdev *loop;
struct netdev *netdev;

static uint32_t ip_parse(char *addr)
{
    uint32_t dst = 0;

    if (inet_pton(AF_INET, addr, &dst) != 1)
    {
        perror("ERR: Parsing inet address failed");
        exit(1);
    }

    return ntohl(dst);
}

static struct netdev *netAlloc(char *addr, char *hwaddr, uint32_t mtu)
{
    struct netdev *dev = malloc(sizeof(struct netdev));

    dev->addr = ip_parse(addr);

    sscanf(hwaddr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &dev->hwaddr[0],
           &dev->hwaddr[1],
           &dev->hwaddr[2],
           &dev->hwaddr[3],
           &dev->hwaddr[4],
           &dev->hwaddr[5]);

    dev->addr_len = 6;
    dev->mtu = mtu;

    return dev;
}

void netInit(void)
{
    loop = netAlloc("127.0.0.1", "00:00:00:00:00:00", 1500);
    netdev = netAlloc("10.0.0.4", "00:0c:29:6d:50:25", 1500);
}

static int netRxFrameHandler(struct frameDescriptor *frame)
{
    struct etherHeader *header = (struct etherHeader *)frame->frame;
    header->etherType = ntohs(header->etherType);

    switch (header->etherType)
    {
    case ETHERTYPE_ARP:
        arpHandler(frame);
        printf("ETHERTYPE: ARP\n");
        break;
    case ETHERTYPE_IPV4:
        // ipv4Handler();
        printf("ETHERTYPE: IPV4\n");
        break;
    case ETHERTYPE_IPV6:
        // ipv6Handler();
        printf("Not supported: IPv6\n");
        break;
    default:
        printf("Unsupported ethertype %x\n", header->etherType);
        frameDescriptorFree(frame);
        break;
    }

    return 0;
}

// int netdev_transmit(struct sk_buff *skb, uint8_t *dst_hw, uint16_t ethertype)
// {
//     struct netdev *dev;
//     struct eth_hdr *hdr;

//     dev = skb->dev;

//     skb_push(skb, ETH_HDR_LEN);

//     hdr = (struct eth_hdr *)skb->data;

//     memcpy(hdr->dmac, dst_hw, dev->addr_len);
//     memcpy(hdr->smac, dev->hwaddr, dev->addr_len);

//     hdr->ethertype = htons(ethertype);
//     eth_dbg("out", hdr);

//     return tun_write((char *)skb->data, skb->len);;
// }

int netTxHandler(struct frameDescriptor *frameDes, uint8_t *desMAC)
{

    return tapWrite((char *)frameDes->frame, frameDes->frameLength);
}
void *netRxLoop(void)
{
    int run = 1;
    while (run)
    {
        struct frameDescriptor *frame = frameDescriptorAlloc(FRAME_LENGTH);
        frame->net = netdev;

        if (tapRead((char *)frame->frame, FRAME_LENGTH) < 0)
        {
            perror("ERR: Read from tun_fd");
            frameDescriptorFree(frame);
            return NULL;
        }

        netRxFrameHandler(frame);
        frameDescriptorFree(frame);
    }

    return NULL;
}