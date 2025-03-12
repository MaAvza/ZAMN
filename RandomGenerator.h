#pragma once
#include <random>

class RandomGenerator {
public:
    RandomGenerator() : m_rng(std::random_device{}()) {}

    float getRandomFloat(float min, float max) {
        return std::uniform_real_distribution<float>{min, max}(m_rng);
    }

    int getRandomInt(int min, int max) {
        return std::uniform_int_distribution<int>{min, max}(m_rng);
    }

private:
    std::mt19937 m_rng;
};