#include "dataFrame.h"

struct recvFrame *recvFrameAlloc(uint32_t sizeOfDataFrame)
{
    struct recvFrame *frame = (struct recvFrame *)malloc(sizeof(struct recvFrame));
    memset(frame, 0, sizeof(struct recvFrame));

    frame->frame = (uint8_t *)malloc(sizeOfDataFrame);
    memset(frame->frame, 0, sizeOfDataFrame);

    return frame;
}

void recvFrameFree(struct recvFrame *frame)
{
    free(frame->frame);
    free(frame);
}