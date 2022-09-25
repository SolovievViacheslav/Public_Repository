#include <iostream>
#include <bits/stdc++.h>

#define ul unsigned long long
#define ll  long long
using namespace std;

int curr_perm=0;

char arr_inp[9];
char arr_out[40320][9];
bool all_unic=true;

void exchange(char* str,int start, int len)
{

    char tmp;
    tmp=str[start];

    for(int j=0,i=start;i<len-1;i++,j++)
    {

        if(tmp!=str[len-1-j])

        {
//            for(int m=start-1;m>=0;m--)
            {
  //              if(str[len-1-j]!=str[m])
                {
                    char str_tmp[9];
                    strcpy(str_tmp,str);
                    str_tmp[start]=str[len-1-j];
                    str_tmp[len-1-j]=tmp;
                    bool f=true;
                    if(!all_unic)
                    {
                        for(int i=0;i<curr_perm;i++)
                        {
                            if(strcmp(arr_out[i],str_tmp)==0)
                            {
                                f=false;
                                break;
                            }
                        }
                    }

                    if(f)
                    {
                        strcpy(arr_out[curr_perm],str_tmp);
                        curr_perm++;
                    }
                    /*
                    strcpy(arr_out[curr_perm],str);
                    arr_out[curr_perm][start]=str[len-1-j];
                    arr_out[curr_perm][len-1-j]=tmp;
                    curr_perm++;
                    */
                }
            }

        }
    }
}
int cmp_str(const void*s,const void*s1)
{
   //  return strcmp(*(char**)s,*(char**)s1);
     return strcmp((const char*)s,(const char*)s1);
}
int main()
{

    int reps[9]={1,1,1,1,1,1,1,1,1};
    int n=0;

    scanf("%s",arr_inp);
    n=strlen(arr_inp);

    int perm_num=1;
    int n_s=n;

    for(int i=0;i<n;i++)
    {
        bool f=true;
        for(int m=i;m>=0;m--)
        {
            if((arr_inp[i]==arr_inp[m])&&(reps[m]>1))
            {
                f=false;
                all_unic=false;
                break;

            }
        }

        if(f)
        {
            for(int j=i+1;j<n;j++)
            {

                if((arr_inp[i]==arr_inp[j]))
                    {
                       reps[i]++;
                    }
            }
        }
    }
    ll all=1;
    for(int i=0;i<n;i++)
    {
        ll t=1;

        while(reps[i])
        {
            t*=reps[i];
            reps[i]--;
        }
        all*=t;
    }

    while(n_s)
    {
        perm_num*=n_s;
        n_s--;
    }
    perm_num=perm_num/all;
    arr_inp[n+1]=0;

    curr_perm=0;
    strcpy(arr_out[curr_perm],arr_inp);
    curr_perm++;
    exchange(arr_inp,0,n);

    int start_sym=0;
    while(curr_perm<perm_num)
    {
        int curr_perm_save=curr_perm;
        start_sym++;
        for(int i=0;i<curr_perm_save;i++)
        {
            char tmp[9];
            strcpy(tmp,arr_out[i]);
            exchange(tmp,start_sym,n);
        }
    }

    qsort(arr_out,perm_num,sizeof(char)*9,cmp_str);
/*
    //test fo repeats.
    for(int i=0;i<perm_num;i++)
    {
        for(int j=i+1;j<perm_num;j++)
        if(strcmp(arr_out[i],arr_out[j])==0)
        {
            break;
        }
    }
    */
    cout<<perm_num<<"\n";
    for(int i=0;i<perm_num;i++)
    {
        //cout<<i<<" "<<arr_out[i]<<endl;
        cout<<arr_out[i]<<endl;
    }
    cout.flush();
    return 0;
}
