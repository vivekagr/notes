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
