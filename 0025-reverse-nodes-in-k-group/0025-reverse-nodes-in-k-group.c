
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (!head || k == 1) return head;
    
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *prevGroup = &dummy;
    struct ListNode *curr = head;
    
    int count = 0;
    while (curr) {
        count++;
        curr = curr->next;
    }
    
    while (count >= k) {
        curr = prevGroup->next;
        struct ListNode *next = curr->next;
        for (int i = 1; i < k; i++) {
            curr->next = next->next;
            next->next = prevGroup->next;
            prevGroup->next = next;
            next = curr->next;
        }
        prevGroup = curr;
        count -= k;
    }
    
    return dummy.next;
}