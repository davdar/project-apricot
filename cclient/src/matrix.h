#ifndef MATRIX_H
#define MATRIX_H	

#include <cmath>
#include <iostream>

#include "types.h"
#include "vector.h"

/*
	A stateless parent class for matrix subclasses to 
	inherit common attributes
*/
class Matrix {
public:
	enum Order {ROW_ORDER, COLUMN_ORDER};
};

class Matrix2x2;
class Matrix3x3;
class Matrix4x4;

/*
    2x2 Matrix Class Definition
*/
class Matrix2x2 : public Matrix {
private:
    /* Internal data is always stored in row-major order */
    Real data[2][2];

    /*Convenience accessors into internal data (easier than () operator inside member functions) */
    Real &cell(int row, int col);
    Real cell(int row, int col) const;

public:
    Matrix2x2();
    Matrix2x2(const Matrix2x2 &m);
    Matrix2x2(const Matrix3x3 &m);
    Matrix2x2(const Matrix4x4 &m);
    Matrix2x2(Real v11, Real v12, Real v21, Real v22);
    Matrix2x2(const Vector2 &v1, const Vector2 &v2, Order order=COLUMN_ORDER);

    Real &operator() (int row, int col);
    Real operator() (int row, int col) const;

    Matrix2x2 operator* (const Matrix2x2 &m) const;
    Vector2 operator* (const Vector2 &vec) const;

    Matrix2x2 transpose() const;
    Matrix2x2 inverse() const;

    void getEigenvalues(Real *lambda1RealPart, Real *lambda1IPart, Real *lambda2RealPart, Real *lambda2IPart) const;
};

Real determinant(const Matrix2x2 &m);

/*
	3x3 Matrix Class Definition
*/
class Matrix3x3 : public Matrix {
private:
	/* Internal data is always stored in row-major order */
	Real data[3][3];

	/* Convenience accessors into internal data (easier than () operater inside member functions) */
	Real &cell(int row, int col);
	Real cell(int row, int col) const;

public:
	Matrix3x3();
	Matrix3x3(const Matrix3x3 &m);
	Matrix3x3(const Matrix4x4 &m);
	Matrix3x3(Real v11, Real v12, Real v13,
				Real v21, Real v22, Real v23,
				Real v31, Real v32, Real v33);
	Matrix3x3(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Order order=COLUMN_ORDER);
	Matrix3x3(const Vector3 v1[3], Order order=COLUMN_ORDER);
	
	Real &operator() (int row, int col);
	Real operator() (int row, int col) const;

	
	Matrix3x3 operator* (const Matrix3x3 &m) const;
	Vector3 operator* (const Vector3 &v) const;

	Matrix3x3 transpose() const;
	Matrix3x3 inverse() const;

	void load(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Order order=COLUMN_ORDER);
	void load(const Real mat[9], Order order=ROW_ORDER);
	void dump(Real mat[9], Order order=ROW_ORDER) const;
};

/*
	Additional Matrix3x3 functions
*/
Real determinant(const Matrix3x3 &m);

#ifndef EPSILON
#define EPSILON (1.0e-8)
#endif

inline Matrix3x3 getRotationAroundAxis(const Vector3 &axis, double theta){
	Vector3 r = axis;
	normalize(r);
	double ct = cos(theta);
	double st = sin(theta);

	double m00 = 1-(1-ct)*(r[1]*r[1]+r[2]*r[2]);
	double m01 = (1-ct)*r[0]*r[1]-st*r[2];
	double m02 = (1-ct)*r[0]*r[2]+st*r[1];
	double m10 = (1-ct)*r[0]*r[1]+st*r[2];
	double m11 = 1-(1-ct)*(r[0]*r[0]+r[2]*r[2]);
	double m12 = (1-ct)*r[1]*r[2]-st*r[0];
	double m20 = (1-ct)*r[0]*r[2]-st*r[1];
	double m21 = (1-ct)*r[1]*r[2]+st*r[0];
	double m22 = 1-(1-ct)*(r[0]*r[0]+r[1]*r[1]);
	return Matrix3x3(	m00, m01, m02,
						m10, m11, m12,
						m20, m21, m22 );
}

