#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = 1e9;

int bfs(int s, int t, vector<int>& parent,
        vector<vector<int>>& residual,
        vector<vector<int>>& adj) {

    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;

    queue<pair<int,int>> q;
    q.push({s, INF});

    while(!q.empty()){
        int u = q.front().first;
        int flow = q.front().second;
        q.pop();

        for(int v : adj[u]){
            if(parent[v] == -1 && residual[u][v] > 0){
                parent[v] = u;
                int newFlow = min(flow, residual[u][v]);
                if(v == t) return newFlow;
                q.push({v, newFlow});
            }
        }
    }
    return 0;
}

int edmondsKarp(int s, int t, int N,
                vector<vector<int>>& residual,
                vector<vector<int>>& adj) {

    int maxFlow = 0;
    vector<int> parent(N);

    while(true){
        int flow = bfs(s, t, parent, residual, adj);
        if(flow == 0) break;

        maxFlow += flow;
        int cur = t;
        while(cur != s){
            int prev = parent[cur];
            residual[prev][cur] -= flow;
            residual[cur][prev] += flow;
            cur = prev;
        }
    }
    return maxFlow;
}

void addEdge(int u, int v, int c,
             vector<vector<int>>& adj,
             vector<vector<int>>& residual) {

    adj[u].push_back(v);
    adj[v].push_back(u);
    residual[u][v] += c;
}

int main() {
    int N, M, K;
    cin >> N >> M >> K;

    vector<pair<int,int>> permits(K);
    for(int i = 0; i < K; i++){
        cin >> permits[i].first >> permits[i].second;
        permits[i].first--;   // 0-based
        permits[i].second--;
    }

    vector<int> capacity(M);
    for(int i = 0; i < M; i++){
        cin >> capacity[i];
    }

    int Z;
    cin >> Z;

    vector<pair<int,int>> changes(Z);
    for(int i = 0; i < Z; i++){
        cin >> changes[i].first >> changes[i].second;
        changes[i].first--;  // 0-based
    }

    int totalNodes = N + M + 2;
    int S = N + M;
    int T = N + M + 1;

    for(int year = 0; year < Z; year++){

        // Rebuild graph every year
        vector<vector<int>> adj(totalNodes);
        vector<vector<int>> residual(totalNodes,
                                     vector<int>(totalNodes, 0));

        // Source → Trucks
        for(int i = 0; i < N; i++){
            addEdge(S, i, 1, adj, residual);
        }

        // Truck → Road (permits)
        for(auto &p : permits){
            int truck = p.first;
            int road  = p.second;
            addEdge(truck, N + road, 1, adj, residual);
        }

        // Road → Sink (capacity)
        for(int j = 0; j < M; j++){
            addEdge(N + j, T, capacity[j], adj, residual);
        }

        // Compute answer BEFORE reduction
        int ans = edmondsKarp(S, T, totalNodes, residual, adj);
        cout << ans << "\n";

        // Apply capacity reduction
        int road = changes[year].first;
        int reduceBy = changes[year].second;
        capacity[road] = max(0, capacity[road] - reduceBy);
    }

    return 0;
}
