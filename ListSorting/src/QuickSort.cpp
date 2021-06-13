#include "QuickSort.h"
#include "List.h"
#include <iostream>

struct PartitionInfo {
	ListNode* head, * pivot, * tail;
	PartitionInfo(): head(nullptr), pivot(nullptr), tail(nullptr) {}
	PartitionInfo(ListNode* h, ListNode* p, ListNode* t): head(h), pivot(p), tail(t) {}
};

PartitionInfo Partition(ListNode* head, ListNode* tail) {
	ListNode* pivot = head;
	ListNode dummy;
	ListNode** py = &(head->next);
	dummy.next = head;
	//std::cout << "pivot: " << pivot->val << std::endl;
	//std::cout << "y0: " << y->val << std::endl;
	while ((*py) != tail) {
		//std::cout << "y: " << (*py)->val << std::endl;
		if ((*py)->val < pivot->val) {
			ListNode* temp = *py;
			*py = (*py)->next;
			temp->next = dummy.next;
			dummy.next = temp;
		}
		else {
			py = &((*py)->next);
		}
	}
	//List list;
	//list.SetHead(dummy.next);
	//std::cout << list << std::endl;
	return PartitionInfo(dummy.next, pivot, tail);
}

std::pair<ListNode*, ListNode*> QuickSort(ListNode* head, ListNode* tail) {
	if (head == tail || head->next == tail) {
		return std::pair<ListNode*, ListNode*>(head, tail);
	}
	PartitionInfo partitionResult = Partition(head, tail);
	if (partitionResult.pivot != nullptr) {
		std::pair<ListNode*, ListNode*> list1 = QuickSort(partitionResult.head, partitionResult.pivot);
		std::pair<ListNode*, ListNode*> list2 = QuickSort(partitionResult.pivot->next, tail);
		list1.second->next = list2.first;
		return std::pair<ListNode*, ListNode*>(list1.first, list2.second);
	}
	return std::pair<ListNode*, ListNode*>(head, tail);
}

ListNode* QuickSort(ListNode* head) {
	return QuickSort(head, nullptr).first;
}