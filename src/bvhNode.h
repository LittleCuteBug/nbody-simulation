#pragma once

#include<body.h>
#include<BBox.h>

struct bvhNode
{
	bvhNode* l;
	bvhNode* r;
	BBox bbox;

	Body body;

	~bvhNode() {
		if (l) delete l;
		if (r) delete r;
	}

	bvhNode(std::vector<Body>::iterator start, std::vector<Body>::iterator end) {
		int cntPoint = 0;

		for (auto p = start; p != end; p++) {
			bbox.expand((*p).position_);
			cntPoint++;
		}

		if (cntPoint == 1) {
			body = (*start).copy();
			l = nullptr;
			r = nullptr;
			return;
		}

		double length_x = bbox.maxP.x - bbox.minP.x;
		double length_y = bbox.maxP.y - bbox.minP.y;
		double length_z = bbox.maxP.z - bbox.minP.z;

		
		std::vector<Body>::iterator it1, it2;
		it1 = start;
		it2 = end;


		Vector centroid = bbox.centroid();

		if (length_x >= length_y && length_x >= length_z) {
			while (it1 != it2)
			{
				Vector bb_centroid = (*it1).position_;
				if (bb_centroid.x >= centroid.x) {
					swap(*(it1), *(--it2));
				}
				else {
					it1++;
				}
			}
		}
		else if (length_y >= length_z) {
			while (it1 != it2)
			{
				Vector bb_centroid = (*it1).position_;
				if (bb_centroid.y >= centroid.y) {
					swap(*(it1), *(--it2));
				}
				else {
					it1++;
				}
			}
		}
		else {
			while (it1 != it2)
			{
				Vector bb_centroid = (*it1).position_;
				if (bb_centroid.z >= centroid.z) {
					swap(*(it1), *(--it2));
				}
				else {
					it1++;
				}
			}
		}
		
		if (it1 == start || it1 == end) {
			int dist = distance(start, end);
			it1 = start;
			advance(it1, dist / 2);
		}
		
		l = new bvhNode(start, it1);
		r = new bvhNode(it1, end);
		body = Body::combineBody(l->body, r->body);
	}

	void updateForce(Body* body_) {
		if (bbox.contains(body_->position_)) {
			if(l != nullptr) 
				l->updateForce(body_);
			if(r != nullptr)
				r->updateForce(body_);
		}
		else {
			body_->addForce(body);
		}
	}
};