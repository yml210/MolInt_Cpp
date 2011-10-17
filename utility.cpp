//utility.cpp
#include <math.h>
#include "utility.h"
#include <f2c.h>
#include <iostream>
using namespace std;
extern "C" {
  int dgesv_(int* n,int* nrhs, double* matrix,int *lda,
	     int* ipiv,double* invmatrix, int *ldb, int* info);
  int dgemm_(char* transa,char* transb,int* n,int* m,int* k,double* alpha,
	     double* a,int* lda,double* b,int* ldb,double* belta,
	     double* c, int* ldc);
  int dsyev_(char* job,char* uplo,int* n,double* a,int* lda,double* w,
	     double* work,int* lwork,int* info);
}

void util::rotationMatrix(double angle[3],double matrix[3][3])
{
    matrix[0][0]=cos(angle[0])*cos(angle[1])*cos(angle[2])
        -sin(angle[0])*sin(angle[2]);

    matrix[0][1]=sin(angle[0])*cos(angle[1])*cos(angle[2])
        +cos(angle[0])*sin(angle[2]);

    matrix[0][1]=-sin(angle[1])*cos(angle[2]);

    matrix[1][0]=-cos(angle[0])*cos(angle[1])*sin(angle[2])
        -sin(angle[0])*cos(angle[2]);

    matrix[1][1]=-sin(angle[0])*cos(angle[1])*sin(angle[2])
        +cos(angle[0])*cos(angle[2]);

    matrix[1][2]=sin(angle[1])*sin(angle[2]);

    matrix[2][0]=cos(angle[0])*sin(angle[1]);

    matrix[2][1]=sin(angle[0])*sin(angle[1]);

    matrix[2][2]=cos(angle[1]);
    
}

void util::rotate(double r[3], double rotMatrix[3][3])
{
    double tmp[3]={0.0,0.0,0.0};
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            tmp[i]+=rotMatrix[i][j]*r[j];
        }
    }

    for(int i=0;i<3;i++){
        r[i]=tmp[i];
    }
}

void util::inverse(double matrix[3][3], double inverseMatrix[3][3])
{
  double tmp1[9];
  double tmp2[9]={
    1.0,0.0,0.0,
    0.0,1.0,0.0,
    0.0,0.0,1.0
  };

  a2DTo1D(matrix,tmp1);

  int info=0;
  int n=3;
  int ipiv[3];

  dgesv_(&n,&n,tmp1,&n,ipiv,tmp2,&n, &info);
  if(info!=0){
    cerr<<"util::inverse: failed!"<<endl
	<<"info= "<<info<<endl;
  }

  a1DTo2D(tmp2,inverseMatrix);

}

void util::dgemv(double a[3][3],double v1[3],double v2[3])
{
  for(int i=0;i<3;i++){
    v2[i]=0.0;
    for(int j=0;j<3;j++){
      v2[i]+=a[i][j]*v1[j];
    }
  }
}
void util::dgemm(double a[3][3],double b[3][3],double c[3][3])
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      c[i][j]=0.0;
      for(int k=0;k<3;k++){
	c[i][j]+=a[i][k]*b[k][j];
      }
    }
  }
}

/*
void util::dgemm(double a[3][3],double b[3][3],double c[3][3])
{
  char trans='N';
  double scalar1=1.0;
  double scalar2=0.0;
  int n=3;

  double tmp1[9],tmp2[9],tmp3[9];
  a2DTo1D(a,tmp1);
  a2DTo1D(b,tmp2);
  dgemm_(&trans,&trans,&n,&n,&n,&scalar1,tmp1,
	 &n,tmp2,&n,&scalar2,tmp3,&n); 
  //  dgemm_(&trans,&trans,&n,&n,&n,&scalar1,&a[0][0],
  // &n,&b[0][0],&n,&scalar2,&c[0][0],&n);
  
  a1DTo2D(tmp3,c);
}
*/

void util::transpose(double a[3][3],double b[3][3])
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      b[i][j]=a[j][i];
    }
  }
}

void util::mcopy(double a[3][3],double b[3][3])
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      b[i][j]=a[i][j];
    }
  }
}
void util::vcopy(double* a,double* b,int n)
{
	for(int i=0;i<n;i++){
	   b[i]=a[i];
	}
}
		

double util::mode(double* v,int n)
{
  double tmp=0.0;
  for(int i=0;i<n;i++){
    tmp+=v[i]*v[i];
  }
  return sqrt(tmp);
}

double util::distance(double* v1,double* v2,int n)
{
   double tmp=0.0;
   for(int i=0;i<n;i++){
	tmp+=(v1[i]-v2[i])*(v1[i]-v2[i]);
   }
   return sqrt(tmp);
} 
  
void util::a2DTo1D(double a[3][3],double b[9])
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      b[i+j*3]=a[i][j];
    }
  }
}

void util::a1DTo2D(double a[9],double b[3][3])
{
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      b[i][j]=a[i+j*3];
    }
  }
}

void util::dsyev(double matrix[3][3],double eigenVectors[3][3],
		 double eigenValues[3])
{
  double tmp1[9],tmp2[9];
  double work[9];
  int n,lda,info,lwork;
  char job,uplo;
  
  job='V';
  uplo='U';
  lwork=9;
  n=3;
  info=3;
  lda=3;

  a2DTo1D(matrix,tmp1);
  
  dsyev_(&job,&uplo,&n,tmp1,&lda,eigenValues,work,&lwork,&info);
  
  if(info!=0){
    cerr<<"util::dsyev: failed!"<<endl
	<<"info= "<<info<<endl;
  }

  a1DTo2D(tmp1,eigenVectors);
}

