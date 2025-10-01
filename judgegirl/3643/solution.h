struct LinkList{
    int val;
    struct LinkList* next;
};
 
 
struct LinkList* solution(struct LinkList* head){
	struct LinkList* slow = head;
	struct LinkList* fast = head;

	slow = slow->next;
	fast = fast->next->next;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next->next;
	}
	slow = head;
	while (slow != fast) {
		slow = slow->next;
		fast = fast->next;
	}
	return slow;
}
