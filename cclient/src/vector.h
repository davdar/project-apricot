#ifndef VECTOR3_H
#define VECTOR3_H

#include <cmath>
#include "types.h"

class Vector2;
class Vector3;
class Vector4;

/*
* Vector2
*/
class Vector2 {
private:
    Real val[2];

public:
    Vector2();
    Vector2(const Vector2 &v);
    Vector2(const Vector3 &v);
    Vector2(const Vector4 &v);
    Vector2(Real v12);
    Vector2(Real v1, Real v2);

    Real &operator [] (int index);
    const Real &operator [] (int index) const;

    Vector2 operator* (Real sca) const;
    Vector2 operator/ (Real sca) const;
    Vector2 operator+ (const Vector2 &v) const;
    Vector2 operator- (const Vector2 &v) const;

    void operator*= (Real sca);
    void operator/= (Real sca);
    void operator+= (const Vector2 &vec);
    void operator-= (const Vector2 &vec);
};

/*
* Vector3
*/
class Vector3 {
private:
	Real val[3];

public:
	Vector3();
	Vector3(const Vector3 &v);
	Vector3(const Vector4 &v);
	Vector3(Real v123);
	Vector3(Real v1, Real v2, Real v3);


	Real &operator [] (int index);
	const Real &operator[] (int index) const;

	Vector3 operator* (Real sca) const;
	Vector3 operator/ (Real sca) const;
	Vector3 operator+ (const Vector3 &vec) const;
	Vector3 operator- (const Vector3 &vec) const;

	void operator/= (Real sca);
	void operator*= (Real sca);
	void operator+= (const Vector3 &vec);
	void operator-= (const Vector3 &vec);
};

/*
*	Vector4
*/
class Vector4{
public:
	Real val[4];

	Vector4();
	Vector4(const Vector4 &v);
	Vector4(const Vector3 &v, Real v4);
	Vector4(Real fill);
	Vector4(Real v1, Real v2, Real v3, Real v4);

	Real &operator[] (int index);
	const Real &operator[] (int index) const;

	Vector4 operator* (Real sca);
	Vector4 operator/ (Real sca);
	Vector4 operator+ (const Vector4 &vec) const;
	Vector4 operator- (const Vector4 &vec) const;

	void operator*= (Real sca);
	void operator/= (Real sca);
	void operator+= (const Vector4 &vec);
	void operator-= (const Vector4 &vec);
};

/*
  Global Vector2 functions
*/

inline Vector2 operator *(Real sca, const Vector2 &vec){
    return Vector2(sca*vec[0], sca*vec[1]);
}

inline Vector2 operator -(const Vector2 &vec){
    return Vector2(-vec[0], -vec[1]);
}

/*
  Vector2 function declarations
*/

inline Vector2::Vector2(){
    val[0] = val[1] = 0.0;
}

inline Vector2::Vector2(const Vector2 &vec){
    val[0] = vec[0];
    val[1] = vec[1];
}

inline Vector2::Vector2(const Vector3 &vec){
    val[0] = vec[0];
    val[1] = vec[1];
}

inline Vector2::Vector2(const Vector4 &vec){
    val[0] = vec[0];
    val[1] = vec[1];
}

inline Vector2::Vector2(Real v12){
    val[0] = val[1] = v12;
}

inline Vector2::Vector2(Real v1, Real v2){
    val[0] = v1;
    val[1] = v2;
}

inline Real &Vector2::operator[] (int index){
    return val[index];
}

inline const Real &Vector2::operator[] (int index) const {
    return val[index];
}

inline Vector2 Vector2::operator* (Real sca) const {
    return Vector2(val[0]*sca, val[1]*sca);
}

inline Vector2 Vector2::operator/ (Real sca) const {
    return Vector2(val[0]/sca, val[1]/sca);
}

inline Vector2 Vector2::operator+ (const Vector2 &vec) const {
    return Vector2(val[0] + vec[0], val[1] + vec[1]);
}

inline Vector2 Vector2::operator- (const Vector2 &vec) const {
    return Vector2(val[0] - vec[0], val[1] - vec[1]);
}

inline void Vector2::operator*= (Real sca){
    val[0] *= sca;
    val[1] *= sca;
}

inline void Vector2::operator/= (Real sca){
    val[0] /= sca;
    val[1] /= sca;
}

inline void Vector2::operator+= (const Vector2 &vec){
    val[0] += vec[0];
    val[1] += vec[1];
}

inline void Vector2::operator-= (const Vector2 &vec){
    val[0] -= vec[0];
    val[1] -= vec[1];
}

/*
*	Global operators
*/
inline Vector3 operator* (Real sca, const Vector3 &vec){
	return Vector3(sca*vec[0], sca*vec[1], sca*vec[2]);
}

inline Vector3 operator- (const Vector3 &vec){
	return Vector3(-vec[0], -vec[1], -vec[2]);
}

/*
*	Vector3 function declarations
*/

inline Vector3::Vector3(){
		val[0] = val[1] = val[2] = 0.f;
}

