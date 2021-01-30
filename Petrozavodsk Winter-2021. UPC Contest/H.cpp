#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define PX 38247LL
#define PY 62231LL
#define PZ 67876LL
#define LIMIT 7000000000000LL
using namespace std;
typedef long long ll;
typedef pair<ll,ll> P;
int x,y,z;
const int base = 1000000000;
const int base_digits = 9; 
struct bigint {
    vector<int> a;
    int sign;
    /*<arpa>*/
    int size(){
	if(a.empty())return 0;
	int ans=(a.size()-1)*base_digits;
	int ca=a.back();
	while(ca)
	    ans++,ca/=10;
	return ans;
    }
    bigint operator ^(const bigint &v){
	bigint ans=1,a=*this,b=v;
	while(!b.isZero()){
	    if(b%2)
		ans*=a;
	    a*=a,b/=2;
	}
	return ans;
    }
    string to_string(){
	stringstream ss;
	ss << *this;
	string s;
	ss >> s;
	return s;
    }
    int sumof(){
	string s = to_string();
	int ans = 0;
	for(auto c : s)  ans += c - '0';
	return ans;
    }
    /*</arpa>*/
    bigint() :
	sign(1) {
    }
 
    bigint(long long v) {
	*this = v;
    }
 
    bigint(const string &s) {
	read(s);
    }
 
    void operator=(const bigint &v) {
	sign = v.sign;
	a = v.a;
    }
 
    void operator=(long long v) {
	sign = 1;
	a.clear();
	if (v < 0)
	    sign = -1, v = -v;
	for (; v > 0; v = v / base)
	    a.push_back(v % base);
    }
 
    bigint operator+(const bigint &v) const {
	if (sign == v.sign) {
	    bigint res = v;
 
	    for (int i = 0, carry = 0; i < (int) max(a.size(), v.a.size()) || carry; ++i) {
		if (i == (int) res.a.size())
		    res.a.push_back(0);
		res.a[i] += carry + (i < (int) a.size() ? a[i] : 0);
		carry = res.a[i] >= base;
		if (carry)
		    res.a[i] -= base;
	    }
	    return res;
	}
	return *this - (-v);
    }
 
    bigint operator-(const bigint &v) const {
	if (sign == v.sign) {
	    if (abs() >= v.abs()) {
		bigint res = *this;
		for (int i = 0, carry = 0; i < (int) v.a.size() || carry; ++i) {
		    res.a[i] -= carry + (i < (int) v.a.size() ? v.a[i] : 0);
		    carry = res.a[i] < 0;
		    if (carry)
			res.a[i] += base;
		}
		res.trim();
		return res;
	    }
	    return -(v - *this);
	}
	return *this + (-v);
    }
 
