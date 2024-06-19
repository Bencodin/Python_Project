#include <unistd.h>
#include <stdio.h>

int main()
{
	write(1,"10",2);
	write(1,"\n",1);
   for (int i = 57; i>48; i--){
        write(1,&i,1);
        write(1,"\n",1);	
    }
    return 0;
}
