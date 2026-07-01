class Solution {
public:
    int n;
    vector<vector<int>> directions{{1, 0}, {-1, 0}, {0, -1}, {0, 1}};

    bool check(vector<vector<int>>& distNearestThief, int sf) {
        if (distNearestThief[0][0] < sf) return false;

        queue<pair<int, int>> que;
        vector<vector<bool>> visited(n, vector<bool>(n, false));
        
        que.push({0, 0});
        visited[0][0] = true;

        while (!que.empty()) {
            int curr_i = que.front().first;
            int curr_j = que.front().second;
            que.pop();

            if (curr_i == n - 1 && curr_j == n - 1) {
                return true;
            }

            for (auto& dir : directions) {
                int new_i = curr_i + dir[0];
                int new_j = curr_j + dir[1];

                if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < n && !visited[new_i][new_j]) {
                    if (distNearestThief[new_i][new_j] < sf) {
                        continue; 
                    }
                    que.push({new_i, new_j});
                    visited[new_i][new_j] = true;
                }
            }
        }
        return false;
    } // Removed the extra semicolon here

    int maximumSafenessFactor(vector<vector<int>>& grid) {
        n = grid.size();
        
        // 1. Multi-source BFS to compute minimum distance to any thief
        vector<vector<int>> distNearestThief(n, vector<int>(n, -1));
        queue<pair<int, int>> que;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    que.push({i, j});
                    distNearestThief[i][j] = 0;
                }
            }
        }
        
        while (!que.empty()) {
            auto [curr_i, curr_j] = que.front();
            que.pop();
            
            for (auto& dir : directions) {
                int new_i = curr_i + dir[0];
                int new_j = curr_j + dir[1];
                
                if (new_i >= 0 && new_i < n && new_j >= 0 && new_j < n && distNearestThief[new_i][new_j] == -1) {
                    distNearestThief[new_i][new_j] = distNearestThief[curr_i][curr_j] + 1;
                    que.push({new_i, new_j});
                }
            }
        }
        
        // 2. Binary Search on the safeness factor
        int low = 0, high = 2 * n, ans = 0;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(distNearestThief, mid)) {
                ans = mid;
                low = mid + 1; // Try to maximize safeness factor
            } else {
                high = mid - 1;
            }
        }
        
        return ans;
    }
}; // This closing brace for the class was missing