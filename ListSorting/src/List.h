#pragma once
#include <ostream>

struct ListNode {
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class List {
private:
	ListNode **mppTail, *mpSentinelNode;

public:
	List() {
		mpSentinelNode = new ListNode(0);
		mpSentinelNode->next = nullptr;
		mppTail = &(mpSentinelNode->next);
	}

	ListNode* GetHead() const {
		return mpSentinelNode->next;
	}

	void SetHead(ListNode* head) {
		mpSentinelNode->next = head;
	}

	void Insert(int value) {
		*mppTail = new ListNode(value);
		mppTail = &((*mppTail)->next);
	}

	void Remove(int value) {
		ListNode** ppNode = &(mpSentinelNode->next);
		while (*ppNode != nullptr) {
			if ((*ppNode)->val == value) {
				Remove(ppNode);
			}
			else {
				ppNode = &(*ppNode)->next;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const List& list) {
		ListNode* pNode = list.mpSentinelNode->next;
		while (pNode != nullptr) {
			os << pNode->val << " ";
			pNode = pNode->next;
		}
		os << std::endl;
		return os;
	}

private:
	void Remove(ListNode** ppTarget) {
		ListNode* pNode = *ppTarget;
		*ppTarget = pNode->next;
		delete pNode;
	}
};

