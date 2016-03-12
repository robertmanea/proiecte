#include <iostream>
#include <fstream>
//Matrice de numere complexe reprezentate ca structuri inlantuite
using namespace std;

template<class T>
class nrcomplex
{

    T re,im;
    public:
    template<class X> friend class mcomplex;
    nrcomplex(T x, T y) {re=x;im=y;}
    nrcomplex(){re=im=0;}
    template<class U> friend istream& operator>>(istream&,nrcomplex<U>&);
    template<class U> friend ifstream& operator>>(ifstream&,nrcomplex<U>&);
    template<class U> friend ostream& operator<<(ostream&,nrcomplex<U>&);
    nrcomplex<T> operator+(nrcomplex<T>);
    nrcomplex<T> operator-(nrcomplex<T>);
    nrcomplex<T> operator*(nrcomplex<T>);
    int operator!=(nrcomplex<T>);
    bool egalcuzero();
};
template<class T>
class mcomplex
{
    protected:
    struct elem{int l,c; nrcomplex<T> val;};
    struct matr{elem Flavia; matr *urm;}*prim,*p,*ultim;
    int m,n;
    public:
    mcomplex(int l, int c)
    {
        nrcomplex<T> x;
        this->m=l;
        this->n=c;
        this->prim=new typename mcomplex<T>::matr;
        this->prim->Flavia.val=x;
        this->prim->Flavia.l=1;this->prim->Flavia.c=1;
        this->prim->urm=NULL;
        this->ultim=this->prim;
        for(int i=1;i<=this->m;i++)
        for(int j=1;j<=this->n;j++) {if(i==1 && j==1) j++;
                                     this->p=new typename mcomplex<T>::matr;
                                     this->p->Flavia.val=x;
                                     this->p->Flavia.l=i;this->p->Flavia.c=j;
                                     this->ultim->urm=this->p;
                                     this->p->urm=NULL;
                                     this->ultim=this->p;}
    }
    mcomplex(){}
    mcomplex(const mcomplex& z)
    {
        if(z.prim==NULL) this->prim=NULL;
        else {this->prim=new typename mcomplex<T>::matr;
              this->prim=z.prim;}
        this->p=this->prim;
        z.p=z.prim->urm;
        for(int i=1;i<=z.m;i++)
        for(int j=1;j<=z.n;j++) if(i!=1 || j!=0) {if(z.p==NULL) this->p->urm=NULL;
                                                  else {this->p->urm=new typename mcomplex<T>::matr;
                                                        this->p=z.p;}
                                                  this->p=this->p->urm;
                                                  z.p=z.p->urm;}
    }
    template<class U> friend istream& operator>>(istream&,mcomplex<U>&);
    template<class U> friend ifstream& operator>>(ifstream&,mcomplex<U>&);
    template<class U> friend ostream& operator<<(ostream&,mcomplex<U>&);
    mcomplex<T> operator+(mcomplex<T>);
    mcomplex<T> operator*(mcomplex<T>);
    virtual nrcomplex<T> det()
    {
    mcomplex<T> y=*this; nrcomplex<T> s;
    if(y.m!=y.n) {cout<<"NU SE POATE EFECTUA"; return s;}
    if(y.m==1) {s=y.prim->Flavia.val; return s;}
    else if(y.m==2) {s=s+y.prim->Flavia.val*y.ultim->Flavia.val-y.prim->urm->Flavia.val*y.prim->urm->urm->Flavia.val; return s;}
    for(int i=0;i<y.m;i++) {nrcomplex<T> prad,prsc;
                            y.p=y.prim;
                            int k=1;
                            while(y.p->Flavia.c!=k+i) y.p=y.p->urm;
                            prad=y.p->Flavia.val; k++;
                            while(k<=y.m) {int o;
                                           if(k+i>y.m) o=k+i-y.m;
                                           else o=k+i;
                                           if(y.p->Flavia.l==k && y.p->Flavia.c==o) {prad=prad*y.p->Flavia.val;
                                                                                     k++;
                                                                                     y.p=y.prim;}
                                           else y.p=y.p->urm;}
                            k=1;
                            int o;
                            if(y.m-k+i+1>y.m) o=i-k+1;
                            else o=y.m-k+i+1;
                            while(y.p->Flavia.c!=o) y.p=y.p->urm;
                            prsc=y.p->Flavia.val; k++;
                            while(k<=y.m) {if(y.m-k+i+1>y.m) o=i-k+1;
                                           else o=y.m-k+i+1;
                                           if(y.p->Flavia.l==k && y.p->Flavia.c==o) {prsc=prsc*y.p->Flavia.val;
                                                                                     k++;
                                                                                     y.p=y.prim;}
                                           else y.p=y.p->urm;}
                            s=s+prad-prsc;}
    if(y.m>3) {nrcomplex<T> ar,are=ar-s;
               return are;}
    return s;
    }
    mcomplex<T> stelat();
};
template<class T>
class mpatr:public mcomplex<T>
{
    public:
    mpatr(int l):mcomplex<T>(l,l)
    {
        nrcomplex<T> x;
        this->m=l;
        this->n=l;
        this->prim=new typename mcomplex<T>::matr;
        this->prim->Flavia.val=x;
        this->prim->Flavia.l=1;this->prim->Flavia.c=1;
        this->prim->urm=NULL;
        this->ultim=this->prim;
        for(int i=1;i<=this->m;i++)
        for(int j=1;j<=this->n;j++) {if(i==1 && j==1) j++;
                                     this->p=new typename mcomplex<T>::matr;
                                     this->p->Flavia.val=x;
                                     this->p->Flavia.l=i;this->p->Flavia.c=j;
                                     this->ultim->urm=this->p;
                                     this->p->urm=NULL;
                                     this->ultim=this->p;}
    }
    mpatr(){}
    mpatr(const mpatr& z)
    {
        if(z.prim==NULL) this->prim=NULL;
        else {this->prim=new typename mpatr<T>::matr;
              this->prim=z.prim;}
        this->p=this->prim;
        z.p=z.prim->urm;
        for(int i=1;i<=z.m;i++)
        for(int j=1;j<=z.n;j++) if(i!=1 || j!=0) {if(z.p==NULL) this->p->urm=NULL;
                                                  else {this->p->urm=new typename mpatr<T>::matr;
                                                        this->p=z.p;}
                                                  this->p=this->p->urm;
                                                  z.p=z.p->urm;}
    }
    ~mpatr()
    {

        for(int i=0;i<this->m;i++)
        for(int j=0;j<this->n;j++) {if(this->prim==NULL) break;
                                    this->p=this->prim;
                                    this->prim=this->prim->urm;
                                    delete this->p;}
    }
    virtual nrcomplex<T> det()
    {
    mpatr<T> y=*this; nrcomplex<T> s;
    if(y.m==1) {s=y.prim->Flavia.val; return s;}
    else if(y.m==2) {s=s+y.prim->Flavia.val*y.ultim->Flavia.val-y.prim->urm->Flavia.val*y.prim->urm->urm->Flavia.val; return s;}
    for(int i=0;i<y.m;i++) {nrcomplex<T> prad,prsc;
                            y.p=y.prim;
                            int k=1;
                            while(y.p->Flavia.c!=k+i) y.p=y.p->urm;
                            prad=y.p->Flavia.val; k++;
                            while(k<=y.m) {int o;
                                           if(k+i>y.m) o=k+i-y.m;
                                           else o=k+i;
                                           if(y.p->Flavia.l==k && y.p->Flavia.c==o) {prad=prad*y.p->Flavia.val;
                                                                                     k++;
                                                                                     y.p=y.prim;}
                                           else y.p=y.p->urm;}
                            k=1;
                            int o;
                            if(y.m-k+i+1>y.m) o=i-k+1;
                            else o=y.m-k+i+1;
                            while(y.p->Flavia.c!=o) y.p=y.p->urm;
                            prsc=y.p->Flavia.val; k++;
                            while(k<=y.m) {if(y.m-k+i+1>y.m) o=i-k+1;
                                           else o=y.m-k+i+1;
                                           if(y.p->Flavia.l==k && y.p->Flavia.c==o) {prsc=prsc*y.p->Flavia.val;
                                                                                     k++;
                                                                                     y.p=y.prim;}
                                           else y.p=y.p->urm;}
                            s=s+prad-prsc;}
    if(y.m>3) {nrcomplex<T> ar,are=ar-s;
               return are;}
    return s;
}
};
template<class T>
class mpatrtri:public mpatr<T>
{
    public:
    mpatrtri(int l):mcomplex<T>(l,l)
    {
        nrcomplex<T> x;
        this->m=l;
        this->n=l;
        this->prim=new typename mcomplex<T>::matr;
        this->prim->Flavia.val=x;
        this->prim->Flavia.l=1;this->prim->Flavia.c=1;
        this->prim->urm=NULL;
        this->ultim=this->prim;
        for(int i=1;i<=this->m;i++)
        for(int j=1;j<=this->n;j++) {if(i==1 && j==1) j++;
                                     this->p=new typename mcomplex<T>::matr;
                                     this->p->Flavia.val=x;
                                     this->p->Flavia.l=i;this->p->Flavia.c=j;
                                     this->ultim->urm=this->p;
                                     this->p->urm=NULL;
                                     this->ultim=this->p;}
    }
    mpatrtri(){}
    mpatrtri(const mpatrtri& z)
    {
        if(z.prim==NULL) this->prim=NULL;
        else {this->prim=new typename mpatrtri<T>::matr;
              this->prim=z.prim;}
        this->p=this->prim;
        z.p=z.prim->urm;
        for(int i=1;i<=z.m;i++)
        for(int j=1;j<=z.n;j++) if(i!=1 || j!=0) {if(z.p==NULL) this->p->urm=NULL;
                                                  else {this->p->urm=new typename mpatrtri<T>::matr;
                                                        this->p=z.p;}
                                                  this->p=this->p->urm;
                                                  z.p=z.p->urm;}
    }
    ~mpatrtri()
    {

        for(int i=0;i<this->m;i++)
        for(int j=0;j<this->n;j++) {if(this->prim==NULL) break;
                                     this->p=this->prim;
                                     this->prim=this->prim->urm;
                                     delete this;}
    }
    int diagonala();
    int scalara();
    virtual nrcomplex<T> det()
    {
    mpatrtri<T> y=*this; nrcomplex<T> s;
    y.p=y.prim;
    for(int i=0;i<y.m;i++)
    for(int j=0;j<y.n;j++) {if(i==j) {if(s.egalcuzero()) s=s+y.p->Flavia.val;
                                      else s=s*y.p->Flavia.val;}
                            y.p=y.p->urm;}
    if(y.m>3) {nrcomplex<T> ar,are=ar-s;
               return are;}
    return s;
}
};

