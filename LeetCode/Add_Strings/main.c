#include <stdio.h>
#include <string.h>

char* f(char* num1,char* num2)
{
    static char rv[10000+2];

    int ln1=strlen(num1);
    int ln2=strlen(num2);
    int r=0;
    int m=0;
    int j=0;
    char* min;
    char* max;
    int min_sz,max_sz;
    if(ln1>ln2){max=num1;min=num2;max_sz=ln1;min_sz=ln2;}
    else {max=num2;min=num1;max_sz=ln2;min_sz=ln1;}

    j=max_sz+1;
    rv[j]=0;
    j--;
    int i_max=max_sz-1;
    int i_min=min_sz-1;

    for(int i=0;i<max_sz;i++)
    {
        int n1;
        int n2;
        if(i_min<0)n2=0;
        else n2=min[i_min--]-'0';

        n1=max[i_max--]-'0';
        int n3;
        r=(n1+n2+m)%10;
        m=(n1+n2+m)/10;
        n3=r;
        rv[j--]=n3+'0';
    }
    if(m)rv[j--]=m+'0';
    return j<0?rv:rv+1;
}
int main()
{
    char n1[]="123";
    char n2[]="456";
    char* r=f(n1,n2);

    printf("%s\n",r);
    return 0;
}
