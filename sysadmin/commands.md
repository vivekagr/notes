Compress/De-compress A Directory
--------------------------------

Compress

    tar -zcvf archive-name.tar.gz directory-name

De-compress

    tar -zxvf archive-name.tar.gz -C /home/user/targer/dir


MySQL Import & Export DB
------------------------

    mysqldump -u [username] -p [database name] > [database name].sql

    mysql -u [username] -p newdatabase < [database name].sql


MySQL new user and db
---------------------

Launch mysql client with root user.

    $ mysql -u root -p

Now create new db, user and give permissions to the user for the db.

    mysql> CREATE DATABASE wordpress;
    Query OK, 1 row affected (0.00 sec)
    
    mysql> CREATE USER wordpressuser@localhost;
    Query OK, 0 rows affected (0.00 sec)
    
    mysql> SET PASSWORD FOR wordpressuser@localhost= PASSWORD("password");
    Query OK, 0 rows affected (0.00 sec)
    
    mysql> GRANT ALL PRIVILEGES ON wordpress.* TO wordpressuser@localhost IDENTIFIED BY 'password';
    Query OK, 0 rows affected (0.00 sec)
    
    mysql> FLUSH PRIVILEGES;
    Query OK, 0 rows affected (0.00 sec)
    
    mysql> exit
