#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minScore(int n, vector<vector<int>>& roads) { 
        
        vector<vector<pair<int, int>>> adj(n + 1);
        for(auto &read : roads){
            int u = read[0];
            int v = read[1];
            int w = read[2];
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }

        vector<bool> vis(n + 1, false);
        queue<int> q;
        
        q.push(1);
        vis[1] = true;
        
        int ans = INT_MAX;
        
        while(!q.empty()){
            int node = q.front();
            q.pop();
            
            for(auto &edge : adj[node]){
                int nei = edge.first;
                int wt = edge.second;
               
                ans = min(ans, wt);
                
                if(!vis[nei]){
                    vis[nei] = true;
                    q.push(nei);
                }
            }
        }
        return ans;
    }
};