    void operator*=(int v) {
	if (v < 0)
	    sign = -sign, v = -v;
	for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
	    if (i == (int) a.size())
		a.push_back(0);
	    long long cur = a[i] * (long long) v + carry;
	    carry = (int) (cur / base);
	    a[i] = (int) (cur % base);
	    //asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
	}
	trim();
    }
 
    bigint operator*(int v) const {
	bigint res = *this;
	res *= v;
	return res;
    }
 
    void operator*=(long long v) {
	if (v < 0)
	    sign = -sign, v = -v;
	for (int i = 0, carry = 0; i < (int) a.size() || carry; ++i) {
	    if (i == (int) a.size())
		a.push_back(0);
	    long long cur = a[i] * (long long) v + carry;
	    carry = (int) (cur / base);
	    a[i] = (int) (cur % base);
	    //asm("divl %%ecx" : "=a"(carry), "=d"(a[i]) : "A"(cur), "c"(base));
	}
	trim();
    }
 
    bigint operator*(long long v) const {
	bigint res = *this;
	res *= v;
	return res;
    }
 
    friend pair<bigint, bigint> divmod(const bigint &a1, const bigint &b1) {
	int norm = base / (b1.a.back() + 1);
	bigint a = a1.abs() * norm;
	bigint b = b1.abs() * norm;
	bigint q, r;
	q.a.resize(a.a.size());
 
	for (int i = a.a.size() - 1; i >= 0; i--) {
	    r *= base;
	    r += a.a[i];
	    int s1 = r.a.size() <= b.a.size() ? 0 : r.a[b.a.size()];
	    int s2 = r.a.size() <= b.a.size() - 1 ? 0 : r.a[b.a.size() - 1];
	    int d = ((long long) base * s1 + s2) / b.a.back();
	    r -= b * d;
	    while (r < 0)
		r += b, --d;
	    q.a[i] = d;
	}
 
	q.sign = a1.sign * b1.sign;
	r.sign = a1.sign;
	q.trim();
	r.trim();
	return make_pair(q, r / norm);
    }
 
    bigint operator/(const bigint &v) const {
	return divmod(*this, v).first;
    }
 
    bigint operator%(const bigint &v) const {
	return divmod(*this, v).second;
    }
 
    void operator/=(int v) {
	if (v < 0)
	    sign = -sign, v = -v;
	for (int i = (int) a.size() - 1, rem = 0; i >= 0; --i) {
	    long long cur = a[i] + rem * (long long) base;
	    a[i] = (int) (cur / v);
	    rem = (int) (cur % v);
	}
	trim();
    }
 
    bigint operator/(int v) const {
	bigint res = *this;
	res /= v;
	return res;
    }
 
    int operator%(int v) const {
	if (v < 0)
	    v = -v;
	int m = 0;
	for (int i = a.size() - 1; i >= 0; --i)
	    m = (a[i] + m * (long long) base) % v;
	return m * sign;
    }
 
    void operator+=(const bigint &v) {
	*this = *this + v;
    }
    void operator-=(const bigint &v) {
	*this = *this - v;
    }
    void operator*=(const bigint &v) {
	*this = *this * v;
    }
    void operator/=(const bigint &v) {
	*this = *this / v;
    }
 
    bool operator<(const bigint &v) const {
	if (sign != v.sign)
	    return sign < v.sign;
	if (a.size() != v.a.size())
	    return a.size() * sign < v.a.size() * v.sign;
	for (int i = a.size() - 1; i >= 0; i--)
	    if (a[i] != v.a[i])
		return a[i] * sign < v.a[i] * sign;
	return false;
    }
 
    bool operator>(const bigint &v) const {
	return v < *this;
    }
    bool operator<=(const bigint &v) const {
	return !(v < *this);
    }
    bool operator>=(const bigint &v) const {
	return !(*this < v);
    }
    bool operator==(const bigint &v) const {
	return !(*this < v) && !(v < *this);
    }
    bool operator!=(const bigint &v) const {
	return *this < v || v < *this;
    }
 
    void trim() {
	while (!a.empty() && !a.back())
	    a.pop_back();
	if (a.empty())
	    sign = 1;
    }
 
    bool isZero() const {
	return a.empty() || (a.size() == 1 && !a[0]);
    }
 
    bigint operator-() const {
	bigint res = *this;
	res.sign = -sign;
	return res;
    }
 
    bigint abs() const {
	bigint res = *this;
	res.sign *= res.sign;
	return res;
    }
 
    long long longValue() const {
	long long res = 0;
	for (int i = a.size() - 1; i >= 0; i--)
	    res = res * base + a[i];
	return res * sign;
    }
 
    friend bigint gcd(const bigint &a, const bigint &b) {
	return b.isZero() ? a : gcd(b, a % b);
    }
    friend bigint lcm(const bigint &a, const bigint &b) {
	return a / gcd(a, b) * b;
    }
 
    void read(const string &s) {
	sign = 1;
	a.clear();
	int pos = 0;
	while (pos < (int) s.size() && (s[pos] == '-' || s[pos] == '+')) {
	    if (s[pos] == '-')
		sign = -sign;
	    ++pos;
	}
	for (int i = s.size() - 1; i >= pos; i -= base_digits) {
	    int x = 0;
	    for (int j = max(pos, i - base_digits + 1); j <= i; j++)
		x = x * 10 + s[j] - '0';
	    a.push_back(x);
	}
	trim();
    }
 
    friend istream& operator>>(istream &stream, bigint &v) {
	string s;
	stream >> s;
	v.read(s);
	return stream;
    }
 
    friend ostream& operator<<(ostream &stream, const bigint &v) {
	if (v.sign == -1)
	    stream << '-';
	stream << (v.a.empty() ? 0 : v.a.back());
	for (int i = (int) v.a.size() - 2; i >= 0; --i)
	    stream << setw(base_digits) << setfill('0') << v.a[i];
	return stream;
    }
 
    static vector<int> convert_base(const vector<int> &a, int old_digits, int new_digits) {
	vector<long long> p(max(old_digits, new_digits) + 1);
	p[0] = 1;
	for (int i = 1; i < (int) p.size(); i++)
	    p[i] = p[i - 1] * 10;
	vector<int> res;
	long long cur = 0;
	int cur_digits = 0;
	for (int i = 0; i < (int) a.size(); i++) {
	    cur += a[i] * p[cur_digits];
	    cur_digits += old_digits;
	    while (cur_digits >= new_digits) {
		res.push_back(int(cur % p[new_digits]));
		cur /= p[new_digits];
		cur_digits -= new_digits;
	    }
	}
	res.push_back((int) cur);
	while (!res.empty() && !res.back())
	    res.pop_back();
	return res;
    }
 
    typedef vector<long long> vll;
 
    static vll karatsubaMultiply(const vll &a, const vll &b) {
	int n = a.size();
	vll res(n + n);
	if (n <= 32) {
	    for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		    res[i + j] += a[i] * b[j];
	    return res;
	}
 
	int k = n >> 1;
	vll a1(a.begin(), a.begin() + k);
	vll a2(a.begin() + k, a.end());
	vll b1(b.begin(), b.begin() + k);
	vll b2(b.begin() + k, b.end());
 
	vll a1b1 = karatsubaMultiply(a1, b1);
	vll a2b2 = karatsubaMultiply(a2, b2);
 
	for (int i = 0; i < k; i++)
	    a2[i] += a1[i];
	for (int i = 0; i < k; i++)
	    b2[i] += b1[i];
 
	vll r = karatsubaMultiply(a2, b2);
	for (int i = 0; i < (int) a1b1.size(); i++)
	    r[i] -= a1b1[i];
	for (int i = 0; i < (int) a2b2.size(); i++)
	    r[i] -= a2b2[i];
 
	for (int i = 0; i < (int) r.size(); i++)
	    res[i + k] += r[i];
	for (int i = 0; i < (int) a1b1.size(); i++)
	    res[i] += a1b1[i];
	for (int i = 0; i < (int) a2b2.size(); i++)
	    res[i + n] += a2b2[i];
	return res;
    }
 
    bigint operator*(const bigint &v) const {
	vector<int> a6 = convert_base(this->a, base_digits, 6);
	vector<int> b6 = convert_base(v.a, base_digits, 6);
	vll a(a6.begin(), a6.end());
	vll b(b6.begin(), b6.end());
	while (a.size() < b.size())
	    a.push_back(0);
	while (b.size() < a.size())
	    b.push_back(0);
	while (a.size() & (a.size() - 1))
	    a.push_back(0), b.push_back(0);
	vll c = karatsubaMultiply(a, b);
	bigint res;
	res.sign = sign * v.sign;
	for (int i = 0, carry = 0; i < (int) c.size(); i++) {
	    long long cur = c[i] + carry;
	    res.a.push_back((int) (cur % 1000000));
	    carry = (int) (cur / 1000000);
	}
	res.a = convert_base(res.a, 6, base_digits);
	res.trim();
	return res;
    }
};
ll u,v;
bigint abc,def;
bigint query(ll x)
{
    printf("? %lld\n",x);
    fflush(stdout);
    string str;
    cin>>str;
    return bigint(str);
}
int getlen(bigint x)
{
    int cnt=0;
    while(x>0)
    {
        x=x/10;
        cnt++;
    }
    return cnt;
}
bigint query_a()
{
    ll x=(u+PY*PZ);
    if(x>=LIMIT) x=(u-PY*PZ);
    bigint res=query(x);
    bigint g=gcd(abc,res);
    assert(getlen(abc/g)==31);
    return abc/g;
}
bigint query_b()
{
    ll x=(u+PX*PZ);
    if(x>=LIMIT) x=(u-PX*PZ);
    bigint res=query(x);
    bigint g=gcd(abc,res);
    assert(getlen(abc/g)==32);
    return abc/g;
}
bigint query_c()
{
    ll x=(u+PX*PY);
    if(x>=LIMIT) x=(u-PX*PY);
    bigint res=query(x);
    bigint g=gcd(abc,res);
    assert(getlen(abc/g)==33);
    return abc/g;
}
bigint query_d()
{
    ll x=(v+PY*PZ);
    if(x>=LIMIT) x=(v-PY*PZ);
    bigint res=query(x);
    bigint g=gcd(def,res);
    assert(getlen(def/g)==31);
    return def/g;
}
bigint query_e()
{
    ll x=(v+PX*PZ);
    if(x>=LIMIT) x=(v-PX*PZ);
    bigint res=query(x);
    bigint g=gcd(def,res);
    assert(getlen(def/g)==32);
    return def/g;
}
bigint query_f()
{
    ll x=(v+PX*PY);
    if(x>=LIMIT) x=(v-PX*PY);
    bigint res=query(x);
    bigint g=gcd(def,res);
    assert(getlen(def/g)==33);
    return def/g;
}
struct node
{
    ll x,y,z;
};
node get_rep(ll u)
{
    node ret;
    ret.x=u%PX;
    ret.y=u%PY;
    ret.z=u%PZ;
    return ret;
}
ll r[3][3],val[3];
int extgcd(int a,int b,int &x,int &y)
{
    int d=a;
    if(b!=0)
    {
        d=extgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
    {
        x=1;
        y=0;
    }
    return d;
}
int mod_inverse(int a,int m)
{
    int x,y;
    extgcd(a,m,x,y);
    return (m+x%m)%m;
}
ll solve(vector<P> &v)
{
    int n=v.size();
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            r[i][j]=mod_inverse(v[i].S,v[j].S);
    ll ans=0;
    for(int i=0;i<n;i++)
    {
        val[i]=v[i].F;
        for(int j=0;j<i;j++)
        {
            val[i]=r[j][i]*(val[i]-val[j]);
            val[i]=val[i]%v[i].S;
            if(val[i]<0) val[i]+=v[i].S;
        }
    }
    ll base=1;
    for(int i=0;i<n;i++)
    {
        ans+=base*val[i];
        base*=v[i].S;
    }
    return ans;
}
void answer(bigint &x)
{
    printf("! ");
    cout<<x<<endl;
    fflush(stdout);
    exit(0);
}
int main()
{
    scanf("%lld%lld",&u,&v);
    abc=query(u),def=query(v);
    bigint g=gcd(abc,def);
    bigint a,b,c,d,e,f;
    if(abc==g)
    {
        a=query_a();
        b=query_b();
        c=abc/a/b;
        bigint res=(a+b+c)*2;
        answer(res);
    }
    else if(g==1)
    {
        node p=get_rep(u),q=get_rep(v);
        set<ll> s;
        s.insert(p.x); s.insert(p.y); s.insert(p.z);
        s.insert(q.x); s.insert(q.y); s.insert(q.z);
        vector<P> vv;
        int now=0; ll tmp;
        while(now<PX)
        {
            while(s.count(now)||now==550757) now++;
            vv.clear();
            vv.push_back(P(now,PX)); vv.push_back(P(p.y,PY)); vv.push_back(P(q.z,PZ));
            tmp=solve(vv);
            if(tmp>=0&&tmp<LIMIT) break; else now++;
        }
        assert(now<PX);
        bigint xbf=query(tmp); s.insert(now);
        now=0;
        while(now<PY)
        {
            while(s.count(now)||now==311155) now++;
            vv.clear();
            vv.push_back(P(q.x,PX)); vv.push_back(P(now,PY)); vv.push_back(P(p.z,PZ));
            tmp=solve(vv);
            if(tmp>=0&&tmp<LIMIT) break; else now++;
        }
        assert(now<PY);
        bigint dyc=query(tmp); s.insert(now);
        now=0;
        while(now<PZ)
        {
            while(s.count(now)||now==50907) now++;
            vv.clear();
            vv.push_back(P(p.x,PX)); vv.push_back(P(q.y,PY)); vv.push_back(P(now,PZ));
            tmp=solve(vv);
            if(tmp>=0&&tmp<LIMIT) break; else now++;
        }
        assert(now<PZ);
        bigint aez=query(tmp); s.insert(now);
        a=gcd(aez,abc); b=gcd(xbf,abc); c=gcd(dyc,abc);
        d=gcd(dyc,def); e=gcd(aez,def); f=gcd(xbf,def);
        bigint res=a+b+c+d+e+f;
        answer(res);
    }
    else 
    {
        int len=getlen(g);
        if(len==31)
        {
            a=g; d=g;
            b=query_b(); e=query_e();
            c=abc/a/b; f=def/d/e;
            bigint res=a+b+c+d+e+f;
            answer(res);
        }
        else if(len==32)
        {
            b=g; e=g;
            a=query_a(); d=query_d();
            c=abc/a/b; f=def/d/e;
            bigint res=a+b+c+d+e+f;
            answer(res);
        }
        else if(len==33)
        {
            c=g; f=g;
            a=query_a(); d=query_d();
            b=abc/a/c; e=def/d/f;
            bigint res=a+b+c+d+e+f;
            answer(res);
        }
        bigint rem=abc/g;
        len=getlen(rem);
        if(len==31)
        {
            a=rem; d=def/g;
            b=query_b(); e=query_e();
            c=abc/a/b; f=def/d/e;
            bigint res=a+b+c+d+e+f;
            answer(res);
        }
        else if(len==32)
        {
            b=rem; e=def/g;
            a=query_a(); d=query_d();
            c=abc/a/b; f=def/d/e;
            bigint res=a+b+c+d+e+f;
            answer(res);
        }
        else if(len==33)
        {
            c=rem; f=def/g;
            a=query_a(); d=query_d();
            b=abc/a/c; e=def/d/f;
            bigint res=a+b+c+d+e+f;
            answer(res);
        }
        else assert(0);
    }
    return 0;
}