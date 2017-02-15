#include"netScan.h"

char *getHost()
{
    char *input = NULL;
    printf("\n Hostname oder IPv4-Adresse: ");
    scanf("%s",input);
    return input;
}

int getPort(char *output)
{
    int input = 0;
    printf("\n %s Port Nummer:" , output);
    scanf("%i" , &input);
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
        printf("\nIPv4 is Set!");
        Scan->sockAddress.sin_addr.s_addr = inet_addr(Scan->hostname);
    }


    // Resolving Hostname to Ipv4
    // gethostbyname returning a struct hostent -> != 0
    Scan->host = gethostbyname(Scan->hostname);
    if (Scan->host != 0)
    {
        printf("\nGetting Host by name");
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
    int i;  // Loop-Iteration

    /* Starting at the defined Stat-Port. Ending at the defined Port!
    * might be a sticky way to solve it .....
    * REMARK: DEFINING WELL KNOWS PORTS AS KONSTANTS
    * MIGHT BE: PORTS.H ????? OR JUST METTWURST.H MIGHT BE A PROPER NAMING HAHA
    */
    for (i = Scan->startPortNumber; i < Scan->endPortNumber;i++)
    {
        // LATER TIME TO SLEEP
    }
}
