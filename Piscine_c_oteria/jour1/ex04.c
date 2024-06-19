#include <unistd.h>
#include <stdio.h>

int main ()
{
    for (int i = 90; i>64; i--)
    {
	write(1,&i,1);
	write(1,"\n",1);
    }

return 0;
}
