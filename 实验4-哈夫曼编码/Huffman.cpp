#include<bits/stdc++.h>
using namespace std;
const int N = 110;
int cas=1;
struct node{
    int val,id;
    vector<int> leaves;
    bool operator < (const node & b) const{       //双关键字排序
        if(val==b.val) return id < b.id;
        return val > b.val;
    }
}tr[N];
void solve(){
    int n;
    cin>>n;
    vector<string> res(N);
    priority_queue<node> heap;
    for(int i=1,w;i<=n;++i){
        node tmp;
        cin>>w;
        tr[i].val = w;
        tmp.val = w;
        tmp.id = i;
        tmp.leaves.push_back(i);
        heap.push(tmp);             //初始将每个结点视作子树
    }
    int idx = n+1;
    while(!heap.empty()){
        node r = heap.top();
        heap.pop();
        if(heap.empty())
            break;
        node l = heap.top();
        heap.pop();      //取出权值最小的两个子树
        node t;
        t.val = r.val + l.val;          //合并权值
        t.id = idx++;
        for(int i=0;i<(int)r.leaves.size();++i){//右子树
            int id = r.leaves[i];
            res[id].push_back('1');
            t.leaves.push_back(id);//把叶子结点加到新合成的节点中
        }
        for(int i=0;i < (int)l.leaves.size(); ++i){//左子树
            int id = l.leaves[i];
            res[id].push_back('0');
            t.leaves.push_back(id);
        }
        heap.push(t);
    }
    cout<<"Case "<<cas++<<'\n';
    for(int i=1;i<=n;++i){
        reverse(res[i].begin(),res[i].end());
        cout<<tr[i].val<<" "<<res[i]<<'\n';
    }
}
int main()
{
    int T;
    cin>>T;
    while(T--){
        solve();
    }
    return 0;
}

