#include "dataFrame.h"

struct frameDescriptor *frameDescriptorAlloc(uint32_t sizeOfDataFrame)
{
    struct frameDescriptor *frame = (struct frameDescriptor *)malloc(sizeof(struct frameDescriptor));
    memset(frame, 0, sizeof(struct frameDescriptor));

    frame->frame = (uint8_t *)malloc(sizeOfDataFrame);
    memset(frame->frame, 0, sizeOfDataFrame);

    return frame;
}

void frameDescriptorFree(struct frameDescriptor *frame)
{
    free(frame->frame);
    free(frame);
}