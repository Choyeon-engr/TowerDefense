#include "CML.hpp"

void CML::Random::Init()
{
    std::random_device rd;
    Seed(rd());
}

void CML::Random::Seed(unsigned int seed)
{
    sGenerator.seed(seed);
}

float CML::Random::GetRandomFloat(float min, float max)
{
    std::uniform_real_distribution<float> randomFloat(min, max);
    return randomFloat(sGenerator);
}

CML::Vector2D CML::Random::GetRandomVector2D(const Vector2D& min, const Vector2D& max)
{
    Vector2D randomVector2D = Vector2D(GetRandomFloat(0.f, 1.f), GetRandomFloat(0.f, 1.f));
    return min + (max - min) * randomVector2D;
}

std::mt19937 CML::Random::sGenerator;
