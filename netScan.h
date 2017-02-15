#ifndef NETSCAN__H
#define NETSCAN__H
    #include<stdio.h>
    #include<stdlib.h>
    #include<errno.h> // to indicate what went wrong -> is set by systemcall
    #include<netdb.h>
    #include<string.h>
    #include<sys/socket.h> // Systemcall for socket
    #include <arpa/inet.h>
    #include <ctype.h>   // for inet_addr() Function
    #include <signal.h> // Signal handling
    #include <unistd.h> // for close()
    #define DEBUG
    #define CLEAR                printf("\033[2J")
    #define SCANSET 1   // Set of Scans
    #define HOSTLEN 19

    // Data structure to manage Scanning-Processes much more easily
    typedef struct
    {
        char *hostIP;
        char *hostname;
        int startPortNumber;
        int endPortNumber;
        int s; // Socket
        int errorNum;
        struct hostent *host;
        struct sockaddr_in sockAddress;
    }TScan;

    // reading Hostname or even IP -> RV: Host
    char *getHost();
    // reading a Port, respectively a port intervall
    int getPort(const char*);
    // Seting the sockadd_in struct to init-State
    void initSocket(TScan*);
    // Checking if "hostname" of TScan is IP or actual hostname
    void isIP(TScan*);
    // Scanning-Loop Function
    void scanLoop(TScan*);
    // Clearing the input Buffer. fflush() wont work on Linux based systems
    void clearBuffer();
    // Starting the scanning Process
    void runScan(TScan*);
    // to copy the real size of the host!
    void copyHost(TScan*,char*);
#endif
