mount -t nfs 192.168.1.1:/software /mnt/software

vi /etc/fstab
192.168.1.1:/software /mnt  nfs defaults 0 0
