//utility.h

namespace util
{
    void rotationMatrix(double angle[3],double rotMatrix[3][3]);
    void  rotate(double r[3],double rotMatrix[3][3]);
    void  inverse(double matrix[3][3],double inverseMatrix[3][3]);
    void dsyev(double matrix[3][3],double eigenVectors[3][3],
	       double eigenValues[3]);
    void dgemm(double a[3][3], double b[3][3],double c[3][3]);
    void dgemv(double a[3][3],double v1[3],double v2[3]);
    void transpose(double a[3][3],double b[3][3]);
    void mcopy(double a[3][3],double b[3][3]);
    void vcopy(double* v1,double* v2,int n=3);
    double mode(double* v,int n=3);
    double distance(double* v1,double *v2,int n=3);
    void a2DTo1D(double a[3][3],double b[9]);
    void a1DTo2D(double a[9],double b[3][3]);
    void vout(double* a,int n);
    void mout(double a[3][3]);
    double toDegree(double angle);
    double toArc(double angle);
    void normalVector(double a[3],double b[3], double n[3]);
    void rotateMatrix(double n[3], double angle,
			double rotMatrix[3][3]);
    void vecProd(double a[3],double b[3],double n[3]);
    double dotProd(double *a,double *b,int n=3);
    void scalemv(double a, double *b,double *c,int n=3);
    void normalize(double a[3]); 
    double angle(double a[3],double b[3]);
    void changeAngle1(double a[3],double b[3],double alpha,double ap[3]);
    void vminusv(double a[3],double b[3],double c[3],int n=3);
    void vplusv(double a[3],double b[3],double c[3],int n=3);
    void eularAngles(double x[3],double y[3],double z[3],double angle[3]);
}



































