inline Matrix3x3 getRotationBetweenVectors(const Vector3 &fromVector, const Vector3 &toVector){
	Vector3 normFromVector(fromVector);
	normalize(normFromVector);

	Vector3 normToVector(toVector);
	normalize(normToVector);

	Real cosTheta = dot(normFromVector, normToVector);

	if(cosTheta >= 1-EPSILON){
		return Matrix3x3();
	} else {
		Vector3 rotationAxis;
		if(cosTheta <= -1 + EPSILON){
			rotationAxis = cross(fromVector, Vector3(0.0, 1.0, 0.0));
			if(magnitudeSqr(rotationAxis) <= EPSILON){
				//let's hope it doesn't come to this
				rotationAxis = cross(fromVector, Vector3(0.0, 0.0, 1.0));
			}
		} else {
			rotationAxis = cross(fromVector, toVector);
		}
		normalize(rotationAxis);

		Real rx = rotationAxis[0];
		Real ry = rotationAxis[1];
		Real rz = rotationAxis[2];

		Real rxSqr = rx*rx;
		Real rySqr = ry*ry;
		Real rzSqr = rz*rz;

		Real cosThetaSqr = cosTheta*cosTheta;
		Real oneMinusCosTheta = 1 - cosTheta;

		Real sinTheta = sqrt(1 - cosThetaSqr);

		Real m00 = 1 - oneMinusCosTheta*(rySqr + rzSqr);
		Real m01 = oneMinusCosTheta*rx*ry - sinTheta*rz;
		Real m02 = oneMinusCosTheta*rx*rz + sinTheta*ry;
		Real m10 = oneMinusCosTheta*rx*ry + sinTheta*rz;
		Real m11 = 1 - oneMinusCosTheta*(rxSqr + rzSqr);
		Real m12 = oneMinusCosTheta*ry*rz - sinTheta*rx;
		Real m20 = oneMinusCosTheta*rx*rz - sinTheta*ry;
		Real m21 = oneMinusCosTheta*ry*rz + sinTheta*rx;
		Real m22 = 1 - oneMinusCosTheta*(rxSqr + rySqr);

		return Matrix3x3(m00, m01, m02, m10, m11, m12, m20, m21, m22);
	}
}

#undef EPSILON

/*
	4x4 Matrix Class definition
*/
class Matrix4x4 : public Matrix {
private:
	/* Internal data is always stored in row-major order */
	Real data[4][4];

	/* Convenience accessors into internal data (easier than () operater inside member functions) */
	Real &cell(int row, int col);
	Real cell(int row, int col) const;

public:
	Matrix4x4();
	Matrix4x4(const Matrix4x4 &m);
	Matrix4x4(const Matrix3x3 &m);
	Matrix4x4(	Real v11, Real v12, Real v13, Real v14,
				Real v21, Real v22, Real v23, Real v24,
				Real v31, Real v32, Real v33, Real v34,
				Real v41, Real v42, Real v43, Real v44 );
	Matrix4x4(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3, const Vector4 &v4, Order order=COLUMN_ORDER);
	Matrix4x4(const Vector4 v[4], Order order=COLUMN_ORDER);

	Real &operator() (int row, int col);
	Real operator() (int row, int col) const;

	Matrix4x4 operator* (const Matrix4x4 &m) const;
	Vector4 operator* (const Vector4 &v) const;

	Matrix4x4 transpose() const;

	void load(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3, const Vector4 &v4, Order order=COLUMN_ORDER);
	void load(const Real mat[16], Order order=ROW_ORDER);
	void dump(Real mat[16], Order order=ROW_ORDER) const;
};

/*
	Additional Matrix4x4 functions
*/
Real determinant(const Matrix4x4 &m);

