#include "List.h"
#include "MergeSort.h"
#include "BucketMergeSort.h"
#include "QuickSort.h"
#include <iostream>


int main() {
	List list1;
	list1.Insert(3);
	list1.Insert(2);
	list1.Insert(1);
	list1.Insert(4);
	list1.Insert(7);
	list1.Insert(6);
	list1.Insert(5);
	list1.Insert(0);
	list1.Insert(12);
	list1.Insert(5);
	std::cout << list1 << std::endl;
	list1.SetHead(MergeSort(list1.GetHead()));
	std::cout << list1 << std::endl;


	List list2;
	list2.Insert(3);
	list2.Insert(2);
	list2.Insert(1);
	list2.Insert(4);
	list2.Insert(7);
	list2.Insert(6);
	list2.Insert(5);
	list2.Insert(0);
	list2.Insert(12);
	list2.Insert(5);
	std::cout << list2 << std::endl;
	list2.SetHead(BucketMergeSort(list2.GetHead()));
	std::cout << list2 << std::endl;


	List list3;
	list3.Insert(3);
	list3.Insert(2);
	list3.Insert(1);
	list3.Insert(4);
	list3.Insert(7);
	list3.Insert(6);
	list3.Insert(5);
	list3.Insert(0);
	list3.Insert(12);
	list3.Insert(5);
	std::cout << list3 << std::endl;
	list3.SetHead(QuickSort(list3.GetHead()));
	std::cout << list3 << std::endl;

	return 0;
}