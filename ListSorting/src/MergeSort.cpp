#include "MergeSort.h"
#include "List.h"

ListNode* MergeTwoList(ListNode* head1, ListNode* head2) {
	ListNode dummy(123);
	ListNode* p = &dummy;
	while (head1 != nullptr && head2 != nullptr) {
		if (head1->val < head2->val) {
			p->next = head1;
			head1 = head1->next;
		}
		else {
			p->next = head2;
			head2 = head2->next;
		}
		p = p->next;
	}
	if (head1) p->next = head1;
	else if (head2) p->next = head2;

	return dummy.next;
}

ListNode* FindMiddleNode(ListNode* head, ListNode* tail) {
	if (tail == nullptr) {
		for (tail = head; tail->next != nullptr; tail = tail->next);
	}
	ListNode* fast, *slow;
	fast = slow = head;
	while (1) {
		if ((fast == tail) || (fast != nullptr && fast->next == tail)) break;
		slow = slow->next;
		fast = fast->next;
		if (fast == tail) break;
		if (fast != nullptr) {
			fast = fast->next;
		}
	}
	return slow;
}

ListNode* MergeSort(ListNode* head, ListNode* tail) {
	if (head == tail) return head;
	ListNode* middleNode = FindMiddleNode(head, tail);
	ListNode* middleNodeNext = middleNode->next;
	middleNode->next = nullptr;
	ListNode* head1 = MergeSort(head, middleNode);
	ListNode* head2 = MergeSort(middleNodeNext, tail);
	return MergeTwoList(head1, head2);
}

ListNode* MergeSort(ListNode* head) {
	return MergeSort(head, nullptr);
}