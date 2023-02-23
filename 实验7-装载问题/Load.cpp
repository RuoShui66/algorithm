#include <bits/stdc++.h>
using namespace std;
const int N=30;
int n,w[N],c1,c2,sum;
int bestw;//第一艘船能装的最大装载重量
string best,cur;//最佳分配方案 当前分配方案
void dfs(int u,int curw){
    if (u==n+1) {//已经分配完
        if (sum-curw>c2) {
            return;//剩余货物第二艘船装不下 不合法的装配方案
        }
        if (curw>bestw) {
            bestw=curw;
            best=cur;
        }
        if (curw==bestw&&cur>best) {//如果存在多种最大的方案 选择字典序更大的
            best=cur;
        }
        return;
    }
    if (curw+w[u]<=c1) {
        cur[u]='1';//能选则选上该货物
        dfs(u+1, curw+w[u]);
        cur[u]='0';//回溯时恢复现场
    }
    dfs(u+1, curw);//不选该货物
}

int main(){
    int cas=1;
    while (cin>>n) {
        best.resize(n+1, '0');
        cur.resize(n+1, '0');
        sum=0;
        bestw=0;
        for (int i=1; i<=n; i++) {
            cin>>w[i];
            sum+=w[i];
        }
        cin>>c1>>c2;
        dfs(1,0);
        cout<<"Case "<<cas++<<'\n';
        if (bestw+c2<sum) {//两艘船能装的最大重量仍装不下 则不能装载
            cout<<"No\n";
            continue;
        }
        best=best.substr(1,n);
        cout<<bestw<<' '<<best<<'\n';
    }
}