inline Vector3::Vector3(const Vector3 &v){
	val[0] = v[0];
	val[1] = v[1];
	val[2] = v[2];
}

inline Vector3::Vector3(const Vector4 &v){
	val[0] = v[0];
	val[1] = v[1];
	val[2] = v[2];
}

inline Vector3::Vector3(Real v123){
		val[0] = val[1] =  val[2] = v123;
}
	
inline Vector3::Vector3(Real v1, Real v2, Real v3){
		val[0] = v1;
		val[1] = v2;
		val[2] = v3;
}

inline Real dot(const Vector3 &v1, const Vector3 &v2){
	return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

inline Vector3 cross(const Vector3 &v1, const Vector3 &v2){
	Real x = v1[1]*v2[2] - v1[2]*v2[1];
	Real y = v1[2]*v2[0] - v1[0]*v2[2];
	Real z = v1[0]*v2[1] - v1[1]*v2[0];
	return Vector3(x,y,z);
}

inline Real magnitudeSqr(const Vector3 &vec){
	return vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2];
}

inline Real magnitude(const Vector3 &vec){
	return sqrt(magnitudeSqr(vec));
}

inline void normalize(Vector3 &vec){
	Real mag = magnitude(vec);
	vec /= mag;
}


/*
* Vector3 operator definitions
*/

inline const Real &Vector3::operator [] (int index) const { return val[index]; }
inline Real &Vector3::operator [] (int index) { return val[index]; }

inline Vector3 Vector3::operator* (Real sca) const {
	return Vector3(val[0]*sca, val[1]*sca, val[2]*sca);
}

inline Vector3 Vector3::operator/ (Real sca) const {
	return Vector3(val[0]/sca, val[1]/sca, val[2]/sca);
}

inline Vector3 Vector3::operator- (const Vector3 &vec) const {
	return Vector3(val[0]-vec[0], val[1]-vec[1], val[2]-vec[2]);
}

inline Vector3 Vector3::operator+ (const Vector3 &vec) const {
	return Vector3(val[0]+vec[0], val[1]+vec[1], val[2]+vec[2]);
}

inline void Vector3::operator*= (Real sca){
	val[0] *= sca;
	val[1] *= sca;
	val[2] *= sca;
}

inline void Vector3::operator/= (Real sca){
	val[0] /= sca;
	val[1] /= sca;
	val[2] /= sca;
}

inline void Vector3::operator+= (const Vector3 &vec){
	val[0] += vec[0];
	val[1] += vec[1];
	val[2] += vec[2];
}

inline void Vector3::operator-= (const Vector3 &vec){
    val[0] -= vec[0];
    val[1] -= vec[1];
    val[2] -= vec[2];
}


/*
*	Vector4 function definitions
*/

inline Vector4::Vector4(){
		val[0] = val[1] = val[2] = val[3] = 0.f;
}

inline Vector4::Vector4(const Vector4 &v){
	val[0] = v[0];
	val[1] = v[1];
	val[2] = v[2];
	val[3] = v[3];
}

inline Vector4::Vector4(const Vector3 &v, Real v4){
	val[0] = v[0];
	val[1] = v[1];
	val[2] = v[2];
	val[3] = v4;
}

inline Vector4::Vector4(Real fill){
		val[0] = val[1] = val[2] = val[3] = fill;
}

inline Vector4::Vector4(Real v1, Real v2, Real v3, Real v4){
		val[0] = v1;
		val[1] = v2;
		val[2] = v3;
		val[3] = v4;
}

inline Real &Vector4::operator[] (int index){
	return val[index];
}

inline const Real &Vector4::operator[] (int index) const{
	return val[index];
}

inline Vector4 Vector4::operator* (Real sca){
	return Vector4(val[0]*sca, val[1]*sca, val[2]*sca, val[3]*sca);
}

inline Vector4 Vector4::operator/ (Real sca){
	return Vector4(val[0]/sca, val[1]/sca, val[2]/sca, val[3]/sca);
}

inline Vector4 Vector4::operator+ (const Vector4 &vec) const {
	return Vector4(
		val[0]+vec[0],
		val[1]+vec[1],
		val[2]+vec[2],
		val[3]+vec[3]);
}

inline Vector4 Vector4::operator- (const Vector4 &vec) const {
	return Vector4(
		val[0]-vec[0],
		val[1]-vec[1],
		val[2]-vec[2],
		val[3]-vec[3]);
}

inline void Vector4::operator*= (Real sca){
	val[0] *= sca;
	val[1] *= sca;
	val[2] *= sca;
	val[3] *= sca;
}

inline void Vector4::operator/= (Real sca){
	val[0] /= sca;
	val[1] /= sca;
	val[2] /= sca;
	val[3] /= sca;
}

inline void Vector4::operator+= (const Vector4 &vec){
	val[0] += vec[0];
	val[1] += vec[1];
	val[2] += vec[2];
	val[3] += vec[3];
}

inline void Vector4::operator-= (const Vector4 &vec){
	val[0] -= vec[0];
	val[1] -= vec[1];
	val[2] -= vec[2];
	val[3] -= vec[3];
}




#endif

