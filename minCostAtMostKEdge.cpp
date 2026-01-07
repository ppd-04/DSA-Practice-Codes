#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w;
};

const int INF = 1e9;

int minCostAtMostKEdges(
    int N, int M, int S, int T, int K,
    const vector<Edge>& edges,
    const vector<int>& vertexCost
) {
    // dist[i][v] = min cost to reach v using at most i edges
    vector<vector<int>> dist(K + 1, vector<int>(N, INF));
    dist[0][S] = vertexCost[S]; // cost to enter source

    for(int i = 1; i <= K; i++) {
        dist[i] = dist[i-1]; // start with previous layer
        for(const auto& e : edges) {
            if(dist[i-1][e.u] != INF) {
                dist[i][e.v] = min(dist[i][e.v],
                                   dist[i-1][e.u] + e.w + vertexCost[e.v]);
            }
        }
    }

    int ans = INF;
    for(int i = 1; i <= K; i++) ans = min(ans, dist[i][T]);

    return ans == INF ? -1 : ans;
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<int> vertexCost(N);
    for(int i = 0; i < N; i++) cin >> vertexCost[i];

    vector<Edge> edges(M);
    for(int i = 0; i < M; i++)
        cin >> edges[i].u >> edges[i].v >> edges[i].w;

    int S, T, K;
    cin >> S >> T >> K;

    int ans = minCostAtMostKEdges(N, M, S, T, K, edges, vertexCost);
    cout << ans << endl;

    return 0;
}
