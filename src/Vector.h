/*
  Struct to hold a 3 dimensional vector with components x y z.
*/
struct Vector {
    double x;
    double y;
    double z;

    Vector() {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Vector(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector operator + (Vector p) {
        return Vector(x + p.x, y + p.y, z + p.z);
    }

    Vector operator / (double p) {
        return Vector(x / p, y / p, z / p);
    }

    Vector operator * (double p) {
        return Vector(x * p, y * p, z * p);
    }
};
