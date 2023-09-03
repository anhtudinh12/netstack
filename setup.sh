if [ $# -eq 0 ]; then
    echo "Usage: $0 <interface>"
    exit 1
fi
# build lvl-ip
cd build
make
# Initialize tap device
mknod /dev/net/tap c 10 200
chmod 0666 /dev/net/tap
# Set up tap device
sysctl -w net.ipv4.ip_forward=1
iptables -I INPUT --source 10.0.0.0/24 -j ACCEPT
iptables -t nat -I POSTROUTING --out-interface $1 -j MASQUERADE
iptables -I FORWARD --in-interface $1 --out-interface tap0 -j ACCEPT
iptables -I FORWARD --in-interface tap0 --out-interface $1 -j ACCEPT