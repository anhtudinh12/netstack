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
    struct etherFrame *hdr = (struct etherFrame *)frame->frame;
    hdr->etherType = ntohs(hdr->etherType);

    switch (hdr->etherType)
    {
    case ETHERTYPE_ARP:
        //arpHandler();
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
        printf("Unsupported ethertype %x\n", hdr->etherType);
        frameDescriptorFree(frame);
        break;
    }

    return 0;
}

void *netRxLoop(void)
{
    while (1)
    {
        struct frameDescriptor *frame = frameDescriptorAlloc(FRAME_LENGTH);

        if (tapRead((char *)frame->frame, FRAME_LENGTH) < 0)
        {
            perror("ERR: Read from tun_fd");
            frameDescriptorFree(frame);
            return NULL;
        }

        netRxFrameHandler(frame);
    }

    return NULL;
}