/*
|
| Some constant definitions
|
*/
static const Matrix2x2 Ideniity2x2 = Matrix2x2();
static const Matrix3x3 Identity3x3 = Matrix3x3();
static const Matrix4x4 Identity4x4 = Matrix4x4();

/*
|---------------------------
|
|	Function Definitions
|
|---------------------------
*/

/*
    Private Matrix2x2 member functions
*/
inline Real &Matrix2x2::cell(int row, int col){
    return data[row][col];
}

inline Real Matrix2x2::cell(int row, int col) const {
    return data[row][col];
}

/*
    Matrix2x2 Member Function Definitions
*/
inline Matrix2x2::Matrix2x2(){
    cell(0,0) = 1.0;
    cell(0,1) = 0.0;
    cell(1,0) = 0.0;
    cell(1,1) = 1.0;
}

inline Matrix2x2::Matrix2x2(const Matrix2x2 &m){
    cell(0,0) = m(0,0);
    cell(0,1) = m(0,1);
    cell(1,0) = m(1,0);
    cell(1,1) = m(1,1);
}

inline Matrix2x2::Matrix2x2(const Matrix3x3 &m){
    cell(0,0) = m(0,0);
    cell(0,1) = m(0,1);
    cell(1,0) = m(1,0);
    cell(1,1) = m(1,1);
}

inline Matrix2x2::Matrix2x2(const Matrix4x4 &m){
    cell(0,0) = m(0,0);
    cell(0,1) = m(0,1);
    cell(1,0) = m(1,0);
    cell(1,1) = m(1,1);
}

inline Matrix2x2::Matrix2x2(Real v11, Real v12, Real v21, Real v22){
    cell(0,0) = v11;
    cell(0,1) = v12;
    cell(1,0) = v21;
    cell(1,1) = v22;
}

inline Matrix2x2::Matrix2x2(const Vector2 &v1, const Vector2 &v2, Order order){
    switch(order){
    case ROW_ORDER:
        cell(0,0) = v1[0];
        cell(0,1) = v1[1];
        cell(1,0) = v2[0];
        cell(1,1) = v2[1];
    case COLUMN_ORDER:
        cell(0,0) = v1[0];
        cell(0,1) = v2[0];
        cell(1,0) = v1[1];
        cell(1,1) = v2[1];
    }
}

inline Real &Matrix2x2::operator() (int row, int col){
    return data[row][col];
}

inline Real Matrix2x2::operator() (int row, int col) const {
    return data[row][col];
}

inline Matrix2x2 Matrix2x2::operator* (const Matrix2x2 &m) const {
    return Matrix2x2(cell(0,0)*m(0,0) + cell(0,1)*m(1,0), cell(0,0)*m(0,1) + cell(0,1)*m(1,1),
                     cell(1,0)*m(0,0) + cell(1,1)*m(1,0), cell(1,0)*m(0,1) + cell(1,1)*m(1,1));
}

inline Vector2 Matrix2x2::operator* (const Vector2 &vec) const {
    return Vector2(cell(0,0)*vec[0] + cell(0,1)*vec[1],
                    cell(1,0)*vec[0] + cell(1,1)*vec[1]);
}

inline Matrix2x2 Matrix2x2::transpose() const {
    return Matrix2x2(cell(0,0), cell(1,0),
                     cell(0,1), cell(1,1));
}

inline Matrix2x2 Matrix2x2::inverse() const {
    Real det = determinant(*this);
    if(det != 0.0){
        Real detInv = 1.0/det;
        return Matrix2x2(cell(1,1)*detInv, -cell(1,0)*detInv,
                         -cell(0,1)*detInv, cell(0,0)*detInv);
    } else {
        std::cout << "Warning: tried to invert a singular matrix" << std::endl;
        return Matrix2x2();
    }
}

