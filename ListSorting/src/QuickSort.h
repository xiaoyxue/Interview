#pragma once

struct ListNode;
struct ListInfo {
	ListNode* head, * tail, * pivot, *pivotPrev;
};
ListInfo Partition(ListNode* head, ListNode* tail);
ListNode* QuickSort(ListNode* head, ListNode* tail = nullptr);