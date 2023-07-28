#pragma once
#include<Vector3.h>
struct Sphere
{
	Vector3 center; //中心点
	float radius;   //半径
};

struct  Plane
{
	Vector3 normal;
	float distance;
};
struct AABB {
	Vector3 min;
	Vector3 max;
};