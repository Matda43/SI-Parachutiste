#include<iostream>
#include<cmath>


struct Vec
{
    float x, z;

    void Debug() const
    {
        std::cout << x << " " << z;
    }

    Vec operator*(const float f) const
    {
        return Vec{ x * f, z * f };
    }

    Vec operator/(const float f) const
    {
        return Vec{ x / f, z / f };
    }

    Vec operator*(const Vec v) const
    {
        return Vec{ x * v.x, z * v.z };
    }

    Vec operator+(const Vec v) const
    {
        return Vec{ x + v.x, z + v.z };
    }

    float normSquared() const
    {
        return x * x + z * z;
    }

    Vec unitVector() const
    {
        const float norm = std::sqrt(normSquared());
        return Vec{ x / norm, z / norm };
    }
};

Vec operator*(const float f, const Vec v)
{
    return Vec{ f * v.x, f * v.z };
}


int main()
{
    // Coef premier parachutiste
    // const float C = 0.25;
    // Coef second parachutiste
    const float C = 0.09;
    const float mass = 80;
    const float g = 9.8;
    const float dt = 1;
    const Vec zGravity{ 0, -1 };

    float t = 0;
    Vec position{ 0, 4000 };
    Vec velocity{ 50, 0 };

    while (position.z >= 1000)
    {
        const Vec fGravity = zGravity * mass * g;
        const Vec fDrag = velocity.unitVector() * (-C * velocity.normSquared());

        const Vec acceleration = (fGravity + fDrag) / mass;

        velocity = velocity + dt * acceleration;
        position = position + dt * velocity;

        std::cout << t << " ";
        position.Debug();
        std::cout << " ";
        velocity.Debug();
        std::cout << " ";
        acceleration.Debug();
        std::cout << "\n";

        t += dt;
    };

    return 0;
}