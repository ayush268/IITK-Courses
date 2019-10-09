#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef vector<ii> vpi;
typedef pair<vpi, vpi> pvpi;
typedef map<int, int> mii;
typedef pair<vvi, mii> vvmi;
typedef pair<vpi, vvmi> vpvvmi;
#define typeof(x) __typeof__(x)
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define tr(c,i) for(typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define present(c,x) ((c).find(x) != (c).end())
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define fr(i,c,s) for(i=0; i<c; i+=s)
#define fd(v, i) (find(v.begin(), v.end(), i) != v.end())
#define rev(v) reverse(v.begin(), v.end())

int n,m;
vpi reverse_path(vpi);
pvpi compute_augmenting_path(vvi, vpi);
vpi get_alternating_walk(vvi, vpi);
pvpi get_augmenting_cycle(vpi, vpi);
vpvvmi get_reduced_graph_and_matching(vvi, set<int>, vpi);
vpi update_matching(vpi, vpi);
pvpi modify_path_and_matching(vpi, vpi, int);
pvpi restore_path_and_matching(vpi, vpi, mii, set<int>, vvi, vpi, vpi);
bool is_augmenting_path(vpi);

int main() {

    int i,j,k;
    scanf("%d %d", &n, &m);
    vvi graph;
    fr(i,n,1)
    {
        vi temp;
        graph.pb(temp);
    }
    
    fr(k,m,1)
    {
        scanf("%d %d", &i, &j);
        graph[i-1].pb(j-1);
        graph[j-1].pb(i-1);
    }

    //fr(i, n, 1)
    //{
    //    printf("%d -> ", i);
    //    fr(j, sz(graph[i]), 1)
    //    {
    //        printf("%d ", graph[i][j]);
    //    }
    //    printf("\n");
    //}
    //printf("\n");

    vpi matching;
    pvpi path_and_matching = compute_augmenting_path(graph, matching);
    vpi augmented_path = path_and_matching.first;
    matching = path_and_matching.second;
    while(sz(augmented_path) != 0)
    {
        matching = update_matching(augmented_path, matching);
        path_and_matching = compute_augmenting_path(graph, matching);
        augmented_path = path_and_matching.first;
        matching = path_and_matching.second;
    }

    fr(k, sz(matching), 1)
    {
        if(matching[k].first <= matching[k].second)
            continue;
        int temp = matching[k].first;
        matching[k].first = matching[k].second;
        matching[k].second = temp;
    }
    sort(matching.begin(), matching.end());

    printf("%d\n", sz(matching));
    fr(k, sz(matching), 1)
    {
        ii couple = matching[k];
        printf("%d %d\n", couple.first+1, couple.second+1);
    }
    return 0;
}

vpi reverse_path(vpi path)
{
    int i, temp;
    rev(path);
    fr(i, sz(path), 1)
    {
        temp = path[i].first;
        path[i].first = path[i].second;
        path[i].second = temp;
    }
    return path;
}

pvpi compute_augmenting_path(vvi graph, vpi matching)
{
    int i, k, j;
    vpi walk;
    walk = get_alternating_walk(graph, matching);

    //printf("Walk -> %d\n", sz(walk));
    //fr(k, sz(walk), 1)
    //{
    //    ii couple = walk[k];
    //    printf("%d %d\n", couple.first+1, couple.second+1);
    //}
    //printf("\n");

    //printf("Matching -> %d\n", sz(matching));
    //fr(k, sz(matching), 1)
    //{
    //    ii couple = matching[k];
    //    printf("%d %d\n", couple.first+1, couple.second+1);
    //}
    //printf("\n");

    if(sz(walk) == 0)
        return make_pair(walk, matching);
    else
    {
        if(is_augmenting_path(walk))
            return make_pair(walk, matching);
        else
        {
            pvpi cycle_and_matching = get_augmenting_cycle(walk, matching);
            matching = cycle_and_matching.second;
            vpi cycle = cycle_and_matching.first;
            set<int> cycle_v;
            fr(i, sz(cycle), 1)
                cycle_v.insert(cycle[i].first);
            vpvvmi matching_and_graph = get_reduced_graph_and_matching(graph, cycle_v, matching);
            vpi re_matching = matching_and_graph.first;
            vvi re_graph = matching_and_graph.second.first;
            mii graph_mapping = matching_and_graph.second.second;

            //printf("\n");
            //printf("Old Matching of size %d\n", sz(matching));
            //fr(k, sz(matching), 1)
            //{
            //    ii couple = matching[k];
            //    printf("%d %d\n", couple.first+1, couple.second+1);
            //}
            //printf("\n");

            //printf("Printing Mapping\n");
            //tr(graph_mapping, iter)
            //    printf("%d -> %d\n", iter->first+1, iter->second+1);
            //printf("\n");

            //printf("Printing Graph\n");
            //fr(i, sz(re_graph), 1)
            //{
            //    printf("%d -> ", i+1);
            //    fr(j, sz(re_graph[i]), 1)
            //    {
            //        printf("%d ", re_graph[i][j]+1);
            //    }
            //    printf("\n");
            //}
            //printf("\n");

            //printf("Matching of size %d\n", sz(re_matching));
            //fr(k, sz(re_matching), 1)
            //{
            //    ii couple = re_matching[k];
            //    printf("%d %d\n", couple.first+1, couple.second+1);
            //}
            //printf("\n");

            pvpi new_path_and_matching = compute_augmenting_path(re_graph, re_matching);
            vpi new_path = new_path_and_matching.first;
            re_matching = new_path_and_matching.second;

            //printf("Reduced graph path %d\n", sz(new_path));
            //fr(k, sz(new_path), 1)
            //{
            //    ii couple = new_path[k];
            //    printf("%d %d\n", couple.first+1, couple.second+1);
            //}
            //printf("\n");


            //printf("Reduced graph matching %d\n", sz(re_matching));
            //fr(k, sz(re_matching), 1)
            //{
            //    ii couple = re_matching[k];
            //    printf("%d %d\n", couple.first+1, couple.second+1);
            //}

            if(sz(new_path) == 0)
                return make_pair(new_path, matching);
            else
            {

                //new_path.clear();
                //re_matching.clear();
                //new_path.pb(make_pair(0,1));
                //new_path.pb(make_pair(1,2));
                //new_path.pb(make_pair(2,3));
                //new_path.pb(make_pair(3,4));
                //new_path.pb(make_pair(4,5));
                //re_matching.pb(make_pair(1,2));
                //re_matching.pb(make_pair(3,4));
                //printf("Path before %d\n", sz(new_path));
                //fr(k, sz(new_path), 1)
                //{
                //    ii couple = new_path[k];
                //    printf("%d %d\n", couple.first+1, couple.second+1);
                //}
                //printf("\n");

                //printf("Matching before reducing %d\n", sz(re_matching));
                //fr(k, sz(re_matching), 1)
                //{
                //    ii couple = re_matching[k];
                //    printf("%d %d\n", couple.first+1, couple.second+1);
                //}
                //printf("\n");

                pvpi modified_path_and_matching = modify_path_and_matching(new_path, re_matching, *cycle_v.begin());
                new_path = modified_path_and_matching.first;
                re_matching = modified_path_and_matching.second;

                //printf("Path after %d\n", sz(new_path));
                //fr(k, sz(new_path), 1)
                //{
                //    ii couple = new_path[k];
                //    printf("%d %d\n", couple.first+1, couple.second+1);
                //}
                //printf("\n");


                //printf("Matching after reducing %d\n", sz(re_matching));
                //fr(k, sz(re_matching), 1)
                //{
                //    ii couple = re_matching[k];
                //    printf("%d %d\n", couple.first+1, couple.second+1);
                //}

                //exit(0);
                
                pvpi final_path_and_matching = restore_path_and_matching(new_path, re_matching, graph_mapping, cycle_v, graph, cycle, matching);
                return final_path_and_matching;
            }
        }
    }
}

pvpi restore_path_and_matching(vpi path, vpi re_matching, mii graph_mapping, set<int> cycle_v, vvi graph, vpi cycle, vpi matching)
{
    int i, v_c = *cycle_v.begin();
    //printf("V_c -> %d\n", v_c+1);
    int last = sz(path)-1;
    mii reverse_mapping;
    tr(graph_mapping, it)
        reverse_mapping[it->second] = it->first;
    fr(i, last, 1)
    {
        path[i].first = reverse_mapping[path[i].first];
        path[i].second = reverse_mapping[path[i].second];
    }
    path[last].first = reverse_mapping[path[last].first];
    if(path[last].second != v_c)
    {
        path[last].second = reverse_mapping[path[last].second];
        return make_pair(path, matching);
    }
    else
    {
        int v,u = path[last].first;
        fr(i, sz(graph[u]), 1)
            if(cycle_v.find(graph[u][i]) != cycle_v.end())
                break;
        v = graph[u][i];
        path[last].second = v;
        fr(i, sz(cycle), 1)
            if(cycle[i].first == v)
                break;
        rotate(cycle.begin(), cycle.begin()+i, cycle.end());
        fr(i, sz(re_matching), 1)
        {
            re_matching[i].first = reverse_mapping[re_matching[i].first];
            re_matching[i].second = reverse_mapping[re_matching[i].second];
        }
        for(i=1; i<sz(cycle); i+=2)
            re_matching.pb(cycle[i]);
        return make_pair(path, re_matching);
    }
}

pvpi modify_path_and_matching(vpi path, vpi matching, int v_c)
{
    int i,k;
    fr(i, sz(path), 1)
    {
        if(path[i].first == v_c)
        {
            if(i%2)
                break;
            else
            {
                path = reverse_path(path);
                break;
            }
        }
    }
    if((i==sz(path)) || (i==0))
        return make_pair(path, matching);
    vpi aug_path;
    fr(i, sz(path), 1)
    {
        if(path[i].first == v_c)
            break;
        aug_path.pb(path[i]);
    }
    path.erase(path.begin(), path.begin()+i);
    matching = update_matching(reverse_path(path), matching);
    return make_pair(aug_path, matching);
}

vpvvmi get_reduced_graph_and_matching(vvi graph, set<int> cycle_v, vpi matching)
{
    int i,k=0,j;

    int v_c = *cycle_v.begin();
    mii mapping;
    bool flag=false, flag_cycle=false;
    fr(i, sz(graph), 1)
    {
        if(cycle_v.find(i) != cycle_v.end())
        {
            if(flag)
                continue;
            flag = true;
        }
        mapping[i] = k++;
    }
    
    vvi new_graph;
    fr(i, k, 1)
    {
        vi temp;
        new_graph.pb(temp);
    }
    set<int> edges_v_c;
    fr(i, sz(graph), 1)
    {
        flag_cycle = false;
        flag = false;
        if(cycle_v.find(i) == cycle_v.end())
            k = mapping[i];
        else
        {
            flag_cycle = true;
            k = v_c;
        }
        fr(j, sz(graph[i]), 1)
        {
            if(cycle_v.find(graph[i][j]) != cycle_v.end())
            {
                flag = true;
                continue;
            }
            if(flag_cycle)
                edges_v_c.insert(mapping[graph[i][j]]);
            else
                new_graph[k].pb(mapping[graph[i][j]]);
        }
        if(flag && !flag_cycle)
            new_graph[k].pb(v_c);
    }
    tr(edges_v_c, iter)
        new_graph[v_c].pb(*iter);

    vpi new_matching;
    fr(i, sz(matching), 1)
    {
        if(cycle_v.find(matching[i].first) != cycle_v.end() || cycle_v.find(matching[i].second) != cycle_v.end())
        {
            if(cycle_v.find(matching[i].first) != cycle_v.end() && cycle_v.find(matching[i].second) != cycle_v.end())
                continue;
            else
            {
                printf("I am here\n");
                if(cycle_v.find(matching[i].first) != cycle_v.end())
                    new_matching.pb(make_pair(mapping[matching[i].second], v_c));
                else
                    new_matching.pb(make_pair(mapping[matching[i].first], v_c));
            }
        }
        else
            new_matching.pb(make_pair(mapping[matching[i].first], mapping[matching[i].second]));
    }

    return make_pair(new_matching, make_pair(new_graph, mapping));
}

pvpi get_augmenting_cycle(vpi walk, vpi matching)
{
    int i,k;
    bool visited[n];
    fr(i, n, 1)
        visited[i] = false;
    visited[walk[0].first] = true;
    fr(i, sz(walk), 1)
    {
        if(visited[walk[i].second])
            break;
        visited[walk[i].second] = true;
    }
    if(i == (sz(walk)-1))
        return make_pair(walk, matching);
    vpi path;
    vpi cycle;
    bool flag = true;
    fr(k, i+1, 1)
    {
        if(walk[k].first == walk[i].second)
            flag = false;
        if(flag)
            path.pb(walk[k]);
        else
            cycle.pb(walk[k]);
    }
    matching = update_matching(path, matching);
    return make_pair(cycle, matching);
}

bool is_augmenting_path(vpi walk)
{
    int i;
    bool visited[n];
    fr(i, n, 1)
        visited[i] = false;
    visited[walk[0].first] = true;
    fr(i, sz(walk), 1)
    {
        if(visited[walk[i].second])
            return false;
        visited[walk[i].second] = true;
    }
    return true;
}

vpi get_alternating_walk(vvi graph, vpi matching)
{
    int i,j,k;
    int v = sz(graph);
    bool unmatch_v[v];
    vpi e_not_m_set;
    fr(i, v, 1)
    {
        unmatch_v[i] = true;
        fr(j, sz(graph[i]), 1)
        {
            if(fd(matching, make_pair(i,graph[i][j])) || fd(matching, make_pair(graph[i][j],i)))
                continue;
            e_not_m_set.pb(make_pair(i,graph[i][j]));
        }
    }

    fr(i, sz(matching), 1)
    {
        unmatch_v[matching[i].first] = false;
        unmatch_v[matching[i].second] = false;
    }

    /* V  -> 0 to n
     * V' -> n+1 to 2n+1
     * t  -> n
     * s' -> 2n+1
     */
    vvi bigraph;
    vi path;
    int parent[2*v+2];
    bool visited[2*v+2];
    fr(i, (2*v)+2, 1)
    {
        parent[i] = -1;
        visited[i] = false;
        vi temp;
        bigraph.pb(temp);
    }
    fr(i, sz(e_not_m_set), 1)
    {
        int a,b;
        a = e_not_m_set[i].first;
        b = e_not_m_set[i].second;
        bigraph[a].pb(b+v+1);
    }
    fr(i, sz(matching), 1)
    {
        int a,b;
        a = matching[i].first;
        b = matching[i].second;
        bigraph[a+v+1].pb(b);
        bigraph[b+v+1].pb(a);
    }
    fr(i, v, 1)
    {
        if(!unmatch_v[i])
            continue;
        bigraph[(2*v)+1].pb(i);
        bigraph[i+v+1].pb(v);
    }

    stack<int> st;
    st.push(2*v+1);
    while(!st.empty())
    {
        int u = st.top();
        st.pop();
        if(!visited[u])
            visited[u] = true;
        tr(bigraph[u],iter)
        {
            if(!visited[*iter])
            {
                parent[*iter] = u;
                st.push(*iter);
            }
        }
    }
    vpi walk;
    if(!visited[v])
        return walk;
    int vertex = parent[v];
    while(vertex != (2*v+1))
    {
        path.pb(vertex);
        vertex = parent[vertex];
    }
    rev(path);
    fr(i, sz(path)-1, 1)
        walk.pb(make_pair(path[i]%(v+1), path[i+1]%(v+1)));
    return walk;
}

vpi update_matching(vpi path, vpi matching)
{
    int i,j;
    vpi new_matching;
    fr(i, sz(path), 2)
    {
        new_matching.pb(path[i]);
        if(i+1 < sz(path))
        {
            ii rev_pair;
            rev_pair.first = path[i+1].second;
            rev_pair.second = path[i+1].first;
            matching.erase(remove(matching.begin(), matching.end(), path[i+1]), matching.end());
            matching.erase(remove(matching.begin(), matching.end(), rev_pair), matching.end());
        }
    }
    fr(i, sz(matching), 1)
        new_matching.pb(matching[i]);
    return new_matching;
}
