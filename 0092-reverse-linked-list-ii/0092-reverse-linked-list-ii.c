struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    if (!head || left == right) return head;
    
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *pre = &dummy;
    
    for (int i = 1; i < left; i++) {
        pre = pre->next;
    }
    
    struct ListNode *curr = pre->next;
    for (int i = 0; i < right - left; i++) {
        struct ListNode *next_node = curr->next;
        curr->next = next_node->next;
        next_node->next = pre->next;
        pre->next = next_node;
    }
    
    return dummy.next;
}