#ifndef TAP_H
#define TAP_H

void tap_init();
int tap_read(char *buf, int len);
int tap_write(char *buf, int len);
void free_tap();

#endif /* TAP_H*/