template<class T>
int mpatrtri<T>::diagonala()
{
    int pp2=0; this->p=this->prim;
    for(int i=0;i<this->m;i++)
    for(int j=0;j<this->n;j++) {if(i==j) if(this->p->Flavia.val.egalcuzero()==false) {pp2=1; break;}
                                 this->p=this->p->urm;}
    if(pp2==0) {cout<<"Matricea nu este diagonala"; return 0;}
    this->p=this->prim;
    for(int i=0;i<this->m;i++)
    for(int j=0;j<this->n;j++) {if(j>i) if(this->p->Flavia.val.egalcuzero()==false) {cout<<"Matricea nu este diagonala"; return 0;}
                                 if(i+j<2*i) if(this->p->Flavia.val.egalcuzero()==false) {cout<<"Matricea nu este diagonala"; return 0;}
                                 this->p=this->p->urm;}
    cout<<"Matricea este diagonala\n"; return 1;
}
template<class T>
int mpatrtri<T>::scalara()
{
    if(this->diagonala()==0) {cout<<"=> nu este scalara"; return 0;}
    this->p=this->prim;
    nrcomplex<T> x=this->p->Flavia.val;
    for(int i=0;i<this->m;i++)
    for(int j=0;j<this->n;j++) {if(i==j) if(this->p->Flavia.val!=x) {cout<<"Matricea nu este scalara"; return 0;}
                                 this->p=this->p->urm;}
    cout<<"Matricea este scalara"; return 1;
}
template<class T>
mcomplex<T> mcomplex<T>::operator+(mcomplex<T> z)
{
    mcomplex<T> y=*this;
    if(y.m!=z.m || y.n!=z.n) {cout<<"NU SE POATE EFECTUA, MATRICEA URMATOARE NU ESTE COMPATIBILA:"; return y;}
    mcomplex<T> w;
    w.m=y.m;
    w.n=y.n;
    w.prim=new mcomplex<T>::matr;
    w.p=w.prim;
    w.prim->urm=NULL;
    w.ultim=w.prim;
    w.p=w.prim;
    y.p=y.prim;
    z.p=z.prim;
    for(int i=1;i<=w.m;i++)
        for(int j=1;j<=w.n;j++) {w.p->Flavia.val=y.p->Flavia.val+z.p->Flavia.val;
                                 w.p->urm=new mcomplex<T>::matr;
                                 w.p=w.p->urm;
                                 y.p=y.p->urm;
                                 z.p=z.p->urm;}
    return w;
}
template<class T>
mcomplex<T> mcomplex<T>::operator*(mcomplex<T> z)
{
    mcomplex<T> y=*this;
    if(y.n!=z.m) {cout<<"NU SE POATE EFECTUA, MATRICEA URMATOARE NU ESTE COMPATIBILA:"; return y;}
    mcomplex<T> w;
    w.m=y.m;
    w.n=z.n;
    w.prim=new mcomplex<T>::matr;
    w.p=w.prim;
    w.prim->urm=NULL;
    w.ultim=w.prim;
    for(int k=1;k<=w.m;k++)
    for(int kk=1;kk<=w.n;kk++) {y.p=y.prim;
    for(int o=1;o<=y.n;o++) {z.p=z.prim;
                             while(y.p->Flavia.l!=k) y.p=y.p->urm;
                             while(z.p->Flavia.l!=o || z.p->Flavia.c!=kk) z.p=z.p->urm;
                             w.p->Flavia.val=w.p->Flavia.val+y.p->Flavia.val*z.p->Flavia.val;
                             y.p=y.p->urm;}
                             w.p->urm=new mcomplex<T>::matr;w.p=w.p->urm;}
    return w;
}

