/*
Climb Stairs
1 step or k steps to find how many solutions, s.t. constant space
F[n] = F[n - 1] + F[n - k]
*/
#include <iostream>
#include <cstring>

constexpr int MAXN = 100000;
constexpr int MAXK = 100;
long long F[MAXN];
long long G[MAXN];

int main()
{
	int n = 10, k = 3;
	memset(F, 0, sizeof(F));
	memset(G, 0, sizeof(G));
	for (int i = 0; i < k; ++i) {
		F[i] = 1;
	}
	F[k % k] = 2;
	for (int i = 1; i < k; ++i) {
		G[i] = 1;
	}
	G[k] = 2;
	for (int i = k + 1; i <= n; ++i) {
		F[i % k] = F[(i - 1) % k] + F[(i - k) % k];
		G[i] = G[i - 1] + G[i - k];
	}
	std::cout << F[n % k] << ", " << G[n] << std::endl;
	return 0;
}