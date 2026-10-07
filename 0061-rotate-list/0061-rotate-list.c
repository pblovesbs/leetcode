struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (!head || !head->next || k == 0) return head;
    
    int len = 1;
    struct ListNode* tail = head;
    while (tail->next) {
        tail = tail->next;
        len++;
    }
    
    tail->next = head;
    k %= len;
    
    int steps = len - k;
    struct ListNode* new_tail = tail;
    while (steps--) {
        new_tail = new_tail->next;
    }
    
    struct ListNode* new_head = new_tail->next;
    new_tail->next = NULL;
    
    return new_head;
}