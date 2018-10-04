sudo yum install nfs-utils nfs-utils-lib
sudo yum install portmap

/etc/init.d/portmap start
/etc/init.d/nfs start
chkconfig --level 35 portmap on
chkconfig --level 35 nfs on

mkdir /software
vi /etc/exports
/software 10.10.10.3(rw,sync,no_root_squash)
/software 10.10.10.4(rw,sync,no_root_squash)
/software 10.10.10.5(rw,sync,no_root_squash)
/software 10.10.10.6(rw,sync,no_root_squash)
/software 10.10.10.7(rw,sync,no_root_squash)
/software 10.10.10.8(rw,sync,no_root_squash)
/software 10.10.10.9(rw,sync,no_root_squash)
/software 10.10.10.10(rw,sync,no_root_squash)
/software 10.10.10.11(rw,sync,no_root_squash)
/software 10.10.10.12(rw,sync,no_root_squash)
/software 10.10.10.13(rw,sync,no_root_squash)
/software 10.10.10.14(rw,sync,no_root_squash)
/software 10.10.10.15(rw,sync,no_root_squash)


#info found:
#https://www.tecmint.com/how-to-setup-nfs-server-in-linux/
