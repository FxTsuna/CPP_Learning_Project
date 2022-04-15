#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <numeric>

template <const int size, typename t>

struct Point
{
    std::array<t, size> values {};
    template <typename... Args>
    Point(t first, Args&&... args) : values {first, std::forward<Args>(args)...}
    { static_assert(sizeof ...(args) + 1 == size, "Not corresponding arguments");}
    /*
    Point(t x, t y) : values { x, y }
    { static_assert(size == 2,"Not a Point2D"); }
    Point(t x, t y, t z) : values { x, y, z }
    { static_assert(size == 3,"Not a Point3D"); }
     */


    /*friend void test_generic_points()
    {
        Point<3,int> p1;
        Point<3,int> p2;
        auto p3 = p1 + p2;
        p1 += p2;
        p1 *= 3; // ou 3.f, ou 3.0 en fonction du type de Point
    }*/

    float& x()
    {
        static_assert(size >= 1);
        return values[0];
    }
    float x() const
    {
        static_assert(size >= 1);
        return values[0];
    }

    float& y()
    {
        static_assert(size >=2);
        return values[1];
    }
    float y() const
    {
        static_assert(size >=2);
        return values[1];
    }

    float& z()
    {
        static_assert(size >= 3);
        return values[2];
    }
    float z() const
    {
        static_assert(size >= 3);
        return values[2];
    }

    Point& operator+=(const Point& other)
    {
        std::transform(values.begin(),values.end(),other.values.begin(),values.begin(),std::plus<float> {});
        return *this;
    }

    Point& operator-=(const Point& other)
    {
        std::transform(values.begin(),values.end(),other.values.begin(),values.begin(),std::minus<float> {});
        return *this;
    }

    Point& operator*=(const float scalar)
    {
        std::transform(values.begin(),values.end(),values.begin(),[scalar](float c) { return c*scalar; });
        return *this;
    }

    Point operator+(const Point& other) const
    {
        Point result = *this;
        result += other;
        return result;
    }

    Point operator-(const Point& other) const
    {
        Point result = *this;
        result -= other;
        return result;
    }

    Point operator*(const t scalar) const
    {
        Point result = *this;
        result *= scalar;
        return result;
    }

    Point operator-() const
    {
        return Point { -x(), -y(), -z() };
    }

    float length() const {
        return std::sqrt(std::inner_product(values.begin(), values.end(), values.begin(), float { 0 }));
    }

    float distance_to(const Point& other) const
    {
        return (*this - other).length();
    }

    Point& normalize(const float target_len = 1.0f)
    {
        const float current_len = length();
        if (current_len == 0)
        {
            throw std::logic_error("Current lenght cannot be 0");
        }

        *this *= (target_len / current_len);
        return *this;
    }

    Point& cap_length(const float max_len)
    {
        assert(max_len > 0);

        const float current_len = length();
        if (current_len > max_len)
        {
            *this *= (max_len / current_len);
        }

        return *this;
    }

    Point operator*(const Point& other) const
    {
        Point result = *this;
        result *= other;
        return result;
    }

    Point& operator*=(const Point& other)
    {
        x() *= other.x();
        y() *= other.y();
        return *this;
    }
};

using Point3D = Point<3, float>;
using Point2D = Point<2, float>;

// our 3D-coordinate system will be tied to the airport: the runway is parallel to the x-axis, the z-axis
// points towards the sky, and y is perpendicular to both thus,
// {1,0,0} --> {.5,.5}   {0,1,0} --> {-.5,.5}   {0,0,1} --> {0,1}
inline Point2D project_2D(const Point3D& p)
{
    return { .5f * p.x() - .5f * p.y(), .5f * p.x() + .5f * p.y() + p.z() };
}