inline void Matrix2x2::getEigenvalues(Real *lambda1RealPart, Real *lambda1IPart, Real *lambda2RealPart, Real *lambda2IPart) const {
    //quadratic formula variables
    Real b = -(cell(0,0) + cell(1,1));
    Real c = cell(0,0)*cell(1,1) - cell(0,1)*cell(1,0);

    Real desc = b*b - 4*c;
    if(desc < 0){
        *lambda1RealPart = -b*0.5;
        *lambda1IPart = sqrt(-desc)*0.5;
        *lambda2RealPart = -b*0.5;
        *lambda2IPart = -sqrt(-desc)*0.5;
    } else {
        *lambda1RealPart = (-b + sqrt(desc))*0.5;
        *lambda1IPart = 0.0;
        *lambda2RealPart = (-b - sqrt(desc))*0.5;
        *lambda2IPart = 0.0;
    }
}

/*
    Additional Matrix2x2 functions
*/
inline Real determinant(const Matrix2x2 &m){
    return m(0,0)*m(1,1) - m(0,1)*m(1,0);
}

/*
	Private Matrix3x3 member functions
*/
inline Real &Matrix3x3::cell(int row, int col){
	return data[row][col];
}

inline Real Matrix3x3::cell(int row, int col) const {
	return data[row][col];
}

/*
	Matrix3x3 member function definitions
*/
inline Matrix3x3::Matrix3x3(){
	data[0][0] = 1;
	data[0][1] = 0; 
	data[0][2] = 0;
	data[1][0] = 0;
	data[1][1] = 1;
	data[1][2] = 0;
	data[2][0] = 0;
	data[2][1] = 0;
	data[2][2] = 1;
}

inline Matrix3x3::Matrix3x3(const Matrix3x3 &m){
	data[0][0] = m.data[0][0];
	data[0][1] = m.data[0][1];
	data[0][2] = m.data[0][2];
	data[1][0] = m.data[1][0];
	data[1][1] = m.data[1][1];
	data[1][2] = m.data[1][2];
	data[2][0] = m.data[2][0];
	data[2][1] = m.data[2][1];
	data[2][2] = m.data[2][2];
}

inline Matrix3x3::Matrix3x3(const Matrix4x4 &m){
	for(int row = 0; row < 3; row++){
		for(int col = 0; col < 3; col++){
			cell(row,col) = m(row,col);
		}
	}
}

inline Matrix3x3::Matrix3x3(Real v11, Real v12, Real v13,
							Real v21, Real v22, Real v23,
							Real v31, Real v32, Real v33){
		data[0][0] = v11;
		data[0][1] = v12;
		data[0][2] = v13;
		data[1][0] = v21;
		data[1][1] = v22;
		data[1][2] = v23;
		data[2][0] = v31;
		data[2][1] = v32;
		data[2][2] = v33;
}

inline Matrix3x3::Matrix3x3(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Order order){
	load(v1,v2,v3,order);
}

inline Matrix3x3::Matrix3x3(const Vector3 v[3], Order order){
	load(v[0], v[1], v[2], order);
}

inline Real &Matrix3x3::operator() (int row, int col){
	return data[row][col];
}

inline Real Matrix3x3::operator() (int row, int col) const {
	return data[row][col];
}

inline Matrix3x3 Matrix3x3::operator* (const Matrix3x3 &m) const {
	Real v11 = data[0][0]*m.data[0][0] + data[0][1]*m.data[1][0] + data[0][2]*m.data[2][0];
	Real v12 = data[0][0]*m.data[0][1] + data[0][1]*m.data[1][1] + data[0][2]*m.data[2][1];
	Real v13 = data[0][0]*m.data[0][2] + data[0][1]*m.data[1][2] + data[0][2]*m.data[2][2];
	Real v21 = data[1][0]*m.data[0][0] + data[1][1]*m.data[1][0] + data[1][2]*m.data[2][0];
	Real v22 = data[1][0]*m.data[0][1] + data[1][1]*m.data[1][1] + data[1][2]*m.data[2][1];
	Real v23 = data[1][0]*m.data[0][2] + data[1][1]*m.data[1][2] + data[1][2]*m.data[2][2];
	Real v31 = data[2][0]*m.data[0][0] + data[2][1]*m.data[1][0] + data[2][2]*m.data[2][0];
	Real v32 = data[2][0]*m.data[0][1] + data[2][1]*m.data[1][1] + data[2][2]*m.data[2][1];
	Real v33 = data[2][0]*m.data[0][2] + data[2][1]*m.data[1][2] + data[2][2]*m.data[2][2];
	return Matrix3x3(v11, v12, v13,
					v21, v22, v23,
					v31, v32, v33);
}

