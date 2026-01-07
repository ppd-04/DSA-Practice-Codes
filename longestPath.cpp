int longestPathNoPositiveCycle(
    int N, int S, int T,
    vector<Edge> edges
) {
    for(auto& e : edges)
        e.w = -e.w;

    const int INF = 1e9;
    vector<int> dist(N, INF);
    dist[S] = 0;

    for(int i = 1; i <= N - 1; i++) {
        for(const auto& e : edges) {
            if(dist[e.u] != INF &&
               dist[e.u] + e.w < dist[e.v]) {
                dist[e.v] = dist[e.u] + e.w;
            }
        }
    }

    return dist[T] == INF ? -1 : -dist[T];
}
