#include<BBox.h>

BBox::BBox() {
	maxP = Vector(-1e9, -1e9, -1e9);
	minP = Vector(1e9, 1e9, 1e9);
}

BBox::BBox(const Vector point) {
	maxP = point;
	minP = point;
}

void BBox::expand(const Vector point) {
	maxP.x = max(maxP.x, point.x);
	maxP.y = max(maxP.y, point.y);
	maxP.z = max(maxP.z, point.z);
}

Vector BBox::centroid() const {
	return Vector((maxP.x + minP.x) / 2, (maxP.y + minP.y) / 2, (maxP.z + minP.z) / 2);
}

bool BBox::contains(const Vector point) {
	return (point.x >= minP.x && point.x <= maxP.x
		&& point.y >= minP.y && point.y <= maxP.y
		&& point.z >= minP.z && point.z <= maxP.z);
}