
#ifndef VECS_HPP
#define VECS_HPP


class Vec3f{
    private:
        float x, y, z;
    
    public:
        Vec3f(float x, float y, float z);
        Vec3f() = default;
        float getX() const;
        float getY() const;
        float getZ() const;
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        Vec3f operator*(const Vec3f& vec) const;
        Vec3f operator+(const Vec3f& vec) const;
        Vec3f operator-(const Vec3f& vec) const;
        Vec3f operator*(float scalar) const;
        Vec3f operator/(float scalar) const;
        Vec3f operator*=(const Vec3f& vec);
        Vec3f operator/=(const Vec3f& vec);
        Vec3f operator+=(const Vec3f& vec);
        Vec3f operator-=(const Vec3f& vec);
        float dot(const Vec3f& vec) const;
        Vec3f cross(const Vec3f& vec) const;
        Vec3f normalized() const;
};


class RGB {
    private:
        float r, g, b;
    
    public:
        RGB(float r, float g, float b);
        RGB(int r, int g, int b);
        RGB() = default;
        float getR() const;
        float getG() const;
        float getB() const;
        void setR(float r);
        void setG(float g);
        void setB(float b);

        RGB operator+(const RGB& other) const;
        RGB operator-(const RGB& other) const;
        RGB operator*(const RGB& other) const;
        RGB operator/(const RGB& other) const;

        RGB operator*(const Vec3f& vec) const;
        RGB operator+(const Vec3f& vec) const;
        RGB operator*=(const Vec3f& vec) const;
        RGB operator+=(const Vec3f& vec) const;


        RGB operator*(float scalar) const;
        RGB operator/(float scalar) const;
        RGB operator+(float scalar) const;
        RGB operator-(float scalar) const;

        void operator+=(const RGB& other);
        void operator-=(const RGB& other);
        void operator*=(const RGB& other);
        void operator/=(const RGB& other);
};


#endif