/*
** EPITECH PROJECT, 2024
** MyFTP
** File description:
** error_code
*/

#ifndef ERROR_CODE_H_
    #define ERROR_CODE_H_

    #define NEW_CONNECTION "220 Service ready for new user.\r\n"
    #define USER_LOGGED "230 User logged in, proceed.\r\n"
    #define CLOSE_CONNECTION "221 Service closing control connection.\r\n"

    #define USER_AUTH "331 User name okay, need password.\r\n"
    #define NO_USER "332 Need account for login.\r\n"

    #define USER_NOT_LOGGED "530 Not logged in.\r\n"
    #define USER_ALREADY_LOGGED "530 Already logged in.\r\n"
    #define WRONG_ID "500 Login incorrect.\r\n"
    #define UNKNOWN_COMMAND "500 Unknown command.\r\n"


#endif /* !ERROR_CODE_H_ */
