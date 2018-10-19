set -x
sudo yum -y install nfs-utils nfs-utils-lib

sudo mkdir -p /users/al844976/software
sudo chmod 777 /users/al844976/software

sudo mkdir -p /users/al844976/scratch
sudo chmod 777 /users/al844976/scratch

systemctl enable nfs-server
service nfs start

sudo mount -t nfs 192.168.1.1:/software /users/al844976/software
sudo mount -t nfs 192.168.1.3:/scratch /users/al844976/scratch

echo '192.168.1.1:/software /users/al844976/software  nfs defaults 0 0' >> /etc/fstab
echo '192.168.1.3:/scratch /users/al844976/scratch  nfs defaults 0 0' >> /etc/fstab

echo "export PATH='$PATH:/users/al844976/software/openmpi/3.1.2/bin'" >> /users/al844976/.bashrc
echo "export LD_LIBRARY_PATH='$LD_LIBRARY_PATH:/users/al844976/software/openmpi/3.1.2/lib/'" >> /users/al844976/.bashrc