inline Vector3 Matrix3x3::operator* (const Vector3 &v) const {
	Real v1 = data[0][0]*v[0] + data[0][1]*v[1] + data[0][2]*v[2];
	Real v2 = data[1][0]*v[0] + data[1][1]*v[1] + data[1][2]*v[2];
	Real v3 = data[2][0]*v[0] + data[2][1]*v[1] + data[2][2]*v[2];
	return Vector3(v1, v2, v3);
}

inline Matrix3x3 Matrix3x3::transpose() const{
	return Matrix3x3(	cell(0,0),	cell(1,0),	cell(2,0),
						cell(0,1),	cell(1,1),	cell(2,1),
						cell(0,2),	cell(1,2),	cell(2,2) );
}

inline Matrix3x3 Matrix3x3::inverse() const{
	Real d = determinant((*this));
	return Matrix3x3(	(cell(1,1)+cell(2,2)-cell(1,2)-cell(2,1))/d,	
						-(cell(0,1)+cell(2,2)-cell(0,2)-cell(2,1))/d,
						(cell(0,1)+cell(1,2)-cell(0,2)-cell(1,1))/d,

						-(cell(1,0)+cell(2,2)-cell(1,2)-cell(2,0))/d,
						(cell(0,0)+cell(2,2)-cell(0,2)-cell(2,0))/d,
						-(cell(0,0)+cell(1,2)-cell(0,2)-cell(1,0))/d,

						(cell(1,0)+cell(2,1)-cell(1,1)-cell(2,0))/d,
						-(cell(0,0)+cell(1,2)-cell(0,2)-cell(1,0))/d,
						(cell(0,0)+cell(1,1)-cell(0,1)-cell(1,0))/d );
}

inline void Matrix3x3::load(const Vector3 &v1, const Vector3 &v2, const Vector3 &v3, Order order){
	switch(order){
	case ROW_ORDER:
		data[0][0] = v1[0];
		data[0][1] = v1[1];
		data[0][2] = v1[2];
		data[1][0] = v2[0];
		data[1][1] = v2[1];
		data[1][2] = v2[2];
		data[2][0] = v3[0];
		data[2][1] = v3[1];
		data[2][2] = v3[2];
		break;
	case COLUMN_ORDER:
		data[0][0] = v1[0];
		data[0][1] = v2[0];
		data[0][2] = v3[0];
		data[1][0] = v1[1];
		data[1][1] = v2[1];
		data[1][2] = v3[1];
		data[2][0] = v1[2];
		data[2][1] = v2[2];
		data[2][2] = v3[2];
		break;
	}
}

inline void Matrix3x3::load(const Real mat[9], Order order){
	switch(order){
	case ROW_ORDER:
		data[0][0] = mat[0];	data[0][1] = mat[1];	data[0][2] = mat[2];
		data[1][0] = mat[3];	data[1][1] = mat[4];	data[1][2] = mat[5];
		data[2][0] = mat[6];	data[2][1] = mat[7];	data[2][2] = mat[8];
		break;
	case COLUMN_ORDER:
		data[0][0] = mat[0];	data[0][1] = mat[3];	data[0][2] = mat[6];
		data[1][0] = mat[1];	data[1][1] = mat[4];	data[1][2] = mat[7];
		data[2][0] = mat[2];	data[2][1] = mat[5];	data[2][2] = mat[8];
		break;
	}
}

