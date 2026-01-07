#include <bits/stdc++.h>
using namespace std;

int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> grid(N, vector<int>(M));
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            cin >> grid[i][j];
        }
    }

    const int INF = 1e9;
    vector<vector<int>> dist(N, vector<int>(M, INF));

    // Min-heap: {cost, {x, y}}
    priority_queue<
        pair<int, pair<int,int>>,
        vector<pair<int, pair<int,int>>>,
        greater<>
    > pq;

    dist[0][0] = grid[0][0];
    pq.push({grid[0][0], {0, 0}});

    while(!pq.empty()) {
        auto top = pq.top();
        pq.pop();

        int cost = top.first;
        int x = top.second.first;
        int y = top.second.second;

        if(cost > dist[x][y]) continue;

        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if(nx >= 0 && ny >= 0 && nx < N && ny < M) {
                int newCost = cost + grid[nx][ny];
                if(newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    pq.push({newCost, {nx, ny}});
                }
            }
        }
    }

    cout << dist[N-1][M-1] << endl;
    return 0;
}
