#include <unistd.h>
#include <string.h>


void o_print_string(char *str)
{
  write(1,str,sizeof(str));
  
}

int main (void)
{
   char bonjour[]="pommade";
   o_print_string(bonjour);

}
