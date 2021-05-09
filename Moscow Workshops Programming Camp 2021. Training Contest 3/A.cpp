#include<bits/stdc++.h>
using namespace std;
const double eps = 1e-8;
int dcmp(double x)
{
	if(fabs(x)<eps)return 0;
	return x<0?-1:1;
}
struct Point3
{
	double x,y,z;
	Point3(double x=0,double y=0,double z=0):x(x),y(y),z(z){}
	void read()
	{
		scanf("%lf%lf%lf",&x,&y,&z);
	}
	void print()
	{
		printf("%lf %lf %lf\n",x,y,z);
	}
};
typedef Point3 Vector3;
Vector3 operator + (Vector3 A,Vector3 B)
{
	return Vector3(A.x+B.x,A.y+B.y,A.z+B.z);
}
Vector3 operator - (Vector3 A,Vector3 B)
{
	return Vector3(A.x-B.x,A.y-B.y,A.z-B.z);
}
Vector3 operator * (Vector3 A,double k)
{
	return Vector3(A.x*k,A.y*k,A.z*k);
}
Vector3 operator / (Vector3 A,double k)
{
	return Vector3(A.x/k,A.y/k,A.z/k);
}
double Dot(Vector3 A,Vector3 B)
{
	return A.x*B.x+A.y*B.y+A.z*B.z;
}
double Length(Vector3 A)
{
	return sqrt(Dot(A,A));
}
double DistanceToPlane(const Point3& p,const Point3& p0,const Vector3& n)
{
	return fabs(Dot(p-p0,n));
}
Point3 GetPlaneProjection(const Point3& p,const Point3& p0,const Vector3& n)
{
	return p-n*Dot(p-p0,n);
}
void rotate_to_horizontal(int n,Point3 *p,Point3 v)
{
	if(!dcmp(v.x)&&!dcmp(v.y))return;
	double a=atan2(v.y,v.x);
	double c=cos(a),s=sin(a);
	for(int i=0;i<n;++i)
	{
		Point3 t=p[i];
		p[i].x=t.x*c+t.y*s;
		p[i].y=t.y*c-t.x*s;
	}
	a=atan2(sqrt(v.x*v.x+v.y*v.y),v.z);
	c=cos(a);s=sin(a);
	for(int i=0;i<n;++i)
	{
		Point3 t=p[i];
		p[i].z=t.z*c+t.x*s;
		p[i].x=t.x*c-t.z*s;
	}
}
struct Point
{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
	void print()
	{
		printf("%lf %lf\n",x,y);
	}
};
typedef Point Vector;
Vector operator + (Vector A,Vector B)
{
	return Vector(A.x+B.x,A.y+B.y);
}
Vector operator - (Vector A,Vector B)
{
	return Vector(A.x-B.x,A.y-B.y);
}
Vector operator * (Vector A,double k)
{
	return Vector(A.x*k,A.y*k);
}
Vector operator / (Vector A,double k)
{
	return Vector(A.x/k,A.y/k);
}
double Dot(Vector A,Vector B)
{
    return A.x*B.x+A.y*B.y;
}
double Length(Vector A)
{
    return sqrt(Dot(A,A));
}
bool operator < (Point a,Point b)
{
    return a.x<b.x||(a.x== b.x&&a.y<b.y);
}
bool operator == (Point a,Point b)
{
    return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;
}
double Cross(Vector A,Vector B)
{
	return A.x*B.y-A.y*B.x;
}
vector<Point> ConvexHull(vector<Point>& p)
{
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    int n=p.size();
    int m=0;
    vector<Point> ch(n+1);
    for(int i=0;i<n;i++)
    {
        while(m>1&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0)m--;
        ch[m++]=p[i];
    }
    int k=m;
    for(int i=n-2;i>=0;i--)
    {
        while(m>k&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0)m--;
        ch[m++]=p[i];
    }
    if(n>1)m--;
    ch.resize(m);
    return ch;
}
Point GetLineIntersection(Point p, Vector v, Point q, Vector w)
{
    return p + v * Cross(w, p - q) / Cross(v, w);
}
struct Line
{
    Point p;
    Vector v;
    double ang;
    Line() {}
    Line(Point P, Vector v):p(P),v(v)
    {
        ang = atan2(v.y, v.x);
    }
    inline bool operator < (const Line& L) const
    {
        return ang < L.ang;
    }
    inline Point point(double t)
    {
        return p + v * t;
    }
};
inline Point GetLineIntersection(Line a, Line b)
{
    return GetLineIntersection(a.p, a.v, b.p, b.v);
}
inline bool OnLeft(const Line& L, const Point& p)
{
    return Cross(L.v, p-L.p) > 0;
}
vector<Point> HalfplaneIntersection(vector<Line> L)
{
    int n = L.size();
    sort(L.begin(), L.end());
    int first, last;
    vector<Point> p(n);
    vector<Line> q(n);
    vector<Point> ans;
    q[first=last=0] = L[0];
    for(int i = 1; i < n; i++)
    {
        while(first < last && !OnLeft(L[i], p[last-1])) last--;
        while(first < last && !OnLeft(L[i], p[first])) first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v, q[last-1].v)) < eps)
        {
            last--;
            if(OnLeft(q[last], L[i].p)) q[last] = L[i];
        }
        if(first < last) p[last-1] = GetLineIntersection(q[last-1], q[last]);
    }
    while(first < last && !OnLeft(q[first], p[last-1])) last--;
    if(last - first <= 1) return ans;
    p[last] = GetLineIntersection(q[last], q[first]);
    for(int i = first; i <= last; i++) ans.push_back(p[i]);
    return ans;
}
#define maxn 100005
int n,m;
Point3 a[maxn],b[maxn],O,aa[maxn],bb[maxn];
Vector3 VA,VB;
vector<Point> A,B;
vector<Line> LS;
int main()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i)a[i].read();
	VA.read();
	scanf("%d",&m);
	for(int i=0;i<m;++i)b[i].read();
	VB.read();
	VA=VA-VB;
	if(dcmp(VA.x)==0&&dcmp(VA.y)==0&&dcmp(VA.z)==0)
	{
		puts("NO");
		return 0;
	}
	VA=VA/Length(VA);
	O=Point3(0,0,0);
	for(int i=0;i<n;++i)aa[i]=GetPlaneProjection(a[i],O,VA);
	for(int i=0;i<m;++i)bb[i]=GetPlaneProjection(b[i],O,VA);
	rotate_to_horizontal(n,aa,VA);
	rotate_to_horizontal(m,bb,VA);
	for(int i=0;i<n;++i)A.push_back(Point(aa[i].x,aa[i].y));
	for(int i=0;i<m;++i)B.push_back(Point(bb[i].x,bb[i].y));
	A=ConvexHull(A);B=ConvexHull(B);
	n=A.size();m=B.size();
	for(int i=0;i<n;++i)LS.push_back(Line(A[i],A[(i+1)%n]-A[i]));
	for(int i=0;i<m;++i)LS.push_back(Line(B[i],B[(i+1)%m]-B[i]));
	vector<Point> Ans=HalfplaneIntersection(LS);
	if(Ans.size())puts("YES");
	else puts("NO");
	return 0;
}