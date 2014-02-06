Install Wordpress on a fresh Ubuntu server
===========================================

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

Make `wordpress.conf` and add the following:

    # WordPress single blog rules.
    # Designed to be included in any server {} block.
    
    # This order might seem weird - this is attempted to match last if rules below fail.
    # http://wiki.nginx.org/HttpCoreModule
    location / {
    	try_files $uri $uri/ /index.php?$args;
    	index index.php;
    }
    
    # Add trailing slash to */wp-admin requests.
    rewrite /wp-admin$ $scheme://$host$uri/ permanent;
    
    # Directives to send expires headers and turn off 404 error logging.
    location ~* ^.+\.(ogg|ogv|svg|svgz|eot|otf|woff|mp4|ttf|rss|atom|jpg|jpeg|gif|png|ico|zip|tgz|gz|rar|bz2|doc|xls|exe|ppt|tar|mid|midi|wav|bmp|rtf)$ {
           access_log off; log_not_found off; expires max;
    }
    
    # Uncomment one of the lines below for the appropriate caching plugin (if used).
    #include global/wordpress-wp-super-cache.conf;
    #include global/wordpress-w3-total-cache.conf;
    
    # Pass all .php files onto a php-fpm/php-fcgi server.
    location ~ \.php$ {
    	# Zero-day exploit defense.
    	# http://forum.nginx.org/read.php?2,88845,page=3
    	# Won't work properly (404 error) if the file is not stored on this server, which is entirely possible with php-fpm/php-fcgi.
    	# Comment the 'try_files' line out if you set up php-fpm/php-fcgi on another machine.  And then cross your fingers that you won't get hacked.
    	try_files $uri =404;
    
    	fastcgi_split_path_info ^(.+\.php)(/.+)$;
    	#NOTE: You should have "cgi.fix_pathinfo = 0;" in php.ini
    
    	include fastcgi_params;
    	fastcgi_index index.php;
    	fastcgi_param SCRIPT_FILENAME $document_root$fastcgi_script_name;
    #	fastcgi_intercept_errors on;
    	fastcgi_pass unix:/var/run/php5-fpm.sock;
    }

Add site's configuration file at `/etc/nginx/sites-available/mynewsite.com`:

    server {
    	listen 80;
    	server_name mynewsite.com;
    	root /var/www/mynewsite.com/;
    
    	access_log /home/vivek/logs/mynewsite_access.log;
    	error_log /home/vivek/logs/mynewsite_error.log;
    
    	include global/restrictions.conf;
    	include global/wordpress.conf;
    }

Create symbolic link of this file in `sites-enabled` directory.

    sudo ln -s /etc/nginx/sites-available/mynewsite.com /etc/nginx/sites-enabled/mynewsite.com

Test nginx configuration and restart service!

    sudo nginx -t
    sudo service nginx restart

Now create a new mysql user (see [commands.md](commands.md)) and access mynewsite.com from a browser and complete the setup.
