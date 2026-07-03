#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size(); // Fixed: changed .length() to .size()
        
        // Build the adjacency list: adj[u] = {{v, cost}}
        vector<vector<pair<int, int>>> adj(n);
        int max_cost = -1;
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int cost = edge[2];
            adj[u].push_back({v, cost});
            max_cost = max(max_cost, cost);
        }

        // Helper lambda to check if a valid path exists where all edges have cost >= mid
        auto check = [&](int mid) -> bool {
            // Min-heap for Dijkstra: {current_total_cost, node}
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            vector<long long> dist(n, -1);
            
            pq.push({0, 0});
            dist[0] = 0;

            while (!pq.empty()) {
                auto [curr_cost, u] = pq.top();
                pq.pop();

                if (curr_cost > dist[u]) continue;
                if (u == n - 1) return curr_cost <= k;

                for (const auto& [v, edge_cost] : adj[u]) {
                    // Skip if the target node is offline or edge cost is less than our binary search guess
                    if (!online[v] || edge_cost < mid) continue;

                    if (dist[v] == -1 || curr_cost + edge_cost < dist[v]) {
                        dist[v] = curr_cost + edge_cost;
                        pq.push({dist[v], v});
                    }
                }
            }
            return dist[n - 1] != -1 && dist[n - 1] <= k;
        }; // Fixed: properly closing the check lambda scope

        // Binary search space for the maximum path score
        int low = 0, high = max_cost;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid)) {
                ans = mid;        // mid is valid, try to find a larger minimum edge cost
                low = mid + 1;
            } else {
                high = mid - 1;   // mid is too restrictive, lower the threshold
            }
        }

        return ans;
    }
};