/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {

    int len=0;
    struct ListNode* bob=head;
    while(bob!=NULL)
    {
        bob=bob->next;
        len++;
    }
    
    bob=head;int i=1;
    if (len==n)
    {return head->next;
        
    }
    
    n=len-n;
    while(i<n)
    {bob=bob->next;
      i++;  
    }

bob->next=bob->next->next;
return head;

    
}