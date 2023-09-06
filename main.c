#include <stdio.h>
#include "./tap/tap.h"
#include "layer2/net.h"
#include "layer3/route.h"
#include "string.h"

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
    init_stack();
    while (1)
    {
        netRxLoop();
    };
}