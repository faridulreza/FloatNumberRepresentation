#include <stdio.h>

int arr[1000];

#define TEST_BIT(m, bitNo) ((m & (1 << bitNo)) == (1 << bitNo))

void add1(int n, int bits)
{
    int carry = 1;
    for (int i = n - 1; i >= 1; i--)
    {
        arr[i] = arr[i] + carry;

        if (arr[i] > 1)
            carry = 1;
        else
            carry = 0;
        arr[i] = arr[i] % 2;
    }
}

int main(int argc, char *argv[])
{

    FILE *in = fopen(argv[1], "r");

    if (in == NULL)
        return 1;

    double num;
    int n, exp, bits;
    // at most 32 bits for integers
    while (fscanf(in, "%lf %d %d %d", &num, &n, &exp, &bits) != EOF)
    {
        for (int i = 0; i <n; i++)
            arr[i]=0;
        
        // sign bit
        if (num < 0)
            arr[0] = 1;
        else
            arr[0] = 0;

        // fill in the bits
        num = num<0?-num:num;

        double fraction = num - (int)num;
        int integer = (int)num;
        
        int int_bits = 0;
        int tmp = integer;
        while (integer)
        {
            int_bits++;
            integer = integer >> 1;
        }
        integer = tmp;

        int j = exp + 1;
        int m = 0;

        // fill in the array with canonical form
        // and get the exponent

        if (integer) // integer part is non zero
        {
            int tmp = 1;

            for (int i = int_bits - 2; i >= 0 && j < n; i--)
            {
                if (integer & (1ll << i))
                    arr[j++] = 1;
                else
                    arr[j++] = 0;

                tmp++;
            }

            int rounded = 0;
            // rounding if not entire integer values
            // were fit
            if (tmp != int_bits)
            {
                int full_value = (1 << (int_bits - tmp) - 1);
                int rem = integer & full_value;

                if (rem > full_value / 2)
                {

                    add1(n, bits);
                    rounded = 1;
                }
                else if (rem && rem == full_value / 2 && arr[n - 1] == 1)
                {
                    add1(n, bits);
                    rounded = 1;
                }

                
            }

            m = int_bits - 1;

            int_bits--;
            while (int_bits < bits && j < n)
            {
                fraction = fraction * 2;
                integer = (int)fraction;
                fraction = fraction - (int)fraction;

                if (integer != 0)
                    arr[j++] = 1;
                else
                    arr[j++] = 0;
                int_bits++;
            }

            // rounding if not all fraction were fit
            if (fraction > .5 && !rounded)
            {
                add1(n, bits);
            }
            else if (!rounded && fraction == .5 && arr[n - 1] == 1 && m<=bits)
            {  
                add1(n, bits);
            }
        }

        else
        {
            m = 0;
            int got_1 = 0;

            while (j < n)
            {
                fraction = fraction * 2;
                integer = (int)fraction;
                fraction = fraction - (int)fraction;

                if (integer != 0)
                {
                    if (!got_1)
                        m--;
                    else
                        arr[j++] = 1;

                    got_1 = 1;
                }
                else
                {
                    if (got_1)
                        arr[j++] = 0;
                    else
                        m--;
                }
                if (got_1)
                    int_bits++;
            }

            if (fraction > .5)
            {
                add1(n, bits);
            }
            else if (fraction == .5 && arr[n - 1] == 1)
            {
                add1(n, bits);
            }
        }

        int bias = (1 << (exp - 1)) - 1;
        m += bias;

        int carry=0;
        for (int i = exp - 1, j = 1; i >= 0; i--, j++)
            arr[j] += ((m & (1 << i)) == (1 << i));
    

        for (int i = exp; i > 0; i--, j++){
            arr[i-1] += arr[i]>1;
            arr[i] = arr[i]%2;

        }
        

        for (int i = 0; i < n; i++)
            printf("%d", arr[i]);

        puts("");
    }

    fclose(in);
    return 0;
}