#include <stdio.h>

int main(int argc, char *argv[])
{

    FILE *in = fopen(argv[1], "r");

    if (in == NULL)
        return 1;

    double d;
    int bits;

    while (fscanf(in, "%lf %d", &d, &bits) != EOF)
    {
        double fraction = d - (int)d;
        int integer = d - fraction;

        int int_bits = 0;
        int tmp = integer;
        while (integer)
        {
            int_bits++;
            integer = integer >> 1;
        }
        integer = tmp;

        if (integer) // integer part is non zero
        {

            int tmp_bits = bits + 1;
            for (int i = int_bits - 1; i >= 0 && tmp_bits; i--, tmp_bits--)
            {
                if (integer & (1ll << i))
                {
                    printf("1");
                }
                else
                    printf("0");
                if (i == int_bits - 1)
                    printf(".");
            }

            int m = int_bits - 1;

            int_bits--;
            while (int_bits < bits)
            {
                fraction = fraction * 2;

                double t_fraction = fraction - (int)fraction;

                integer = fraction - t_fraction;
                fraction = t_fraction;

                if (integer != 0)
                    printf("1");
                else
                    printf("0");
                int_bits++;
            }

            printf(" %d\n", m);
        }

        else
        {
            int m = 0;
            // int_bits == 0
            int got_1 = 0;
            int_bits--;
            while (int_bits < bits)
            {
                fraction = fraction * 2;

                double t_fraction = fraction - (int)fraction;

                integer = fraction - t_fraction;
                fraction = t_fraction;

                if (integer != 0)
                {
                    if (!got_1){
                        m--;
                        printf("1.");
                    }
                    else 
                        printf("1");
                    
                    got_1 = 1;
                }
                else
                {
                    if (got_1)
                        printf("0");
                    else m--;
                }
                if(got_1)
                    int_bits++;
            }

            printf(" %d\n",m);
        }
    }

    fclose(in);
    return 0;
}