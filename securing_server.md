Taken from http://spenserj.com/blog/2013/07/15/securing-a-linux-server/

**This is for Ubuntu 12.04 x64**

Add a new user, and add it to an admin group (preconfigured in /etc/sudoers to have access to sudo).

	# sudo addgroup admin
	Adding group `admin' (GID 1000) ...
	Done.

	# sudo adduser vivek
	Adding user `vivek' ...
	Adding new group `vivek' (1001) ...
	Adding new user `vivek' (1000) with group `vivek' ...
	Creating home directory `/home/vivek' ...
	Copying files from `/etc/skel' ...
	Enter new UNIX password: 
	Retype new UNIX password: 
	passwd: password updated successfully
	Changing the user information for vivek
	Enter the new value, or press ENTER for the default
	    Full Name []: Vivek Agarwal
	    Room Number []: 
	    Work Phone []: 
	    Home Phone []: 
	    Other []: 
	Is the information correct? [Y/n] Y

	# sudo usermod -a -G admin vivek


Edit `/etc/ssh/sshd_config` and disable root login.

	PermitRootLogin no
	PermitEmptyPasswords no
	AllowUsers vivek

Restart SSH for the changes to take effect.

	# sudo service ssh restart


Disconnect, reconnect with new account add your public key to authorized_keys on the server.

	# mkdir ~/.ssh

	# echo "ssh-rsa [your public key]" > ~/.ssh/authorized_keys

Now, update the server.

	# sudo apt-get update

	# sudo apt-get upgrade


Go ahead and set up a firewall, and only allow what you need right at this moment. You can always add another exception later, and a few minutes of extra work won’t kill you. IPTables comes preinstalled in Ubuntu, so go ahead and set up some rules for it.

	# sudo mkdir /etc/iptables

Edit `/etc/iptables/rules`.

	*filter
	:INPUT DROP [0:0]
	:FORWARD DROP [0:0]
	:OUTPUT DROP [0:0]
	
	# Accept any related or established connections
	-I INPUT  1 -m state --state RELATED,ESTABLISHED -j ACCEPT
	-I OUTPUT 1 -m state --state RELATED,ESTABLISHED -j ACCEPT
	
	# Allow all traffic on the loopback interface
	-A INPUT  -i lo -j ACCEPT
	-A OUTPUT -o lo -j ACCEPT
	
	# Allow outbound DHCP request - Some hosts (Linode) automatically assign the primary IP
	#-A OUTPUT -p udp --dport 67:68 --sport 67:68 -j ACCEPT
	
	# Outbound DNS lookups
	-A OUTPUT -o eth0 -p udp -m udp --dport 53 -j ACCEPT
	
	# Outbound PING requests
	-A INPUT -p icmp -j ACCEPT
	-A OUTPUT -p icmp -j ACCEPT
	
	# Outbound Network Time Protocol (NTP) request
	-A OUTPUT -p udp --dport 123 --sport 123 -j ACCEPT
	
	# SSH
	-A INPUT  -i eth0 -p tcp -m tcp --dport 22 -m state --state NEW -j ACCEPT
	-A OUTPUT  -o eth0 -p tcp -m tcp --dport 22 -m state --state NEW,ESTABLISHED -j ACCEPT
	
	# Outbound HTTP
	-A OUTPUT -o eth0 -p tcp -m tcp --dport 80 -m state --state NEW -j ACCEPT
	-A OUTPUT -o eth0 -p tcp -m tcp --dport 443 -m state --state NEW -j ACCEPT
	
	# Inbound HTTP
	-A INPUT -i eth0 -p tcp -m tcp --dport 80 -m state --state NEW -j ACCEPT
	
	COMMIT
