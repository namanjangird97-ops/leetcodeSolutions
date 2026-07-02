class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        
        
        vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        
        
        vector<vector<int>> max_health(m, vector<int>(n, -1));
        
       
        priority_queue<pair<int, pair<int, int>>> pq;
        
        int start_health = health - grid[0][0];
        if (start_health <= 0) return false;
        
        pq.push({start_health, {0, 0}});
        max_health[0][0] = start_health;
        
        while (!pq.empty()) {
            auto [curr_health, cell] = pq.top();
            auto [r, c] = cell;
            pq.pop();
            
            if (r == m - 1 && c == n - 1) {
                return curr_health >= 1;
            }
            
            if (curr_health < max_health[r][c]) continue;
            
            for (auto& dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;
                
                if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                    int next_health = curr_health - grid[nr][nc];
               
                    if (next_health > 0 && next_health > max_health[nr][nc]) {
                        max_health[nr][nc] = next_health;
                        pq.push({next_health, {nr, nc}});
                    }
                }
            }
        }
        
        return false;
    }
};