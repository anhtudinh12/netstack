#include <stdio.h>
#include "./tap/tap.h"
#include "layer2/net.h"
#include "layer3/route.h"
#include "string.h"

struct sk_buff
{
    struct list_head list;
    struct rtentry *rt;
    struct netdev *dev;
    int refcnt;
    uint16_t protocol;
    uint32_t len;
    uint32_t dlen;
    uint32_t seq;
    uint32_t end_seq;
    uint8_t *end;
    uint8_t *head;
    uint8_t *data;
    uint8_t *payload;
};

static void init_stack()
{
    tapInit();
    netInit();
    // route_init();
    // arp_init();
    // tcp_init();
}

int main()
{
    struct sk_buff *skb = malloc(sizeof(struct sk_buff));
    memset(skb, 0, sizeof(struct sk_buff));

    skb->data = malloc(1600);
    memset(skb->data, 0, 1600);

    skb->refcnt = 0;
    skb->head = skb->data;
    skb->end = skb->data + 1600;

    list_init(&skb->list);

    init_stack();
    while (1)
    {
        netRxLoop();
    };
}