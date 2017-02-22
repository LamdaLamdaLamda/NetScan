#include"netScan.h"

void clearBuffer()
{
    char c;
    while (c != '\n')
        scanf("%c",&c);
}

char *getHost()
{
    char *input = (char*)malloc(sizeof(char) * HOSTLEN);
    printf("\n Hostname oder IPv4-Adresse: ");
    scanf("%s",input);
    clearBuffer();
    return input;
}

int getPort(const char *output)
{
    int input = 0;
    printf("\n %s Port Nummer:" , output);
    scanf("%i" , &input);
    clearBuffer();
    return input;
}

void initSocket(TScan *Scan)
{
    printf("\nInitializing...\n");
    // Setting sockAddr_in stuct to zero
    bzero(&Scan->sockAddress,sizeof(struct sockaddr_in));
    Scan->sockAddress.sin_family = AF_INET;  // IPv4
}

void isIP(TScan *Scan)
{

    // in Case first Char is digit -> setting IP!
    if (isdigit(Scan->hostname[0]))
    {
        printf("\n\nIPv4 is Set!");
        Scan->sockAddress.sin_addr.s_addr = inet_addr(Scan->hostname);
    }
    else if ((Scan->host =gethostbyname(Scan->hostname) != 0))// gethostbyname returning a struct hostent -> != 0
    {
        fprintf(stdout,"\nGetting Host by name"); // Resolving Hostname to Ipv4
        // Copying the IP-List (h_addr_list) to the sin_addr struct
        strncpy((char*)&Scan->sockAddress.sin_addr,(const char*)Scan->host->h_addr_list, sizeof(Scan->sockAddress.sin_addr));
    }
    else
    {
        fprintf(stderr,"\nResolving not possible...");
        raise(SIGTERM);
    }
}

void runScan(TScan *Scan)
{
    char *tempHost;
    tempHost = getHost();
    copyHost(Scan,tempHost);
    Scan->startPortNumber = getPort("\nStarting at Port:");
    Scan->endPortNumber = getPort("\nEnding at Port:");
    Scan->connectTimeout = getConnectTimeout();
    initSocket(Scan);
    isIP(Scan);
    scanAllPorts(Scan);
}

void copyHost(TScan *Scan,char* host)
{
    // reserving memory for host!
    Scan->hostname = malloc(sizeof(TScan) * strlen(host) + 1);
    strncpy(Scan->hostname,host,strlen(host) + 1);
}

void printPort(int portNumber,const char *print)
{
    switch (portNumber)
    {
        case ECHO:       fprintf(stdout,"\n ECHO %i Port %s" ,portNumber,print);
                         break;
        case FTP_DATA:   fprintf(stdout,"\n FTP %i DATA Port %s",portNumber,print);
                         break;
        case FTP_CONTROl:fprintf(stdout,"\n FTP %i CONTROL Port %s",portNumber,print);
                         break;
        case SSH:        fprintf(stdout,"\n SSH %i Port %s",portNumber,print);
                         break;
        case TELNET:     fprintf(stdout,"\n TELNET %i Port %s",portNumber,print);
                         break;
        case SMTP:       fprintf(stdout,"\n SMTP %i Port %s",portNumber,print);
                         break;
        case WHOIS:      fprintf(stdout,"\n WHOIS %i Port %s",portNumber,print);
                         break;
        case DNS:        fprintf(stdout,"\n DNS %i Port %s",portNumber,print);
                         break;
        case FINGER:     fprintf(stdout,"\n FINGER %i Port %s",portNumber,print);
                         break;
        case HTTP:       fprintf(stdout,"\n HTTP %i Port %s",portNumber,print);
                         break;
        case POP3:       fprintf(stdout,"\n POP3 %i Port %s",portNumber,print);
                         break;
        case SQL_SERVICE:fprintf(stdout,"\n SQL SERVICE %i Port %s",portNumber,print);
                         break;
        case IRC:        fprintf(stdout,"\n IRC %i Port %s",portNumber,print);
                         break;
        case LDAP:        fprintf(stdout,"\n LDAP %i Port %s",portNumber,print);
                         break;
        case HTTPS:      fprintf(stdout,"\n HTTPS %i Port %s",portNumber,print);
                         break;
        case APPLE_QUICKTIME: fprintf(stdout,"\n APPLE QUICKTIME %i Port %s",portNumber,print);
                              break;
        case DHCP_CLIENT:fprintf(stdout,"\n DHCP CLIENT %i Port %s",portNumber,print);
                         break;
        case DHCP_SERVER:fprintf(stdout,"\n DHCP SERVER %i Port %s",portNumber,print);
                         break;
        case OPEN_VPN:   fprintf(stdout,"\n OPEN VPN %i Port %s",portNumber,print);
                         break;
        default: fprintf(stdout,"\n Port %i %s",portNumber,print);
    }
}

void scanAllPorts(TScan *Scan)
{
    int i = 0;  // Loop-Iteration
    /* Starting at the defined Stat-Port. Ending at the defined Port!
    * might be a sticky way to solve it .....
    * REMARK: DEFINING WELL KNOWS PORTS AS KONSTANTS
    * MIGHT BE: PORTS.H ????? OR JUST METTWURST.H MIGHT BE A PROPER NAMING HAHA
    */
    printf("\nStarting Scan...");
    for (i = Scan->startPortNumber; i < Scan->endPortNumber;i++)
    {
        // Seting the Port according to the loop index:
        /* Casting from Host Byte Order to Network Byte
        *  Order. Excpecting unsigned int
        */
        Scan->sockAddress.sin_port = htons(i);

        // Create Socket based on TCP -> This is why this Scan is NOT stealthy!
        // Connection must be established!
        Scan->s = socket(AF_INET,SOCK_STREAM,0);

        // in case that the socket cant be created
        if (socket < 0)
        {
            printf("\nAbort.Socket cant be created...\n");
            raise(SIGTERM);
        }

        setsockopt(Scan->s,SOL_TCP,TCP_TIMEOUT,(char*)&Scan->connectTimeout,sizeof(Scan->connectTimeout));

        // seting up the connection.
        Scan->errorNum = connect(Scan->s,(struct sockaddr*)&Scan->sockAddress,sizeof(Scan->sockAddress));

        if (Scan->errorNum < 0)
           printPort(i,"closed.");
        else
           printPort(i,"open.");


        // Closing Filedeskriptor on socket.
        close(Scan->s);
    }
    fprintf(stdout,"\n\nScan on %s finished!",Scan->hostname);
}

int getConnectTimeout()
{
    int timeout;
    fprintf(stdout,"\nTCP-Connect Timeout [ms]:");
    scanf("%i",&timeout);
    return timeout;
}
