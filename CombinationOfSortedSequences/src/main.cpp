/********************** Problem *************************
Give three arrays A[], B[], C[], find counts of combination
for A[i] < B[j] < C[k]
***********************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

class Timer {
public:
	inline void Start() 
	{
		t0 = std::chrono::steady_clock::now();
	}
	inline void Stop() 
	{
		t1 = std::chrono::steady_clock::now();
	}

	inline double Duration() 
	{
		return (std::chrono::duration<double>(t1 - t0)).count();
	}
private:
	std::chrono::time_point<std::chrono::steady_clock> t0;
	std::chrono::time_point<std::chrono::steady_clock> t1;
};

int main()
{
	// Timer
	Timer timer;

	// Random engine
	std::random_device rd;
	std::uniform_int_distribution<> uniform;
	std::mt19937 rng(rd());

	// Initialize data
	int sizeA = 3000, sizeB = 4000, sizeC = 5000;
	std::vector<int> A(sizeA);
	std::vector<int> B(sizeB);
	std::vector<int> C(sizeC);
	for (int i = 0; i < sizeA; ++i) A[i] = uniform(rng);
	for (int i = 0; i < sizeB; ++i) B[i] = uniform(rng);
	for (int i = 0; i < sizeC; ++i) C[i] = uniform(rng);

	// Sort
	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());
	std::sort(C.begin(), C.end());

	// O(n^3)
	timer.Start();
	long long cnt1 = 0;
	for (int i = 0; i < A.size(); ++i)
	{
		for (int j = 0; j < B.size(); ++j)
		{
			for (int k = 0; k < C.size(); ++k)
			{
				if ((B[j] > A[i]) && (C[k] > B[j]) ) cnt1++;
			}
		}
	}
	timer.Stop();
	std::cout << cnt1 << std::endl;
	std::cout << "Duration: " << timer.Duration() << "s" << std::endl;

	// O(n^2logn)
	timer.Start();
	long long cnt2 = 0;
	for (auto itA = A.begin(); itA != A.end(); ++itA)
	{
		auto itB = std::upper_bound(B.begin(), B.end(), *itA);
		for (; itB != B.end(); ++itB)
		{
			auto itC = std::upper_bound(C.begin(), C.end(), *itB);
			if (itC != C.end())
			{
				cnt2 += std::distance(itC, C.end());
			}
		}
	}
	timer.Stop();
	std::cout << cnt2 << std::endl;
	std::cout << "Duration: " << timer.Duration() << "s" << std::endl;

	// O(nlogn)
	timer.Start();
	long long cnt3 = 0;
	for (auto itB = B.begin(); itB != B.end(); ++itB)
	{
		auto itA = std::lower_bound(A.begin(), A.end(), *itB);
		auto itC = std::upper_bound(C.begin(), C.end(), *itB);
		if ((itA != A.end()) && (itC != C.end()))
		{
			cnt3 += std::distance(A.begin(), itA) * std::distance(itC, C.end());
		}
	}	
	timer.Stop();
	std::cout << cnt3 << std::endl;
	std::cout << "Duration: " << timer.Duration() << "s" << std::endl;

	return 0;
}