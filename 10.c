#include <stdio.h>
#include <math.h>

int arr[1000];

void write8Bits(char b, int index)
{

    int num = b - '0';
    if (b >= 'a' && b <= 'f')
        num = 10 + b - 'a';

    for (int i = index, j = 3; i < index + 4; i++, j--)
    {
        arr[i] = (num & (1 << j)) == (1 << j);
    }
}

long long getPower(int exp)
{
    long long power = 0;
    long long pw = 1;
    for (int i = exp; i > 0; i--)
    {
        if (arr[i])
            power += pw;

        pw *= 2;
    }

    return power;
}

double pow(long long pw)
{

    double res = 1;
    if (pw < 0)
        for (int i = 0; i < abs(pw); i++)
        {
            res /= 2;
        }
    else
        for (int i = 0; i < abs(pw); i++)
        {
            res *= 2;
        }

    return res;
}

int frac_len(double d)
{

    d = d - (int)d;

    int cnt = 0;
    while (d != 0 && cnt < 100)
    {
        d = d * 10;
        d = d - (int)d;
        cnt++;
    }

    return cnt;
}
int main(int argc, char *argv[])
{

    FILE *in = fopen(argv[1], "r");

    if (in == NULL)
        return 1;

    int n, exp, bits, precision;
    char buff[1000];

    // at most 32 bits for integers
    while (fscanf(in, "%d %d %d %s %d", &n, &exp, &bits, buff, &precision) != EOF)
    {

        for (int i = 0; i < n; i++)
            arr[i] = 0;

        int k = 0;
        for (int i = 2; buff[i] != '\0'; i++, k += 4)
            write8Bits(buff[i], k);

        // if k>n shif (k-n) bits
        if (k > n)
        {
            int shift= k-n;
            for (int i = 0; i < k-shift; i++)
            {
                arr[i]=arr[i+shift];
            }
        }

        int total = 0;
        for (int i = 1; i < exp + bits + 1; i++)
            total += arr[i];

        long long exponent = getPower(exp);

        if (total == 0)
        {
            if (arr[0])
                printf("-");

            double result = 0;
            printf("%.*lf\n", precision, result);
            continue;
        }

        ;

        long long bias = (1 << (exp - 1)) - 1;
        int expo_zero = 0;

        if (!exponent)
        {
            exponent = -bias + 1;
            expo_zero = 1;
        }
        else
            exponent -= bias;

        double result = 0;
        // printf("|%lld\n",leftmost_pw);

        if (!expo_zero) //zero exponent means the mantissa is in denormalized form
            result += 1;

        for (int i = exp + 1, k = 1; i < exp + bits + 1; i++, k++)
            result += arr[i] * pow(-k);

        result *= pow(exponent);

        if (arr[0])
            printf("-");

        printf("%.*lf\n", precision, result);
    }

    fclose(in);
    return 0;
}