#include<iostream>
using namespace std;
int board[1100][1100];
int id = 1;

void fillboard(int x,int y,int tx,int ty,int size)//(x,y)为当前棋盘的左上角,(tx,ty)为特殊方格所在的坐标
//size为当前棋盘的宽度
{
   if(size==1) return ;//递归边界
   int t=id++;//骨牌号
   int len=size/2;//偏离距离
   //覆盖左上角子棋盘
   if(tx<x+len && ty<y+len)
       fillboard(x,y,tx,ty,len);//特殊方格在此棋盘中
   else //此棋盘中无特殊方格，用t号L型骨牌覆盖右下角
   {
       board[x+len-1][y+len-1]=t;
       //覆盖其余方格
       fillboard(x,y,x+len-1,y+len-1,len);
   }
   //覆盖右上角子棋盘
   if(tx<x+len && ty>=y+len)
       fillboard(x,y+len,tx,ty,len);//特殊方格在此棋盘中
   else //此棋盘中无特殊方格，用t号L型骨牌覆盖左下角
   {
       board[x+len-1][y+len]=t;
       //覆盖其余方格
       fillboard(x,y+len,x+len-1,y+len,len);
   }
   //覆盖左下角子棋盘
   if(tx>=x+len && ty<y+len)//特殊方格在此棋盘中
       fillboard(x+len,y,tx,ty,len);
   else //此棋盘中无特殊方格，用t号L型骨牌覆盖右上角
   {
       board[x+len][y+len-1]=t;
       //覆盖其余方格
       fillboard(x+len,y,x+len,y+len-1,len);
   }
   //覆盖右下角子棋盘
   if(tx>=x+len && ty>=y+len)//特殊方格在此棋盘中
       fillboard(x+len,y+len,tx,ty,len);
   else //此棋盘中无特殊方格，用t号L型骨牌覆盖左上角
   {
       board[x+len][y+len]=t;
       //覆盖其余方格
       fillboard(x+len,y+len,x+len,y+len,len);
   }
}

int main()
{
   int i,j;
   int k,cas=0;
   while(cin>>k)
   {
       cas++;
       id=1;
       int size = 1<<k;
       int x,y;
       cin>>x>>y;
       board[x][y]=0;
       fillboard(1, 1, x, y, size);
       cout<<"Case "<<cas<<": n="<<size<<'\n';
       for(i=1; i<=size; i++)
       {
           for(j = 1; j <=size; j++){
               if (!board[i][j]) {
                   cout<<"#\t";
               }
               else cout<< board[i][j]<<"\t";
           }
           cout<<"\n";
       }
   }
   return 0;
}


