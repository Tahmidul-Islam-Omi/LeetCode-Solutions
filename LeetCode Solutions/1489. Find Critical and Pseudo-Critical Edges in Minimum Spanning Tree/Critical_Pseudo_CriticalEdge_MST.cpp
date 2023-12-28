class DS {
    vector<int> parent , size;

    public:
        DS(int n) {
            parent.resize(n+1 , 0);
            size.resize(n+1 , 0);

            for(int i=0; i<=n; i++) {
                parent[i] = i;
                size[i] = 1;
            }
        }

        int findUltParent(int node) {
            

            if( node == parent[node]) {
                return node;
            }

            return parent[node] = findUltParent(parent[node]);
            
        }

        void unionBySize(int u , int v) {
            int ulPar_u = findUltParent(u);
            int ulPar_v = findUltParent(v);

            if( ulPar_u == ulPar_v) {
                return;
            }

            else if(ulPar_u < ulPar_v) {
                parent[ulPar_u] = ulPar_v;
                size[ulPar_v] += size[ulPar_u];
            }

            else {
                parent[ulPar_v] = ulPar_u;
                size[ulPar_u] += size[ulPar_v];
            }

        }
};

bool compareAlgo(const pair < pair<int, int> , int> &a, const pair <pair<int, int> , int> &b) {
    return a.second < b.second;
}

int findMSTWeight1 (vector< pair < pair<int,int> , int > > edges_info , int vertices , int edge_idx) {
    // excluding edge
    DS ds(vertices);

    int mst_weight = 0;

    int edges = 0;

    vector< pair < pair<int,int> , int > > Updateedges_info;  

    for(int i=0; i<edges_info.size(); i++) {
        if( i != edge_idx) {
            Updateedges_info.push_back(edges_info[i]);
        }
    }

    sort( Updateedges_info.begin() ,  Updateedges_info.end() , compareAlgo);

    for(int i=0; i< Updateedges_info.size() ; i++) {
        
        int u = Updateedges_info[i].first.first;
        int v = Updateedges_info[i].first.second;


        if(ds.findUltParent(u) != ds.findUltParent(v)) {
            edges++;
            ds.unionBySize(u , v);
            mst_weight += Updateedges_info[i].second;         
        }

    }

    if( edges != vertices-1 ) {
        return INT_MAX;
    }

    return mst_weight;
    
}

int findMSTWeight2 (vector< pair < pair<int,int> , int > > edges_info , int vertices , int edge_idx) {

    // including edges_idx

    DS ds(vertices);

    int mst_weight = edges_info[edge_idx].second;

    int u = edges_info[edge_idx].first.first;
    int v = edges_info[edge_idx].first.second;

    ds.unionBySize(u , v);

    vector< pair < pair<int,int> , int > > Updateedges_info;  

    for(int i=0; i<edges_info.size(); i++) {
        if( i != edge_idx) {
            Updateedges_info.push_back(edges_info[i]);
        }
    }

    sort( Updateedges_info.begin() ,  Updateedges_info.end() , compareAlgo);
    
    for(int i=0; i< Updateedges_info.size() ; i++) {
        
        u = Updateedges_info[i].first.first;
        v = Updateedges_info[i].first.second;


        if(ds.findUltParent(u) != ds.findUltParent(v)) {

            ds.unionBySize(u , v);
            mst_weight += Updateedges_info[i].second;
            //MST.push_back(edges_info[i]);         
        }

    }

    return mst_weight;
}

vector < vector<int> > findCritical_PsedoCritical(vector< pair < pair<int,int> , int > > edges_info , int vertices) {
    
    int mst_weight = findMSTWeight1(edges_info, vertices , -1);

    vector < vector<int> > result(2);

    for(int i=0; i<edges_info.size(); i++) {
        int mst_weight_exclude = findMSTWeight1(edges_info, vertices , i);
        int mst_weight_include = findMSTWeight2(edges_info, vertices , i); 

        if(mst_weight_exclude > mst_weight) {
            result[0].push_back(i);
            // Critical
        }

        else if(mst_weight_include == mst_weight) {
            result[1].push_back(i);
            // Psedo Critical
        }
    }

    return result;

}

class Solution {
public:
    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {

        int vertices = n;
        vector< pair < pair<int,int> , int > > edges_info ;

        for(int i=0; i< edges.size(); i++) {

        pair<int, int> pr;
        pr.first = edges[i][0] , pr.second = edges[i][1] ;

        edges_info.push_back({pr , edges[i][2] });

    }


        vector< vector<int> > result = findCritical_PsedoCritical(edges_info , vertices);

        return result;
        
    }
};
