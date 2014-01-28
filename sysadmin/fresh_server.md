Basic
-----

Derived from http://spenserj.com/blog/2013/07/15/securing-a-linux-server/

    $ sudo addgroup admin
    Adding group `admin' (GID 1000) ...
    Done.


    $ sudo adduser vivek
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
    	Full Name []: 
    	Room Number []: 
    	Work Phone []: 
    	Home Phone []: 
    	Other []: 
    Is the information correct? [Y/n]


    $ sudo usermod -a -G admin vivek


Now close the session and log in back as newly created user `vivek`.

Copy your private key of your local machine.

    $ mkdir ~/.ssh
    $ echo "ssh-rsa [your public key]" > ~/.ssh/authorized_keys

Now check if you can login directly with your key. Then disable root login.

    $ sudo vi /etc/ssh/sshd_config

Set `PermitRootLogin no`.

    $ sudo service ssh restart
    ssh stop/waiting
    ssh start/running, process 11429

Now update.

    $ sudo apt-get update
    $ sudo apt-get upgrade

Extras
------


Now make `/var/www` directory for hosting sites/pages/apps/whateveryourmothermade. From http://askubuntu.com/questions/19898

    $ sudo mkdir /var/www
    $ sudo adduser vivek www-data
    $ sudo chgrp -R www-data /var/www
    $ sudo chown -R www-data:www-data /var/www
    $ sudo chmod -R g+rw /var/www

Logout and log back in to see the changes.
