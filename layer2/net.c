#include "net.h"

struct netdev *loop;
struct netdev *netdev;

static uint32_t ip_parse(char *addr)
{
    uint32_t dst = 0;
    
    if (inet_pton(AF_INET, addr, &dst) != 1) {
        perror("ERR: Parsing inet address failed");
        exit(1);
    }

    return ntohl(dst);
}

void net_init(void)
{
    loop = net_alloc("127.0.0.1", "00:00:00:00:00:00", 1500);
    netdev = net_alloc("10.0.0.4", "00:0c:29:6d:50:25", 1500);
}

struct netdev *net_alloc(char *addr, char *hwaddr, uint32_t mtu)
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
