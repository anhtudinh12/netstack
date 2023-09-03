#include "syshead.h"
#include "../utils/utils.h"

static int tun_fd;
static char *dev;

/* HARD CODE */
char *tapaddr = "10.0.0.5";
char *taproute = "10.0.0.0/24";

static int set_if_route(char *dev, char *cidr)
{
    return run_cmd("ip route add dev %s %s", dev, cidr);
}

static int set_if_address(char *dev, char *cidr)
{
    return run_cmd("ip address add dev %s local %s", dev, cidr);
}

static int set_if_up(char *dev)
{
    return run_cmd("ip link set dev %s up", dev);
}

/*
 * Taken from Kernel Documentation/networking/tuntap.txt
 */
static int tap_alloc(char *dev)
{
    struct ifreq ifr;
    int fd, err;

    if ((fd = open("/dev/net/tap", O_RDWR)) < 0)
    {
        perror("Cannot open TUN/TAP dev\n"
               "Make sure one exists with "
               "'$ mknod /dev/net/tap c 10 200'");
        exit(1);
    }

    memset(&ifr, 0, sizeof(ifr));

    /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
     *        IFF_TAP   - TAP device
     *
     *        IFF_NO_PI - Do not provide packet information
     */
    ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
    if (*dev)
    {
        strncpy(ifr.ifr_name, dev, IFNAMSIZ);
    }

    if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0)
    {
        perror("ERR: Could not ioctl tun");
        close(fd);
        return err;
    }

    strcpy(dev, ifr.ifr_name);
    return fd;
}

int tap_read(char *buf, int len)
{
    return read(tun_fd, buf, len);
}

int tap_write(char *buf, int len)
{
    return write(tun_fd, buf, len);
}

void tap_init()
{
    dev = calloc(10, 1);
    tun_fd = tap_alloc(dev);

    if (set_if_up(dev) != 0)
    {
        print_err("ERROR when setting up if\n");
    }

    if (set_if_route(dev, taproute) != 0)
    {
        print_err("ERROR when setting route for if\n");
    }

    if (set_if_address(dev, tapaddr) != 0)
    {
        print_err("ERROR when setting addr for if\n");
    }
}

void free_tun()
{
    free(dev);
}