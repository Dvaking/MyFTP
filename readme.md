# MYFTP
## Table of Contents
1. [General Info](#general-info)
2. [Technologies](#technologies)
3. [Installation](#installation)
4. [Overview](#Overview)
## General Info
The goal of this project is to create a **FTP server.**

    USAGE: ./myftp port path
        port is the port number on which the server socket listens
        path is the path to the home directory for the Anonymous user
## Technologies


[![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)](https://fr.wikipedia.org/wiki/C_(langage))
[![Libmy_C](https://img.shields.io/badge/Libmy_C-Dvaking?style=for-the-badge&color=red&link=https%3A%2F%2Fgithub.com%2FDvaking%2FLibrary%2Ftree%2Fmain%2FLib_C)](https://github.com/Dvaking/Library/tree/main/Lib_C)
## Installation
A little intro about the installation.
```
$ git clone git@github.com:Dvaking/MyFTP.git
$ cd MyFTP
$ make
$ ./myftp port path
```
## Overview
***
```
Server:

$ make
$ ./myftp 8000 ./
Waiting for connection...
```
```
Client:

$ telnet localhost 8000
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
220 Service ready for new user.
USER Anonymous
331 User name okay, need password.
PASS
230 User logged in, proceed.
HELP
214 Help message.
  USER [arg]:
    send ur username to connect
  PASS [arg]:
    send ur pass to connect
  CWD [arg]:
    moves through server files
  CDUP
    moves to the parent file
  PWD [arg]:
    is used to give the position in files
  DELE [arg]:
    deletes a file on the server
  QUIT:
    allows you to disconnect

```
