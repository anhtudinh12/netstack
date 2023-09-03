#ifndef DATAFRAME_H
#define DATAFRAME_H

#include <stdint.h>

struct etherFrame
{
    uint8_t dmac[6];
    uint8_t smac[6];
    uint16_t etherType;
    uint8_t payload[];
} __attribute__((packed));

#endif DATAFRAME_H /* DATAFRAME_H */