#include <iostream>
using namespace std;
const int N=105;
int n,dp[N][N],pos[N][N],p[N];
const int inf=(1<<30);
int chain(int l,int r)
{
    int &v=dp[l][r];
    if(v>0)return v;
    if(l==r)return 0;
    int mn=inf;
    pos[l][r]=l;//pos[l][r]表示矩阵l到r在pos[l][r]后分开
    for(int k=l;k<r;k++)
    {
        int t=chain(l,k)+chain(k+1,r)+p[l-1]*p[k]*p[r];
        if(t<mn)
        {
            mn=t;
            pos[l][r]=k;
        }
    }
    return v=mn;
}
void print(int l, int r)
{
    if (l==r)
    {
        cout<<"A"<<l;
        return;
    }
    if (l!=1||r!=n) {
        cout << "(";
    }
    print(l, pos[l][r]);
    print(pos[l][r]+1, r);
    if (l!=1||r!=n) {
        cout << ")";
    }
}
int main()
{
    int cas=0;
    while (cin>>n) {
        memset(dp, 0, sizeof dp);
        cas++;
        for(int i=0;i<=n;i++)
            cin>>p[i];
        cout<<"Case "<<cas<<'\n';
        chain(1,n);
        cout<<dp[1][n]<<' ';
        print(1, n);
        cout<<'\n';
    }
    return 0;
}
