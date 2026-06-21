#include<bits/stdc++.h>
using ll=__int128_t;   // 使用 128 位整数，避免大数溢出
using namespace std;

// 模加：在模 mod 下计算 (a+b)
inline ll add(ll a,ll b,ll mod)
{
    return a+b>=mod?a+b-mod:a+b;
}

// 模乘：在模 p 下计算 (a*b)，避免溢出
inline ll mul(ll a,ll b,ll p)
{
    return (a*b-(ll)((__float128)a/p*b/p)*p+p)%p;
}

// 模减：在模 p 下计算 (a-b)
inline ll sub(ll a,ll b,ll p)
{
    return a<b?a-b+p:a-b;
}

// 最大公约数
inline ll gcd(ll a,ll b){ return b ? gcd(b,a % b) : a; }

// 输入大整数
inline void read(ll &ret)
{
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar(); // 跳过非数字
    ret=0;
    while(ch>='0'&&ch<='9')             // 逐位读取
        ret=ret*10+ch-'0',ch=getchar();
}

// 输出大整数
inline void writell(ll a)
{
    if(!a) return;
    writell(a/10);                      // 递归打印高位
    putchar(a%10+'0');                  // 打印最低位
}

// 快速幂：计算 a^b mod c
inline ll qpow(ll a,ll b,ll c)
{
    ll ans=1;
    while(b)
    {
        if(b&1) ans=mul(ans,a,c);       // 如果当前位为 1，乘上 a
        a=mul(a,a,c);                   // 平方迭代
        b>>=1;
    }
    return ans;
}

// Miller–Rabin 素性测试（概率版）
inline ll Miller_Rabin(ll p)
{
    if(p<2) return false;
    if(p==2) return true;
    if(p%2==0) return false;

    ll a=p-1,b=0;
    while(a%2==0) a>>=1,b++;            // 将 p-1 分解为 2^b * a

    for(ll i=0;i<10;i++)                // 随机测试 10 次
    {
        ll x=qpow(rand()%(p-2)+2,a,p),y=x;
        for(ll j=0;j<b;j++)
        {
            x=mul(x,x,p);
            if(x==1&&y!=1&&y!=p-1) return false; // 非平凡平方根
            y=x;
        }
        if(x!=1) return false;          // 最终必须为 1
    }
    return true;                        // 可能是素数
}

// Pollard’s Rho 随机化因数分解
inline ll Pollard_Rho(ll x)
{
    ll s=0,t=0;
    ll c=ll(rand()%(x-1))+1;            // 随机常数 c
    ll val=1;
    for(ll goal=1;goal<=1000000;goal++) // 迭代上限
    {
        for(ll step=1;step<=goal;step++)
        {
            t=add(mul(t,t,x),c,x);      // f(t) = t^2 + c mod x
            val=mul(val,abs(t-s),x);    // 累积差值
            if(step%20==0)
            {
                ll d=gcd(val,x);        // 检查公因数
                if(d>1) return d;
            }
        }
        ll d=gcd(val,x);
        if(d>1) return d;
    }
    return x;                           // 未找到因子
}

// 存储质因数及其次数
map<ll,int> mp;

// 分解函数
void solve(ll x)
{
    if(x<2) return;
    if(Miller_Rabin(x)) { mp[x]++; return; } // 如果是素数，计数+1
    ll p=Pollard_Rho(x);                     // 找到一个因子
    solve(p);                                // 分解因子 p
    solve(x/p);                              // 分解剩余部分
}

int main()
{
    ll x;
    while(1)
    {
        read(x);                             // 输入整数
        if(!x) break;                        // 输入 0 结束
        writell(x); putchar(':');            // 输出原数
        solve(x);                            // 分解
        for(auto i:mp)                       // 输出质因数分解结果
        {
            writell(i.first);                // 质因数
            putchar('^'); writell(i.second); // 指数
            putchar(' ');
        }
        putchar('\n');
    }
}