void util::mout(double m[3][3]){
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      cout<<' '<<m[i][j];
    }
    cout<<endl;
  }
  cout<<endl;
}

void util::vout(double* v,int n)
{
  for(int i=0;i<n;i++){
    cout<<' '<<v[i];
  }
  cout<<endl<<endl;
}

double util::toDegree(double angle)
{
  double PI=acos(-1.0);
  return 180.0*angle/PI;
}

double util::toArc(double angle)
{
  double PI=acos(-1.0);
  return angle/180.0*PI;
}

void util::normalVector(double a[3],double b[3],double n[3])
{
  double r;
  vecProd(a,b,n);
  r=mode(n,3);
  if(r!=0.0){
    for(int i=0;i<3;i++){
      n[i]=n[i]/r;
    }
  }
  else
  {
    cerr<<"util::normalVector: r= "<<r<<endl;
  }
}

void util::rotateMatrix(double n[3],double angle,
			 double rotMatrix[3][3])
{
  rotMatrix[0][0]=cos(angle);
  rotMatrix[1][1]=rotMatrix[0][0];
  rotMatrix[2][2]=rotMatrix[0][0];
  rotMatrix[0][1]=-n[2]*sin(angle);
  rotMatrix[1][0]=-rotMatrix[0][1];
  rotMatrix[0][2]=n[1]*sin(angle);
  rotMatrix[2][0]=-rotMatrix[0][2];
  rotMatrix[1][2]=-n[0]*sin(angle);
  rotMatrix[2][1]=-rotMatrix[1][2];
}

void util::vecProd(double a[3],double b[3],double n[3])
{
  
  n[0]=a[1]*b[2]-a[2]*b[1];
  n[1]=a[2]*b[0]-a[0]*b[2];
  n[2]=a[0]*b[1]-a[1]*b[0];
}
  
void util::normalize(double a[3])
{
  double r=mode(a,3);
  if(r!=0.0){
    for(int i=0;i<3;i++){
      a[i]=a[i]/r;
    }
  }
  else
  {
    cerr<<"util::normalize: r= "<<r<<endl;
  }
}

double util::angle(double a[3],double b[3])
{
    double d1,d2,d3;

    d1=mode(a,3);
    d2=mode(b,3);
    d3=0.0;
    for(int i=0;i<3;i++)
    {
      d3=d3+(a[i]-b[i])*(a[i]-b[i]);
    }
    d3=sqrt(d3);
      
    if((d1==0)||(d2==0)){
        cerr<< "Atom::angle:"<<endl
            <<"d1= "<<d1<<endl
            <<"d2= "<<d2<<endl;
        return -1.0;
    }

    d3=acos((d1*d1+d2*d2-d3*d3)/(2.0*d1*d2));
    return d3;
}
 
void util::changeAngle1(double a[3],double b[3],double alpha,double ap[3])
{
  double n[3],np[3],tmp;
  vcopy(b,n,3);
  normalize(n);
  tmp=dotProd(n,a);
  scalemv(tmp,n,ap);
  vminusv(ap,a,np);
  normalize(np);
  tmp=mode(a,3);
  scalemv(tmp*cos(alpha),n,ap);
  vcopy(ap,n,3);
  scalemv(tmp*sin(alpha),np,ap);
  vcopy(ap,np,3);
  vplusv(n,np,ap);
}

void util::scalemv(double a,double b[3],double c[3],int n)
{
  for(int i=0;i<n;i++){
    c[i]=a*b[i];
  }
}
  
void util::vminusv(double a[3],double b[3],double c[3],int n)
{
  for(int i=0;i<n;i++){
    c[i]=b[i]-a[i];
  }
}
  
void util::vplusv(double a[3],double b[3],double c[3],int n)
{
  for(int i=0;i<n;i++){
    c[i]=b[i]+a[i];
  }
}

void util::eularAngles(double x[3],double y[3],double z[3],double angles[3])
{
  double xx[]={1.0,0.0,0.0};
  double zz[]={0.0,0.0,1.0};
  double tmp1[3],tmp2[3],tmp;

  angles[1]=angle(z,zz);

  vecProd(zz,z,tmp1);
  vecProd(tmp1,z,tmp2);
  tmp =dotProd(y,tmp2,3);
  angles[2]=(tmp<0.0)? 360.0-angle(tmp1,y):angle(tmp1,y);

  vecProd(tmp1,zz,tmp2);
  angles[0]=(tmp2[1]<0.0)? 360.0-angle(tmp2,xx):angle(tmp2,xx);
}

double util::dotProd(double *a,double *b,int n)
{
  double tmp=0;
  for(int i=0;i<n;i++){
    tmp+=a[i]*b[i];
  }
  return tmp;
} 
/*---------------------------------------------------
test drive

void main(){

  double im[3][3],m1[3][3],ev[3][3],e[3];
  double m[3][3]={
    {1.0,4.5,6.2},
    {4.5,2.5,2.2},
    {6.2,2.2,1.8}
  };

  mout(m);

  util::dsyev(m,ev,e);
  mout(ev);

  util::dgemm(m,ev,m1);
  mout(m1);
  vout(e);

  util::transpose(ev,im);
  util::dgemm(im,ev,m1);
  mout(m1);

  util::inverse(m,im);
  mout(im);

  util::dgemm(m,im,m1); 
  mout(m1);
}
*/











