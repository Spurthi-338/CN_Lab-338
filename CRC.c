#include <stdio.h>
#include <string.h>

void computeCRC(const char data[], const char poly[], char remainder[])
{
    char temp[300];
    int dataLen = strlen(data);
    int polyLen = strlen(poly);
    int totalLen = dataLen + polyLen - 1;

    // Copy message
    strcpy(temp, data);

    // Append zeros directly
    for (int i = 0; i < polyLen - 1; i++)
        temp[dataLen + i] = '0';
    temp[totalLen] = '\0';

    printf("\nPadded data (Message + zeros): %s\n", temp);

    // Division
    for (int i = 0; i <= totalLen - polyLen; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < polyLen; j++)
                temp[i + j] = (temp[i + j] == poly[j]) ? '0' : '1';
        }
    }

    // Extract remainder
    strncpy(remainder, temp + totalLen - (polyLen - 1), polyLen - 1);
    remainder[polyLen - 1] = '\0';
}

int checkReceived(const char received[], const char poly[])
{
    char temp[300];
    strcpy(temp, received);

    int msgLen = strlen(temp);
    int polyLen = strlen(poly);

    for (int i = 0; i <= msgLen - polyLen; i++)
    {
        if (temp[i] == '1')
        {
            for (int j = 0; j < polyLen; j++)
                temp[i + j] = (temp[i + j] == poly[j]) ? '0' : '1';
        }
    }

    // Check remainder
    for (int i = msgLen - (polyLen - 1); i < msgLen; i++)
        if (temp[i] == '1')
            return 0;

    return 1;
}

int main()
{
    char message[150], poly[50], crc[50], transmitted[300], received[300];

    printf("Enter message bits: ");
    scanf("%149s", message);

    printf("Enter polynomial g(x): ");
    scanf("%49s", poly);

    computeCRC(message, poly, crc);

    printf("CRC bits (remainder): %s\n", crc);

    // Build transmitted frame
    strcpy(transmitted, message);
    strcat(transmitted, crc);

    printf("Transmitted message: %s\n", transmitted);

    printf("\nEnter received bits: ");
    scanf("%299s", received);

    if (checkReceived(received, poly))
        printf("\nNo Error detected. Message OK.\n");
    else
        printf("\nERROR detected in received message!\n");

    return 0;
}