inline void Matrix3x3::dump(Real mat[9], Order order) const{
	switch(order){
	case ROW_ORDER:
		mat[0] = data[0][0];	mat[1] = data[0][1];	mat[2] = data[0][2];
		mat[3] = data[1][0];	mat[4] = data[1][1];	mat[5] = data[1][2];
		mat[6] = data[2][0];	mat[7] = data[2][1];	mat[8] = data[2][2];
		break;
	case COLUMN_ORDER:
		mat[0] = data[0][0];	mat[3] = data[0][1];	mat[6] = data[0][2];
		mat[1] = data[1][0];	mat[4] = data[1][1];	mat[7] = data[1][2];
		mat[2] = data[2][0];	mat[5] = data[2][1];	mat[8] = data[2][2];
		break;
	}
}

/*
	Additional Matrix3x3 function definitions
*/
inline Real determinant(const Matrix3x3 &m){
	return m(0,0)*m(1,1)*m(2,2) + m(0,1)*m(1,2)*m(2,0) + m(0,2)*m(1,0)*m(2,1)
			- m(0,0)*m(1,2)*m(2,1) - m(0,1)*m(1,0)*m(2,2) - m(0,2)*m(1,1)*m(2,0);
}

/*
	Private Matrix4x4 member functions
*/

inline Real &Matrix4x4::cell(int row, int col){
	return data[row][col];
}

inline Real Matrix4x4::cell(int row, int col) const{
	return data[row][col];
}

/*
	Matrix4x4 member function definitions
*/
inline Matrix4x4::Matrix4x4(){
	cell(0,0)=1;	cell(0,1)=0;	cell(0,2)=0;	cell(0,3)=0;
	cell(1,0)=0;	cell(1,1)=1;	cell(1,2)=0;	cell(1,3)=0;
	cell(2,0)=0;	cell(2,1)=0;	cell(2,2)=1;	cell(2,3)=0;
	cell(3,0)=0;	cell(3,1)=0;	cell(3,2)=0;	cell(3,3)=1;
}

inline Matrix4x4::Matrix4x4(const Matrix4x4 &m){
	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			cell(row,col) = m(row,col);
		}
	}
}

inline Matrix4x4::Matrix4x4(const Matrix3x3 &m){
	for(int row = 0; row < 3; row++){
		for(int col = 0; col < 3; col++){
			cell(row,col) = m(row,col);
		}
		cell(row,3) = 0;
	}
	cell(3,0) = cell(3,1) = cell(3,2) = 0;
	cell(3,3) = 1;
}

inline Matrix4x4::Matrix4x4(Real v11, Real v12, Real v13, Real v14,
							Real v21, Real v22, Real v23, Real v24,
							Real v31, Real v32, Real v33, Real v34,
							Real v41, Real v42, Real v43, Real v44){

	cell(0,0)=v11;  cell(0,1)=v12;  cell(0,2)=v13;  cell(0,3)=v14;
	cell(1,0)=v21;  cell(1,1)=v22;  cell(1,2)=v23;  cell(1,3)=v24;
	cell(2,0)=v31;  cell(2,1)=v32;  cell(2,2)=v33;  cell(2,3)=v34;
	cell(3,0)=v41;  cell(3,1)=v42;  cell(3,2)=v43;  cell(3,3)=v44;
}

inline Matrix4x4::Matrix4x4(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3, const Vector4 &v4, Order order){
	load(v1,v2,v3,v4,order);
}

inline Matrix4x4::Matrix4x4(const Vector4 v[4], Order order){
	load(v[0], v[1], v[2], v[3], order);
}

inline Real &Matrix4x4::operator() (int row, int col){
	return data[row][col];
}

inline Real Matrix4x4::operator() (int row, int col) const{
	return data[row][col];
}

