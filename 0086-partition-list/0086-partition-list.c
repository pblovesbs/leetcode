struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode less_head = {0, NULL};
    struct ListNode greater_head = {0, NULL};
    struct ListNode *less = &less_head;
    struct ListNode *greater = &greater_head;

    while (head != NULL) {
        if (head->val < x) {
            less->next = head;
            less = less->next;
        } else {
            greater->next = head;
            greater = greater->next;
        }
        head = head->next;
    }

    greater->next = NULL;
    less->next = greater_head.next;

    return less_head.next;
}