template<class T>
mcomplex<T> mcomplex<T>::stelat()
{
    mcomplex<T> y=*this;
    mcomplex<T> w,x,z;
    w.m=y.m; //w=transpusa
    w.n=y.m;
    w.prim=new mcomplex<T>::matr;
    w.p=w.prim;
    for(int i=2;i<=y.m*y.m;i++) {w.p->urm=new mcomplex<T>::matr;
                                 w.p=w.p->urm;}
    w.ultim=w.p;
    w.p=w.prim;
    for(int i=1;i<=y.m;i++) for(int j=1;j<=y.m;j++) {y.p=y.prim;
                                                     while(y.p->Flavia.l!=j || y.p->Flavia.c!=i) y.p=y.p->urm;
                                                     w.p->Flavia.val=y.p->Flavia.val;
                                                     w.p->Flavia.l=i;
                                                     w.p->Flavia.c=j;
                                                     if(w.p->urm!=0) w.p=w.p->urm;}
    x.m=x.n=w.m-1; //x=submatricea
    z.m=z.n=w.m; //z=matricea*
    x.prim=new mcomplex<T>::matr;
    x.p=x.prim;
    z.prim=new mcomplex<T>::matr;
    z.p=z.prim;
    for(int i=2;i<=z.m*z.m;i++) {z.p->urm=new mcomplex<T>::matr;
                                 z.p=z.p->urm;}
    for(int i=2;i<=x.m*x.m;i++) {x.p->urm=new mcomplex<T>::matr;
                                 x.p=x.p->urm;}
    z.p=z.prim;
    for(int j=1;j<=w.m;j++)
     for(int qwe=1;qwe<=w.m;qwe++)
     {x.p=x.prim; int nl=1,nc=1; w.p=w.prim;
      for(int i=1;i<=x.m*x.m;i++)
      {while(w.p->Flavia.l==j || w.p->Flavia.c==qwe) w.p=w.p->urm;
       x.p->Flavia.val=w.p->Flavia.val; x.p->Flavia.l=nl; x.p->Flavia.c=nc;
       nc++;
       if(nc>x.m) {nc=1; nl++;}
       if(x.p->urm!=NULL) x.p=x.p->urm;
       w.p=w.p->urm;}
     x.ultim=x.p;
     if((j+qwe)%2==0) z.p->Flavia.val=x.det();
     else {nrcomplex<T> ar,are=ar-x.det();
           z.p->Flavia.val=are;}
     z.p->Flavia.l=j; z.p->Flavia.c=qwe;
     z.p=z.p->urm;}
    return z;
}
template<class T>
nrcomplex<T> nrcomplex<T>::operator+(nrcomplex<T> b)
{
    nrcomplex<T> n;
    n.re=re+b.re;
    n.im=im+b.im;
    return n;
}
template<class T>
nrcomplex<T> nrcomplex<T>::operator-(nrcomplex<T> b)
{
    nrcomplex<T> n;
    n.re=re-b.re;
    n.im=im-b.im;
    return n;
}
template<class T>
nrcomplex<T> nrcomplex<T>::operator*(nrcomplex<T> b)
{
    nrcomplex<T> n;
    n.re=re*b.re-im*b.im;
    n.im=re*b.im+im*b.re;
    return n;
}
template<class T>
int nrcomplex<T>::operator!=(nrcomplex<T> b)
{
    if(re==b.re && im==b.im) return 0;
    else return 1;
}
template<class T>
bool nrcomplex<T>::egalcuzero()
{
    if(re==0 && im==0) return true;
    else return false;
}
template<class T>
istream& operator>>(istream& in,nrcomplex<T>& n)
{
    in>>n.re>>n.im;
    return in;
}
template<class T>
ifstream& operator>>(ifstream& in,nrcomplex<T>& n)
{
    in>>n.re>>n.im;
    return in;
}
template<class T>
istream& operator>>(istream& in,mcomplex<T>& z)
{
    cout<<"\nNumar de linii:\n";
    in>>z.m;
    cout<<"\nNumar de coloane:\n";
    in>>z.n;
    z.prim=new typename mcomplex<T>::matr;
    cout<<"\nElementul de pe linia 1 si coloana 1:\n";
    in>>z.prim->Flavia.val;
    z.prim->Flavia.l=1;z.prim->Flavia.c=1;
    z.prim->urm=NULL;
    z.ultim=z.prim;
    for(int i=1;i<=z.m;i++)
    for(int j=1;j<=z.n;j++) {if(i==1 && j==1) j++;
                             z.p=new typename mcomplex<T>::matr;
                             cout<<"\nElementul de pe linia "<<i<<" si coloana "<<j<<":\n";
                             in>>z.p->Flavia.val;
                             z.p->Flavia.l=i;z.p->Flavia.c=j;
                             z.ultim->urm=z.p;
                             z.p->urm=NULL;
                             z.ultim=z.p;}
    return in;
}
template<class T>
ifstream& operator>>(ifstream& in,mcomplex<T>& z)
{
    in>>z.m;
    in>>z.n;
    z.prim=new typename mcomplex<T>::matr;
    in>>z.prim->Flavia.val;
    z.prim->Flavia.l=1;z.prim->Flavia.c=1;
    z.prim->urm=NULL;
    z.ultim=z.prim;
    for(int i=1;i<=z.m;i++)
    for(int j=1;j<=z.n;j++) {if(i==1 && j==1) j++;
                             z.p=new typename mcomplex<T>::matr;
                             in>>z.p->Flavia.val;
                             z.p->Flavia.l=i;z.p->Flavia.c=j;
                             z.ultim->urm=z.p;
                             z.p->urm=NULL;
                             z.ultim=z.p;}
    return in;
}
template<class T>
ostream& operator<<(ostream& out,nrcomplex<T>& n)
{
    if(n.re==0 && n.im==0) out<<0;
    else if(n.re==0) if(n.im==1) out<<"i";
                     else out<<n.im<<"i";
    else if(n.im==0) out<<n.re;
    else if(n.im==1) out<<n.re<<"+i";
    else if(n.im==-1) out<<n.re<<"-i";
    else if(n.im<0) out<<n.re<<n.im<<"i";
    else out<<n.re<<"+"<<n.im<<"i";
    return out;
}
template<class T>
ostream& operator<<(ostream& out,mcomplex<T>& z)
{
    out<<'\n';
    z.p=z.prim;
    for(int i=1;i<=z.m;i++)
        {for(int j=1;j<=z.n;j++)
    {out<<z.p->Flavia.val;
     out<<"   ";
     z.p=z.p->urm;}
     out<<'\n';}
    return out;
}
int main()
{
    mpatr<double> a; mcomplex<double> c; mpatrtri<double> b; nrcomplex<double> d; int x;
    ifstream f("matrice.in");
    f>>a>>b;
    do{cout<<"\nAlegeti o optiune:\n1.Adunare\n2.Inmultire\n3.Determinant\n4.Inversa\n5.Diagonala\n6.Scalara\n0.Iesire\n";
       cin>>x;
       switch(x){
       case 1: {c=a+b; cout<<c; break;}
       case 2: {c=a*b; cout<<c; break;}
       case 3: {cout<<"\nCe determinant doriti sa calculati?\n"; int abc;
                cin>>abc;
                if(abc==0) break;
                else if(abc==1) d=a.det();
                else if(abc==2) d=b.det();
                else {cout<<"Nu exista acea matrice"; break;}
                cout<<d;
                break;}
       case 4: {cout<<"\nCe inversa doriti sa calculati?\n"; int abc;
                cin>>abc;
                if(abc==0) break;
                else if(abc==1) {c=a.stelat(); d=a.det();}
                else if(abc==2) {c=b.stelat(); d=b.det();}
                else {cout<<"Nu exista acea matrice"; break;}
                if(!d.egalcuzero()) {cout<<"1/("; cout<<d; cout<<")  *\n("; cout<<c; cout<<")";}
                break;}
       case 5: {b.diagonala(); break;}
       case 6: {b.scalara(); break;}
       case 0: break;};
       } while(x!=0);
    return 0;
}
