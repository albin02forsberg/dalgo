#include <random>

float dalgoRandom()
{
    static bool seeded = false;
    static std::default_random_engine e;
    static std::uniform_real_distribution<> dis(0, 1); // rage 0 - 1
    if (!seeded){
        static std::random_device rd;
        e.seed(rd());
        seeded = true;
    }
    return dis(e);
}


