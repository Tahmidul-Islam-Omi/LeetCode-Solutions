class Solution {

    public:
     int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector< vector< pair<int,int> > > adjList(n+1);

        for(int i=0; i<flights.size(); i++) {
            adjList[flights[i][0]].push_back( {flights[i][2] , flights[i][1]} );  // dist , node
        }

        vector<int> visited(n+1 , INT_MAX);

        queue< pair < int ,pair<int,int> > > q;  // stops , dist , node
        q.push({0 ,{0, src}});
        visited[src] = 0;

        while (!q.empty())
        {
            int stops = q.front().first;
            int dist = q.front().second.first;
            int u = q.front().second.second;

            q.pop();

            if( stops > k) {
                continue;
            }

            for(auto it: adjList[u]) {
                int v = it.second;
                int w = it.first;

                if( dist + w < visited[v] && stops <= k) {
                     visited[v] = dist + w;
                    q.push({ stops+1 , { dist+w , v}});
                }
            }

        }

        if( visited[dst] != INT_MAX) {
            return visited[dst];
        }

        else {
            return -1;
        }
        
    }
};
