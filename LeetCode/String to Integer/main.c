#include <stdio.h>
#include <limits.h>

int f(char* s)
{

    long long rv=0;
    int i=0;
    int i1=0;
    int db=0;
    int si=0;
    while(s[i]&&(s[i]>'9'||s[i]<='0'))
    {
        if((s[i]!=' '&&s[i]!='-'&&s[i]!='+'&&s[i]!='0')||(i&&((s[i]+s[i-1]=='+'+'-')||
                                                              (s[i]+s[i-1]=='+'+'+')||
                                                              (s[i]+s[i-1]=='-'+'-')||
                                                              (s[i]==' '&&s[i-1]=='-')||
                                                              (s[i]==' '&&s[i-1]=='+')||
                                                              (s[i]==' '&&s[i-1]=='0')||
                                                              (s[i]=='-'&&s[i-1]=='0'))))
        {

            return 0;
        }
        if(i&&(s[i]=='0'&&s[i-1]=='-'))si=1;

        i++;
    }
    db=i;
    if(i&&s[i])if(s[i-1]=='-')si=1;
    if(s[0]=='-')si=1;
    while(s[i]&&(s[i]<='9'&&s[i]>='0'))
    {
        i++;
        i1++;
    }

    i1--;
    i=db;
    if(i1>9)return si?-1*INT_MIN:INT_MAX;
    while(s[i]&&(s[i]<='9'&&s[i]>='0'))
    {
        long long b=10;
        int v=s[i]-'0';
        for(int i=1;i<i1;i++)b*=10;
        if(i1)rv+=b*v;
        else rv+=v;

        i1--;
        i++;

        if(rv>__INT_MAX__)
        {
            return si?-1*INT_MIN:INT_MAX;
        }


    }

    rv=si?-1*rv:rv;

    return rv;

}

int main()
{
    int xxx=INT_MAX;
    xxx=INT_MIN;
    int a='4'-'0';
    //a=f("-91283472332 wer");
    //a=f("000-42a123 wer");
    //a=f("  -43");
    a=f(" 9000000000000000000");
    printf("Hello World!\n");
    return 0;
}
