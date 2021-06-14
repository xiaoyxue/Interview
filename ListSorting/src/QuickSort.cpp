#include "QuickSort.h"
#include "List.h"
#include <random>

struct PartitionInfo {
	ListNode* head, * pivot, * tail;
	int left, right;
	PartitionInfo() : head(nullptr), pivot(nullptr), tail(nullptr), left(0), right(0) {}
	PartitionInfo(ListNode* h, ListNode* p, ListNode* t, int l, int r) : head(h), pivot(p), tail(t), left(l), right(0) {}
};

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_real_distribution<float> dist(0.f, 1.f);

PartitionInfo Partition(ListNode* head, ListNode* tail, int length) {
	int stepLength = std::min(length / 2, int(length * dist(mt)));
	ListNode** pp = &head;
	for (int i = 0; i < stepLength; ++i) {
		pp = &((*pp)->next);
	}

	if (*pp != head) {
		ListNode* temp = *pp;
		*pp = (*pp)->next;
		temp->next = head;
		head = temp;
	}

	ListNode* pivot = head;
	ListNode dummy;
	ListNode** py = &(head->next);
	dummy.next = head;
	int left = 0, right = 0;
	while ((*py) != tail) {
		if ((*py)->val < pivot->val) {
			ListNode* temp = *py;
			*py = (*py)->next;
			temp->next = dummy.next;
			dummy.next = temp;
			++left;
		}
		else {
			py = &((*py)->next);
			++right;
		}
	}
	return PartitionInfo(dummy.next, pivot, tail, left, right);
}

std::pair<ListNode*, ListNode*> QuickSort(ListNode* head, ListNode* tail, int length) {
	if (head == tail || head->next == tail) {
		return std::pair<ListNode*, ListNode*>(head, tail);
	}
	PartitionInfo partitionResult = Partition(head, tail, length);
	if (partitionResult.pivot != nullptr) {
		std::pair<ListNode*, ListNode*> list1 = QuickSort(partitionResult.head, partitionResult.pivot, partitionResult.left);
		std::pair<ListNode*, ListNode*> list2 = QuickSort(partitionResult.pivot->next, tail, partitionResult.right);
		list1.second->next = list2.first;
		return std::pair<ListNode*, ListNode*>(list1.first, list2.second);
	}
	return std::pair<ListNode*, ListNode*>(head, tail);
}

ListNode* QuickSort(ListNode* head) {
	ListNode* p = head;
	int length = 0;
	while (p != nullptr) {
		length++;
		p = p->next;
	}
	return QuickSort(head, nullptr, length).first;
}