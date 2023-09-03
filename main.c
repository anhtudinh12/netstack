#include <stdio.h>
#include "./tap/tap.h"
#include "layer2/net.h"
#include "layer3/route.h"

static void init_stack()
{
    tap_init();
    net_init();
    // route_init();
    // arp_init();
    // tcp_init();
}

int main()
{
    init_stack();
    while (1)
    {
    };
}