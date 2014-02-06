Install Packages
----------------

Install nginx

    sudo apt-get install nginx

Add a repository to pull latest PHP build

    sudo apt-get install python-software-properties
    sudo add-apt-repository ppa:ondrej/php5
    sudo apt-get update
    sudo apt-get upgrade
    sudo apt-get install php5-fpm

Install MySQL

    sudo apt-get install mysql-server mysql-client php5-mysql

Install `unzip`

    sudo apt-get install unzip


Make Directories & Set Permissions
----------------------------------

    sudo mkdir /var/www
    sudo adduser vivek www-data
    sudo chgrp -R www-data /var/www
    sudo chown -R www-data:www-data /var/www
    sudo chmod -R g+rw /var/www


Download Wordpress
------------------

    wget http://wordpress.org/latest.zip
    sudo mv wordpress /var/www/mynewsite.com


Nginx Configuration
-------------------

    sudo mkdir /etc/nginx/global
    cd /etc/nginx/global

Make a new file called `restrictions.conf` and add the following content:

    # Global restrictions configuration file.
    # Designed to be included in any server {} block.</p>
    location = /favicon.ico {
    	log_not_found off;
    	access_log off;
    }
    
    location = /robots.txt {
    	allow all;
    	log_not_found off;
    	access_log off;
    }
    
    # Deny all attempts to access hidden files such as .htaccess, .htpasswd, .DS_Store (Mac).
    # Keep logging the requests to parse later (or to pass to firewall utilities such as fail2ban)
    location ~ /\. {
    	deny all;
    }
    
    # Deny access to any files with a .php extension in the uploads directory
    # Works in sub-directory installs and also in multisite network
    # Keep logging the requests to parse later (or to pass to firewall utilities such as fail2ban)
    location ~* /(?:uploads|files)/.*\.php$ {
    	deny all;
    }
