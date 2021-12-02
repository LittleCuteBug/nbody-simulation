#pragma once

#include<body.h>

struct BBox {
	Vector maxP;
	Vector minP;

	BBox();

	BBox(const Vector point);

	void expand(const Vector point);

	Vector centroid() const;

	bool contains(const Vector point);
};