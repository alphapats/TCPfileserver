#!/bin/sh

 /etc/init.d/mysql stop
 sudo mysqld_safe --skip-grant-tables &
 mysql -u root mysql
 update user set password=PASSWORD("root") where User='root';
 FLUSH PRIVILEGES;