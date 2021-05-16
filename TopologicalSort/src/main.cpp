#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <set>
#include <map>

class Graph 
{
public:
	std::map<int, std::vector<int>> mAdjacency;
	std::set<int> mVertices;
	std::map<int, int> mDegree;
public:
	void AddEdge(int from, int to) {
		mVertices.insert(from);
		mVertices.insert(to);
		if (mAdjacency.find(from) != mAdjacency.end()) {
			mAdjacency[from].push_back(to);
		}
		else {
			mAdjacency[from] = std::vector<int>();
			mAdjacency[from].push_back(to);
		}
		IncreaseDegree(from, to);

	}
private:
	void IncreaseDegree(int from, int to) {
		if (mDegree.find(from) == mDegree.end()) {
			mDegree[from] = 0;
		}
		if (mDegree.find(to) != mDegree.end()) {
			mDegree[to]++;
		}
		else if (from != to) {
			mDegree[to] = 1;
		}
		else {
			mDegree[to] = 0;
		}
	}
};

bool Topology(Graph &graph) {
	std::queue<int> q;
	for (std::map<int, int>::iterator it = graph.mDegree.begin(); it != graph.mDegree.end(); ++it) {
		if (it->second == 0) q.push(it->first);
	}
	int cnt = 0;
	while (!q.empty()) {
		++cnt;
		int u = q.front(); q.pop();
		const auto& adj = graph.mAdjacency[u];
		for (int i = 0; i < adj.size(); ++i) {
			int v = adj[i];
			graph.mDegree[v]--;
			if (!graph.mDegree[v]) q.push(v);
		}
	}
	return cnt == graph.mVertices.size() ? true : false;
}

void Run() {
	int u, v, N, M, T;
	std::cin >> T;
	while (T--) {
		Graph graph;
		std::cin >> M >> N;
		for (int i = 0; i < M; i++) {
			std::cin >> u >> v;
			graph.AddEdge(u, v);
		}
		if (Topology(graph))
			std::cout << "Correct" << std::endl;
		else
			std::cout << "Wrong" << std::endl;

	}
}

int main()
{
	freopen("C:\\Code\\Interview\\TopologicalSort\\src\\input.txt","r",stdin);
	Run();
	return 0;
}