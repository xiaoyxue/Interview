#include "List.h"
#include "BucketMergeSort.h"
#include "MergeSort.h"
#include <cstring>

ListNode* buckets[64];

ListNode* BucketMergeSort(ListNode* head) {
	memset(buckets, 0, sizeof(buckets));
	ListNode* p = head;
	int fill = 0, counter;
	while (head) {
		p = head->next;
		head->next = nullptr;
		for (counter = 0; counter != fill && buckets[counter] != nullptr; ++counter) {
			head = MergeTwoList(buckets[counter], head);
			buckets[counter] = nullptr;
		}
		buckets[counter] = head;
		if (counter == fill) ++fill;
		head = p;
	}
	head = nullptr;
	for (counter = 0; counter <= fill; ++counter) {
		head = MergeTwoList(head, buckets[counter]);
	}
	return head;
}