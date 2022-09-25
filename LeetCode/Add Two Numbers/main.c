#include <stdio.h>

struct ListNode
{
    int val;
    struct ListNode* next;
};

struct ListNode* addTwoNumbers(struct ListNode* l1,struct ListNode* l2)
{
    static struct ListNode storage[101];
    int indx=0;
    struct ListNode* l3,*last;
    l3=storage;

    int n=0;
    int h=0;
    int l=0;

    do
    {
        n=l1->val+l2->val+h;
        h=n/10;
        l=n%10;
        l3->val=l;
        l3->next=&storage[++indx];
        last=l3;
        l3=l3->next;
        l1=l1->next;
        l2=l2->next;

    }while(l1&&l2);

    if(l1||l2||h)
    {
        struct ListNode* left;

        left=l1?l1:l2;

        if(left)
        {
            do
            {
                n=left->val+h;
                h=n/10;
                l=n%10;
                l3->val=l;
                l3->next=&storage[++indx];
                last=l3;
                l3=l3->next;
                left=left->next;

            }while(left);
        }

        if(h)
        {
            l3->val=1;
        }

    }
    last->next=0;
    return storage;
}

struct ListNode l1,l11,l12,l13,l14,l15,l16;
struct ListNode l2,l21,l22,l23,l24,l25,l26;

int main()
{
    l1.next=&l11;
    l11.next=&l12;
    l12.next=0;//&l13;
    l13.next=&l14;
    l14.next=&l15;
    l15.next=&l16;
    l16.next=0;

    l2.next=&l21;
    l21.next=&l22;
    l22.next=0;//&l23;
    l23.next=&l24;
    l24.next=&l25;
    l25.next=&l26;
    l26.next=0;

    l1.val=2; l11.val=4; l12.val=3;
    l2.val=5; l21.val=6; l22.val=4;


    //l1.val=9; l11.val=9; l12.val=9; l13.val=9; l14.val=9; l15.val=9; l16.val=9;
    //l2.val=9; l21.val=9; l22.val=9; l23.val=9;

    //l1.val=1; l11.val=2; l12.val=3; l13.val=4; l14.val=9; l15.val=9; l16.val=9;
    //l2.val=1; l21.val=2; l22.val=3; l23.val=4;

    struct ListNode* rv=addTwoNumbers(&l1,&l2);


    return 0;
}
