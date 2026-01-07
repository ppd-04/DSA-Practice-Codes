#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct flight {
    int a, b, cost, duration;  // ADD: duration field
};

// MODIFIED: State now includes time_spent
// Priority queue element: {cost, {node, {coupon_used, time_spent}}}
vector<vector<int>> dijkstra(vector<vector<pair<pair<int,int>, int>>>& adj, int src, int T) {
    // MODIFIED: Store {cost, {node, {used, time}}}
    priority_queue<pair<int, pair<int, pair<int,int>>>, 
                   vector<pair<int, pair<int, pair<int,int>>>>, 
                   greater<>> pq;
    
    int sz = adj.size();
    
    // MODIFIED: Still track best cost for each (node, coupon_used)
    vector<vector<int>> dist(sz, vector<int>(2, INT_MAX));
    
    // MODIFIED: Track minimum time to reach each state
    vector<vector<int>> min_time(sz, vector<int>(2, INT_MAX));
    
    pq.push({0, {src, {0, 0}}});  // {cost=0, {node=src, {used=0, time=0}}}
    dist[src][0] = 0;
    min_time[src][0] = 0;
    
    while(!pq.empty()) {
        auto t = pq.top();
        pq.pop();
        
        int d = t.first;
        int u = t.second.first;
        int used = t.second.second.first;
        int time_spent = t.second.second.second;
        
        // ADDED: Prune if time constraint violated
        if(time_spent > T) {
            continue;
        }
        
        // Skip if we found a better path
        if(d > dist[u][used]) {
            continue;
        }
        
        // MODIFIED: adj now stores {cost, duration} and destination
        for(auto &edge : adj[u]) {
            int v = edge.first.first;        // destination
            int w = edge.first.second;       // cost
            int duration = edge.second;      // duration
            
            // ADDED: Calculate new time
            int new_time = time_spent + duration;
            
            // ADDED: Skip if time constraint would be violated
            if(new_time > T) {
                continue;
            }
            
            // Transition without using coupon
            if(dist[u][used] + w < dist[v][used]) {
                dist[v][used] = dist[u][used] + w;
                min_time[v][used] = new_time;
                pq.push({dist[v][used], {v, {used, new_time}}});
            }
            // ADDED: If same cost but less time, still explore
            else if(dist[u][used] + w == dist[v][used] && new_time < min_time[v][used]) {
                min_time[v][used] = new_time;
                pq.push({dist[v][used], {v, {used, new_time}}});
            }
            
            // Transition with using coupon (only if not used yet)
            if(used == 0) {
                int hf = w / 2;
                if(dist[u][0] + hf < dist[v][1]) {
                    dist[v][1] = dist[u][0] + hf;
                    min_time[v][1] = new_time;
                    pq.push({dist[v][1], {v, {1, new_time}}});
                }
                // ADDED: If same cost but less time, still explore
                else if(dist[u][0] + hf == dist[v][1] && new_time < min_time[v][1]) {
                    min_time[v][1] = new_time;
                    pq.push({dist[v][1], {v, {1, new_time}}});
                }
            }
        }
    }
    
    return dist;
}

void solve() {
    int n, m, T;  // ADDED: T for time constraint
    cin >> n >> m >> T;
    
    vector<flight> flights(m);
    
    // MODIFIED: Adjacency list now stores {{destination, cost}, duration}
    vector<vector<pair<pair<int,int>, int>>> adj(n + 1);
    
    for(int i = 0; i < m; i++) {
        cin >> flights[i].a >> flights[i].b >> flights[i].cost >> flights[i].duration;
        adj[flights[i].a].push_back({{flights[i].b, flights[i].cost}, flights[i].duration});
    }
    
    vector<vector<int>> finalDestination = dijkstra(adj, 1, T);
    
    // Output the minimum of using coupon vs not using (both must satisfy time constraint)
    int result = min(finalDestination[n][0], finalDestination[n][1]);
    
    if(result == INT_MAX) {
        cout << -1 << endl;  // No valid path within time T
    } else {
        cout << result << endl;
    }
}

int main() {
    solve();
    return 0;
}
