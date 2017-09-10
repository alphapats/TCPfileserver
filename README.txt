#########################################################################################################################################################################################################

									FILES AND FOLDERS

######################################################################################################################################################################################################

-------------------------------------SERVER2 FOLDER :Authentication server-----------------------------------------------------------------------
1.server2.cpp : Authentication server code.This file creates a Authentication server. File takes one commandline input arguments ie own listning port.
Server2 (Backend authentication server) receives username and password from Server1 for either creating new account or to authenticate the user.


2.installmysql.sh : script to install MySQL server and required libraries for header files.

3.importdatabase.sh : script to import database and user table from cs744.sql file.

4.cs744.sql : contains MySQL database and table for import.

5.Makefile 


-------------------------------------SERVER1 FOLDER :File server-----------------------------------------------------------------------
1.server1.cpp : File server code.This file creates a file server. File takes one commandline input arguments ie own listning port.
Client sends username and password to server for either creating new account or to authenticate himself for fetching file. Once authenticated, client will send filename to server1 and will downlaod file from server1 if file exists.
The command prompt message to enter Authentication server IP address (Server2) and listening port.

2."uploads" sub-folder :  to store files available for sharing.

3. Makefile 


------------------------------CLIENT FOLDER-------------------------------------------------------------------------------------
1.client.cpp : This file creates a client. File takes two commandline input arguments file server (server1) IP and server port.
Server IP and port will be used to connect the server and request files. The client sends username and password to server for either creating new account or to authenticate himself for fetching file. Once authenticated, client will send filename to server1 and will downlaod file from server1 if file exists.

2."downloads" sub-folder :  to store files received from server.

3. Makefile 
-----------------------------------------------------------------------------------------------------------------------------------

#########################################################################################################################################################################################################

									HOW TO RUN

######################################################################################################################################################################################################
HOW TO INSTALL MYSQL AT SERVER2:
Step by step procedure for installation of MySQL is as follows:
1.  Command to install MySQL:
sudo apt-get install mysql-server
2.  To log in to MySQL as the root user:
mysql -u root -p
//USER ”root”
//PASSWORD ”root”
3.  To create a New MySQL Database ”ems
data”
create database ems
data;
use ems
data;
4.  To create table ”user” with attributes ”user
name” and ”passwd”
Field — Type — Null — Key — Default
user
name — varchar(20) — NO — PRI — NULL —
passwd — varchar(20) — NO — — NULL —
CREATE TABLE user (user
name VARCHAR(20) NOT NULL PRI-
MARY, passwd varchar(20) NOT NULL);
5.  To insert values in table
INSERT INTO user VALUES (’username’,’password’);
6.  To export databases:
mysqldump -u<Username>-p<DatabaseName>><wantedsqlfile.sql>
7.  To import database:
mysql -u<username>-p<databasename><<filename.sql>
In order to make MySQL commands from C++ program, there is requirement to install required libraries for including header files.  The command to  install same:
sudo apt-get install libmysqlclient-dev
Above  steps  have  been  consolidated  in  two  shell  scripts  provided  in  folder:
installmysql.sh
importdatabase.sh

TO RUN SERVER2: 
1. Run make.
2. Run ./server2 <own listening port no>


---------------------------------------------------------------------------------------------------------------------------------------
HOW TO RUN server1:

1. Open server1 folder.
2. Run make.
3. Run ./server1  <own listening port no> 
4. The command prompt message to enter Authentication server IP address (Server2) and listening port.

---------------------------------------------------------------------------------------------------------------------------------------
HOW TO RUN CLIENT:

1. Open client folder.
2. Run make.
3. Run ./client <server1 IP address> <Server1 listening port no> 
4. Follow commands on screen for adding new user or fetching files.
	
 ------------------------------------------------------------------------------------------------------------------------------------

