#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#define Max_Buffer 16

int main(int argc, char const* argv[])
{
    char* buf = malloc(Max_Buffer * sizeof(char));
    int Line = 1, int i;
    
    FILE* File;
    if (argc < 2) {
        printf("Podano nieodpowiednią ilość argumentów");
        return 1;
    }
    else {
        File = fopen(argv[1], "r");
    }
    while (fread(buf, sizeof(char), Max_Buffer, File) > 0)
    {
        printf("%08X  ", Line * Max_Buffer);

        for (i = 0; i < sizeof(char) * Max_Buffer; i++)
        {
            printf("%02X ", Max_Buffer[i]);
        }
        printf(" ");
        for (i = 0; i < sizeof(char) * Max_Buffer; i++)
        {
            if ((buf[i] > 31 && buf[i] < 127) || buf[i] > 127)
                printf("%c", buf[i]);
            else
                printf(" ");
        }
        for (i = 0; i < Max_Buffer; i++)
        {
            buf[i] = ' ';
        }
        printf("\n");
        Line++;
    }
    fclose(File);
    free(buf);
    return 0;
}

