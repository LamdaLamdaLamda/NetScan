#ifndef WELLKNOWNPORTS__H
#define WELLKNOWNPORTS__H
    #define ECHO 7
    #define FTP_DATA 20     // FTP File-Transmision
    #define FTP_CONTROl 21 // FTP request
    #define SSH 22
    #define TELNET 23
    #define SMTP 25
    #define WHOIS 43
    #define DNS 53
    #define FINGER 79
    #define HTTP 80
    #define POP3 110
    #define SQL_SERVICE 118
    #define IRC 194
    #define LDAP 389
    #define HTTPS 443
    #define APPLE_QUICKTIME 458
    #define DHCP_CLIENT 546
    #define DHCP_SERVER 547
    #define OPEN_VPN 1194

    // Array with Ports, for Iteration over well-known ports
     int portArray[] ={
                        ECHO,FTP_DATA,FTP_CONTROl,
                        SSH,TELNET,SMTP,
                        WHOIS,DNS,FINGER,
                        HTTP,POP3,SQL_SERVICE,
                        IRC,LDAP,HTTPS,
                        APPLE_QUICKTIME,DHCP_CLIENT,DHCP_SERVER,
                        OPEN_VPN
                        };
#endif // WELLKNOWSPORTS__H
