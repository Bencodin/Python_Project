#include<stdio.h>
#include<unistd.h>
char* o_strcpy(char *a,  char *b, size_t n)
{
	int i=0;
       do{
           b[i]=a[i];
	   i++;
       }
   	while(a[i] != '\0');
}       
char* o_strncpy(char* dest, const char* src, unsigned int n)

{
    
    if ((dest == NULL) &&(src == NULL))
        return NULL;
    char* start = dest;
   
    while (*src && n--)
    {
        *dest = *src;
        dest++;
        src++;
    }
    while (*dest)

    {
        *dest = '\0';
	dest++;
    }

    return start;
}
int main()
{
    char src[] = "ViveOteria";
    
    char dest[5] = {0};
    o_strncpy(dest, src,12);

    write(1,&dest,sizeof(dest));

    write(1,"\n",1);

    char a[] = "abc";
    printf("input string: %s", a);

    char b[sizeof(a)];

    o_strcpy(a,b,10);

    printf("\noutput string: %s",b);
    
    return 0;

}
