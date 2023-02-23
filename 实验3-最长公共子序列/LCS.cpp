#include <bits/stdc++.h>
#ifdef DEBUG
#define debug(x) cerr<<__LINE__<<"行 [" << #x << "] = "<<x<< endl;
#else
#define debug(...)
#endif
using namespace std;
typedef pair<int, int> pii;
int n,m;
const int N=210,M=70,NPOS=-1;//NPOS为数组默认值，M为字母表长度，N为序列长度
int func(char ch){
    if (ch>='a'&&ch<='z') {
        return ch-'a';
    }
    if (ch>='A'&&ch<='Z') {
        return ch-'A'+26;
    }
    if (ch>='0'&&ch<='9') {
        return ch-'0'+52;
    }
    return 0;
}
char func2(int x){
    if (x>=0&&x<=25) {
        return 'a'+x;
    }
    if (x>25&&x<=51) {
        return 'A'+x-26;
    }
    if (x>=52) {
        return '0'+x-52;
    }
    return '0';
}
class SequenceAM {// 序列自动机 Sequence Auto Machine
    public:
        int nxt[N][M]; // 核心数组,代表从第i个位置开始，字符j出现的第一个位置
        string s;  // 当前串
    void init() {  // 初始化序列自动机
        fill(nxt[s.size()], nxt[s.size()]+M, NPOS);
        for (int i=(int)s.size()-1; i>=0; i--) {  // 倒序初始化
            memcpy(nxt[i], nxt[i+1], sizeof nxt[i]);
            nxt[i][func(s[i])]=i+1;  // 更新数组
        }
    }
};
SequenceAM a,b;
int dp[N][N],len,id,cnt,path[N][N];
string ans,s1,s2;
void dfs(int x,int y){
    if (ans.size()==len) {
        cnt++;
        for (auto x: ans) {
            cout<<x<<' ';
        }
        cout<<'\n';
    }
    for (int i=0; i<62; i++) {
        if (a.nxt[x][i]!=NPOS&&b.nxt[y][i]!=NPOS) {
            ans.push_back(func2(i));
            dfs(a.nxt[x][i], b.nxt[y][i]);
            ans.pop_back();
        }
    }
}
int cal_len(){
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            if (s1[i-1]==s2[j-1]) {
                dp[i][j]=dp[i-1][j-1]+1;
                path[i][j]=0;
            }
            else if (dp[i-1][j]>=dp[i][j-1]){
                dp[i][j]=dp[i-1][j];
                path[i][j]=1;
            }
            else{
                dp[i][j]=dp[i][j-1];
                path[i][j]=2;
            }
        }
    }
    return dp[n][m];
}
void solve(){
    memset(dp, 0, sizeof dp);
    memset(path, 0, sizeof path);
    cnt=0;
    id++;
    cin>>n>>m;
    s1.resize(n);
    s2.resize(m);
    for (auto &x: s1) {
        cin>>x;
    }
    for (auto &x: s2) {
        cin>>x;
    }
    len=cal_len();
    cout<<"Case "<<id<<'\n';
    cout<<"The length of LCS="<<len<<"\nLCS(X,Y):\n";
    a.s=s1;b.s=s2;
    a.init();
    b.init();
    dfs(0, 0);
    cout<<"Total number="<<cnt<<'\n';
    cout<<"b table:\n";
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            cout<<path[i][j]<<' ';
        }
        cout<<'\n';
    }
    cout<<"c table:\n";
    for (int i=1; i<=n; i++) {
        for (int j=1; j<=m; j++) {
            cout<<dp[i][j]<<' ';
        }
        cout<<'\n';
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t=1;
    cin>>t;
    while (t--) {
        solve();
    }
    return 0;
}

