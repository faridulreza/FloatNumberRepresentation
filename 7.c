#include <stdio.h>

void printBinary(long long num, int bits)
{

    if (bits == 0)
    {
        return;
    }

    printBinary(num >> 1, bits - 1);

    if (num & 1)
        printf("1");
    else
        printf("0");
}

int main(int argc, char *argv[])
{

    FILE *in = fopen(argv[1], "r");

    if (in == NULL)
        return 1;

    long long num;
    int  bits;
    // at most 32 bits for integers
    while (fscanf(in, "%lld %d", &num, &bits) != EOF)
    {

        int bit_cnt = 0;
        long long tmp = num < 0 ? -num : num; // absolute value

        while (tmp)
        {
            tmp = tmp >> 1;
            bit_cnt++;
        }
     
        if (num < 0)
        {
            if (bit_cnt >= bits)
                num = 1ll << (bits - 1);
            printBinary(num, bits);
        }
        else
        {
            if (bit_cnt >= bits)
                num = (1ll << (bits-1)) - 1;
            printBinary(num, bits);
        }
        puts("");
        
    }

    fclose(in);
    return 0;
}