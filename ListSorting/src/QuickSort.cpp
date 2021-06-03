#include "List.h"
#include "QuickSort.h"
#include <iostream>

void Swap(ListNode** a, ListNode** b) {
	ListNode* tempA = *a;
	ListNode* tempA_Next = (*a)->next;
	ListNode* tempB = *b;
	ListNode* tempB_Next = (*b)->next;
	*a = *b;
	(*a)->next = tempA_Next;
	*b = tempA;
	(*b)->next = tempB_Next;
}

//struct ListInfo {
//	ListNode* head, * tail, * pivot;
//};

ListInfo Partition(ListNode* head, ListNode* tail) {

	ListNode** x = &head;
	ListNode** y = &(head->next);
	ListNode** pivot = &(head);
	ListNode dummy;
	ListNode* prev = &dummy;
	prev->next = head;
	while (*y!= tail) {
		if ((*y)->val < (*pivot)->val) {
			x = &((*x)->next);
			prev = prev->next;
			Swap(x, y);
		}
		y = &((*y)->next);
		//List list;
		//list.SetHead(head);
		//std::cout << list << std::endl;
	}
	Swap(x, pivot);
	List list;
	list.SetHead(*pivot);
	std::cout << (*x)->val << std::endl;
	std::cout << list << std::endl;
	ListInfo listInfo;
	listInfo.head = *pivot;
	listInfo.tail = *y;
	listInfo.pivot = *x;
	listInfo.pivotPrev = prev;
	return listInfo;
}


ListNode* QuickSort(ListNode* head, ListNode* tail) {
	if (head == tail) return head;
	ListInfo listInfo = Partition(head, tail);
	ListNode* head1, * head2 ;
	head1 = QuickSort(listInfo.head, listInfo.pivotPrev);
	head2 = QuickSort(listInfo.pivot->next, listInfo.tail);

	if(listInfo.pivot != nullptr)
		listInfo.pivot->next = head2;
	return head1;
}