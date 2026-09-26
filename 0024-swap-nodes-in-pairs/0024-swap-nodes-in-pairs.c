/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapPairs(struct ListNode* head) {
    
    struct ListNode *temp = head;
    struct ListNode *prev = NULL;
    int i = 1;

    while (temp != NULL && temp->next != NULL) {

        if (i % 2 == 1) {

            struct ListNode *temp1 = temp->next;

            // Connect temp to the node after temp1
            temp->next = temp1->next;

            // Put temp1 before temp
            temp1->next = temp;

            if (i == 1) {
                head = temp1;
            }
            else {
                prev->next = temp1;
            }

            // temp is now the second node of the pair
            prev = temp;
            temp = temp->next;
        }

        i++;
    }

    return head;
}