inline Matrix4x4 Matrix4x4::operator* (const Matrix4x4 &m) const{
	Matrix4x4 result = Matrix4x4();
	result(0,0) = cell(0,0)*m(0,0) + cell(0,1)*m(1,0) + cell(0,2)*m(2,0) + cell(0,3)*m(3,0);
	result(0,1) = cell(0,0)*m(0,1) + cell(0,1)*m(1,1) + cell(0,2)*m(2,1) + cell(0,3)*m(3,1);
	result(0,2) = cell(0,0)*m(0,2) + cell(0,1)*m(1,2) + cell(0,2)*m(2,2) + cell(0,3)*m(3,2);
	result(0,3) = cell(0,0)*m(0,3) + cell(0,1)*m(1,3) + cell(0,2)*m(2,3) + cell(0,3)*m(3,3);

	result(1,0) = cell(1,0)*m(0,0) + cell(1,1)*m(1,0) + cell(1,2)*m(2,0) + cell(1,3)*m(3,0);
	result(1,1) = cell(1,0)*m(0,1) + cell(1,1)*m(1,1) + cell(1,2)*m(2,1) + cell(1,3)*m(3,1);
	result(1,2) = cell(1,0)*m(0,2) + cell(1,1)*m(1,2) + cell(1,2)*m(2,2) + cell(1,3)*m(3,2);
	result(1,3) = cell(1,0)*m(0,3) + cell(1,1)*m(1,3) + cell(1,2)*m(2,3) + cell(1,3)*m(3,3);

	result(2,0) = cell(2,0)*m(0,0) + cell(2,1)*m(1,0) + cell(2,2)*m(2,0) + cell(2,3)*m(3,0);
	result(2,1) = cell(2,0)*m(0,1) + cell(2,1)*m(1,1) + cell(2,2)*m(2,1) + cell(2,3)*m(3,1);
	result(2,2) = cell(2,0)*m(0,2) + cell(2,1)*m(1,2) + cell(2,2)*m(2,2) + cell(2,3)*m(3,2);
	result(2,3) = cell(2,0)*m(0,3) + cell(2,1)*m(1,3) + cell(2,2)*m(2,3) + cell(2,3)*m(3,3);

	result(3,0) = cell(3,0)*m(0,0) + cell(3,1)*m(1,0) + cell(3,2)*m(2,0) + cell(3,3)*m(3,0);
	result(3,1) = cell(3,0)*m(0,1) + cell(3,1)*m(1,1) + cell(3,2)*m(2,1) + cell(3,3)*m(3,1);
	result(3,2) = cell(3,0)*m(0,2) + cell(3,1)*m(1,2) + cell(3,2)*m(2,2) + cell(3,3)*m(3,2);
	result(3,3) = cell(3,0)*m(0,3) + cell(3,1)*m(1,3) + cell(3,2)*m(2,3) + cell(3,3)*m(3,3);

	return result;
}

inline Vector4 Matrix4x4::operator* (const Vector4 &v) const{
	Vector4 result = Vector4(	cell(0,0)*v[0] + cell(0,1)*v[1] + cell(0,2)*v[2] + cell(0,3)*v[3],
								cell(1,0)*v[0] + cell(1,1)*v[1] + cell(1,2)*v[2] + cell(1,3)*v[3],
								cell(2,0)*v[0] + cell(2,1)*v[1] + cell(2,2)*v[2] + cell(2,3)*v[3],
								cell(3,0)*v[0] + cell(3,1)*v[1] + cell(3,2)*v[2] + cell(3,3)*v[3] );
	return result;
}

inline Matrix4x4 Matrix4x4::transpose() const{
	return Matrix4x4(	cell(0,0), cell(1,0), cell(2,0), cell(3,0),
						cell(0,1), cell(1,1), cell(2,1), cell(3,1),
						cell(0,2), cell(1,2), cell(2,2), cell(3,2),
						cell(0,3), cell(1,3), cell(2,3), cell(3,3) );
}

