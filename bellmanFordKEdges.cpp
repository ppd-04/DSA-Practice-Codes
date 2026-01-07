int bellmanFordKEdges(
    int N,
    int source,
    int target,
    int K,
    const vector<Edge>& edges
) {
    const int INF = 1e9;
    vector<int> dist(N, INF);
    dist[source] = 0;

    for(int i = 1; i <= K; i++) {
        vector<int> newDist(N, INF);

        for(const auto& e : edges) {
            if(dist[e.u] != INF) {
                newDist[e.v] =
                    min(newDist[e.v], dist[e.u] + e.w);
            }
        }
        dist = newDist;
    }

    return dist[target] == INF ? -1 : dist[target];
}
