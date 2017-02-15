#include"netScan.h"

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
    #ifdef DEBUG
        fprintf(stderr,"\n Host: %s" , Scan->hostname);
        fprintf(stderr,"\n Host[0]: %c" , Scan->hostname[0]);
    #endif // DEBUG

    if (isdigit(Scan->hostname[0]))
    {
        printf("\nIPv4 is Set!");
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

void scanLoop(TScan *Scan)
{
    int i = 0;  // Loop-Iteration
    /* Starting at the defined Stat-Port. Ending at the defined Port!
    * might be a sticky way to solve it .....
    * REMARK: DEFINING WELL KNOWS PORTS AS KONSTANTS
    * MIGHT BE: PORTS.H ????? OR JUST METTWURST.H MIGHT BE A PROPER NAMING HAHA
    */
    fprintf(stdout,"\nStarting Scan...");
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
            fprintf(stderr,"\nAbort.Socket cant be created...\n");
            raise(SIGTERM);
        }

        // seting up the connection.
        Scan->errorNum = connect(Scan->s,(struct sockaddr*)&Scan->sockAddress,sizeof(Scan->sockAddress));

        if (Scan->errorNum < 0)
            fprintf(stderr,"\nPort %i closed. Host: %s",i,Scan->hostname);
        else
            fprintf(stdout,"\n Port %i open. Host: %s" , i , Scan->hostname);

        // Closing Filedeskriptor on socket.
        close(Scan->s);
        clearBuffer();
    }
    fprintf(stdout,"\n\nScan on %s finished!",Scan->hostname);
}

void clearBuffer()
{
    char c;
    while (c != '\n')
        scanf("%c",&c);
}

void runScan(TScan *Scan)
{
    char * tempHost;
    tempHost = getHost();
    copyHost(Scan,tempHost);
    Scan->startPortNumber = getPort("\nStarting at Port:");
    Scan->endPortNumber = getPort("\nEnding at Port:");
    initSocket(Scan);
    isIP(Scan);
    scanLoop(Scan);
}

void copyHost(TScan *Scan,char* host)
{
    // reserving memory for host!
    Scan->hostname = malloc(sizeof(TScan) * strlen(host) + 1);
    strncpy(Scan->hostname,host,strlen(host) + 1);
}
