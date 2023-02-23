#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
const int N=2e5+10;
int n,m,dist[N],pre[N],cnt[N];//dist数组记录距离 pre数组记录路径前一个点 cnt数组记录路径上边的数量
vector<pii> h[N];

bool cmp(int x,int y){//比较到达x和y的路径字典序
    vector<int> a,b;
    a.push_back(x);
    b.push_back(y);
    while (pre[a.back()]) {//把前面的节点都存入vector中比较
        a.push_back(pre[a.back()]);
        b.push_back(pre[b.back()]);
    }
    //路径是从后往前得到的,所以反转之后比较
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    for (int i=0; i<(int)a.size(); i++) {
        if (a[i]==b[i]) {//节点相等则继续比较
            continue;
        }
        if (a[i]<b[i]) {//如果路径a当前节点编号更小则返回true
            return true;
        }
        return false;
    }
    return false;
}

int dijkstra(int st,int ed)
{
    memset(dist, 0x3f, sizeof(dist));
    memset(cnt, 0x3f, sizeof cnt);
    priority_queue<pii,vector<pii>,greater<pii>> heap;
    heap.push({0,st});
    dist[st]=0;
    cnt[st]=0;
    while (heap.size()) {
        auto [distance,cur]=heap.top();
        heap.pop();
        for (auto [x,w]: h[cur]) {
            if (distance+w>dist[x]) {
                continue;//路径长度更大则不用更新
            }
            if (distance+w<dist[x]) {//如果有更短的路径则直接更新
                dist[x]=distance+w;
                heap.push({dist[x],x});
                pre[x]=cur;
                cnt[x]=cnt[cur]+1;
                continue;
            }
            //路径长度相等,比较路段数
            if (cnt[x]<cnt[cur]+1) {
                continue;//当前路段数更少则不用更新
            }
            if (cnt[x]>cnt[cur]+1) {//如果路段数更少,则更新
                heap.push({dist[x],x});
                pre[x]=cur;
                cnt[x]=cnt[cur]+1;
                continue;
            }
            //路段数相等,比较路径节点字典序
            if (cmp(cur,pre[x])) {
                heap.push({dist[x],x});
                pre[x]=cur;
            }
        }
    }
    if (dist[ed]==0x3f3f3f3f) {
        return -1;
    }
    return dist[ed];
}

void printsfp(int ed){
    stack<int> st;
    st.push(ed);
    while (pre[st.top()]!=0) {
        st.push(pre[st.top()]);
    }
    while (st.size()) {
        cout<<st.top();
        st.pop();
        if (!st.empty()) {
            cout<<"->";
        }
    }
}

int main(){
    int cas=1;
    while (cin>>n) {
        for (int i=1; i<=n; i++) {
            for (int j=1; j<=n; j++) {
                int w;
                cin>>w;
                if (w!=-1) {
                    h[i].push_back({j,w});
                }
            }
        }
        int st,ed;
        cin>>st>>ed;
        cout<<"Case "<<cas++<<'\n';
        cout<<"The least distance from "<<st<<"->"<<ed<<" is "<<dijkstra(st,ed)<<'\n';
        cout<<"the path is ";
        printsfp(ed);
        cout<<'\n';
    }
}
