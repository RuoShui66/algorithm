#include <bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n=8;
int dx[8]={1,1,2,2,-1,-1,-2,-2},dy[8]={2,-2,1,-1,2,-2,1,-1};
int dist[N][N];
bool state[N][N];
int solve(int x,int y,int ex,int ey){
    queue<pair<int, int>> q;
    q.push({x,y});
    memset(dist, -1, sizeof dist);
    memset(state, 0, sizeof state);
    dist[x][y]=0;
    state[x][y]=true;
    while (q.size()) {
        auto [x2,y2]=q.front();
        q.pop();
        for (int i=0; i<8; i++) {
            int tx=x2+dx[i],ty=y2+dy[i];
            if (tx<1||tx>n||ty<1||ty>n||state[tx][ty]) {
                continue;
            }
            state[tx][ty]=true;
            q.push({tx,ty});
            dist[tx][ty]=dist[x2][y2]+1;
        }
    }
    return dist[ex][ey];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string st,ed;
    while (cin>>st) {
        cin>>ed;
        int sx,sy,ex,ey;
        sx=st[1]-'0';
        sy=st[0]-'a'+1;
        ex=ed[1]-'0';
        ey=ed[0]-'a'+1;
        int dist=solve(sx,sy,ex,ey);
        cout<<st<<"==>"<<ed<<": "<<dist<<" moves\n";
    }
}
