set -x

sudo yum -y install nfs-utils-lib
sudo mount -t nfs 192.168.1.3:/scratch /users/al844976/scratch

echo "192.168.1.3:users/al844976/scratch /scratch  nfs defaults 0 0" >> /etc/fstab
