#include <unistd.h>

void   o_print_number(int nb)
{
    if (nb < 0)
    {
        write(1, "-", 1);
        nb *= -1;
    }
    if (nb > 9)
    {
        o_print_number(nb / 10);
        o_print_number(nb % 10);
    }
    else
    {
        nb += '0';
        write(1, &nb, 1);
    }
}

int main (void)
{
   o_print_number(50);
}