inline void Matrix4x4::load(const Vector4 &v1, const Vector4 &v2, const Vector4 &v3, const Vector4 &v4, Order order){
	switch(order){
	case ROW_ORDER:
		cell(0,0)=v1[0];  cell(0,1)=v1[1];  cell(0,2)=v1[2];  cell(0,3)=v1[3];
		cell(1,0)=v2[0];  cell(1,1)=v2[1];  cell(1,2)=v2[2];  cell(1,3)=v2[3];
		cell(2,0)=v3[0];  cell(2,1)=v3[1];  cell(2,2)=v3[2];  cell(2,3)=v3[3];
		cell(3,0)=v4[0];  cell(3,1)=v4[1];  cell(3,2)=v4[2];  cell(3,3)=v4[3];
		break;
	case COLUMN_ORDER:
		cell(0,0)=v1[0];  cell(0,1)=v2[0];  cell(0,2)=v3[0];  cell(0,3)=v4[0];
		cell(1,0)=v1[1];  cell(1,1)=v2[1];  cell(1,2)=v3[1];  cell(1,3)=v4[1];
		cell(2,0)=v1[2];  cell(2,1)=v2[2];  cell(2,2)=v3[2];  cell(2,3)=v4[2];
		cell(3,0)=v1[3];  cell(3,1)=v2[3];  cell(3,2)=v3[3];  cell(3,3)=v4[3];
		break;
	}
}

inline void Matrix4x4::load(const Real mat[16], Order order){
	switch(order){
	case ROW_ORDER:
		cell(0,0)=mat[0];  cell(0,1)=mat[1];  cell(0,2)=mat[2];  cell(0,3)=mat[3];
		cell(1,0)=mat[4];  cell(1,1)=mat[5];  cell(1,2)=mat[6];  cell(1,3)=mat[7];
		cell(2,0)=mat[8];  cell(2,1)=mat[9];  cell(2,2)=mat[10]; cell(2,3)=mat[11];
		cell(3,0)=mat[12]; cell(3,1)=mat[13]; cell(3,2)=mat[14]; cell(3,3)=mat[15];
		break;
	case COLUMN_ORDER:
		cell(0,0)=mat[0];  cell(0,1)=mat[4];  cell(0,2)=mat[8];  cell(0,3)=mat[12];
		cell(1,0)=mat[1];  cell(1,1)=mat[5];  cell(1,2)=mat[9];  cell(1,3)=mat[13];
		cell(2,0)=mat[2];  cell(2,1)=mat[6];  cell(2,2)=mat[10]; cell(2,3)=mat[14];
		cell(3,0)=mat[3];  cell(3,1)=mat[7];  cell(3,2)=mat[11]; cell(3,3)=mat[15];
		break;
	}
}

inline void Matrix4x4::dump(Real mat[16], Order order) const{
	switch(order){
	case ROW_ORDER:
		mat[0]=cell(0,0);  mat[1]=cell(0,1);  mat[2]=cell(0,2);  mat[3]=cell(0,3);
		mat[4]=cell(1,0);  mat[5]=cell(1,1);  mat[6]=cell(1,2);  mat[7]=cell(1,3);
		mat[8]=cell(2,0);  mat[9]=cell(2,1);  mat[10]=cell(2,2); mat[11]=cell(2,3);
		mat[12]=cell(3,0); mat[13]=cell(3,1); mat[14]=cell(3,2); mat[15]=cell(3,3);
		break;
	case COLUMN_ORDER:
		mat[0]=cell(0,0);  mat[4]=cell(0,1);  mat[8]=cell(0,2);  mat[12]=cell(0,3);
		mat[1]=cell(1,0);  mat[5]=cell(1,1);  mat[9]=cell(1,2);  mat[13]=cell(1,3);
		mat[2]=cell(2,0);  mat[6]=cell(2,1);  mat[10]=cell(2,2); mat[14]=cell(2,3);
		mat[3]=cell(3,0);  mat[7]=cell(3,1);  mat[11]=cell(3,2); mat[15]=cell(3,3);
		break;
	}
}

#endif

