#ifndef TAP_H
#define TAP_H

void tapInit();
int tapRead(char *buf, int len);
int tapWrite(char *buf, int len);
void tapFree();

#endif /* TAP_H*/
