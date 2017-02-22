#include"netScan.h"

int main()
{
    TScan *Scan = (TScan*)malloc(sizeof(TScan) * SCANSET);
    runScan(Scan);
    free(Scan);
    return 0;
}
