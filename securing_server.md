Taken from http://spenserj.com/blog/2013/07/15/securing-a-linux-server/

I'll be editing the above article to suit my needs.

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


Install a Firewall
------------------

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

Apply the ruleset with a timeout through `iptables-apply`, and if you lose the connection, fix your rules and try again before continuing.

	# sudo iptables-apply /etc/iptables/rules
	Applying new ruleset... done.
	Can you establish NEW connections to the machine? (y/N) y
	... then my job is done. See you next time.

Create the file `/etc/network/if-pre-up.d/iptables`, with the following content. This will automatically load your IPTables rules when you start the server.

	#!/bin/sh
	iptables-restore < /etc/iptables/rules

Now give it execute permissions, and execute the file to ensure it loads properly.

	# sudo chmod +x /etc/network/if-pre-up.d/iptables
	# sudo /etc/network/if-pre-up.d/iptables


Fail2Ban The Wannabe l33t Hack0rz
---------------------------------

	# sudo apt-get install fail2ban

Fail2ban installs a default configuration (`/etc/fail2ban/jail.conf`), but we’ll want to make our changes in `/etc/fail2ban/jail.local`, so copy it there.

	sudo cp /etc/fail2ban/jail.{conf,local}

**Configuration**

You’ll also want to set up a destemail, which I normally enter as my own email address followed by ,fail2ban@blocklist.de. BlockList.de is a system to track and automatically report hacking attempts to the proper abuse contact for their IP.

Edit `/etc/fail2ban/jail.local`.

	# Destination email address used solely for the interpolations in
	# jail.{conf,local} configuration files.
	destemail = root@localhost,fail2ban@blocklist.de

**Actions**

Actions allow you to react to malicious activity, however the default is to issue an IPTables ban, while we want it to ban and send an email. Thankfully there is a preconfigured `action_mwl`, which does just that.

	# Choose default action.  To change, just override value of 'action' with the
	# interpolation to the chosen action shortcut (e.g.  action_mw, action_mwl, etc) in jail.local
	# globally (section [DEFAULT]) or per specific section
	action = %(action_mwl)s

**Jails**

In order for Fail2ban to work, it needs to know what to watch. These are configured in the Jails section of the config, and there are quite a few examples pre-loaded and disabled. Since you’ve only enabled SSH access on the server so far, we’ll only enable the SSH and SSH-DDoS jails, however you’ll want to add a new jail for each publicly-accessible service that you install on this server.

	[ssh]
	
	enabled  = true
	port     = ssh
	filter   = sshd
	logpath  = /var/log/auth.log
	maxretry = 6
	
	[ssh-ddos]
	
	enabled  = true
	port     = ssh
	filter   = sshd-ddos
	logpath  = /var/log/auth.log
	maxretry = 6


**Apply the changes**

	# sudo service fail2ban restart
	 * Restarting authentication failure monitor fail2ban
	   ...done.

At any time, you can use `sudo iptables -L` to list your rules, and subsequently list any currently-banned IPs. 
