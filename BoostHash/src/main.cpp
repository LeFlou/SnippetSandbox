#include <iostream>
#include <unordered_map>
#include <boost/functional/hash.hpp>

struct Key
{
    explicit Key(const int i, const float f, const std::string& s)
        : integer(i), floating(f), str(s) {}

    int integer = 0;
    float floating = 0.f;
    std::string str;
};

struct KeyEqual
{
    bool operator()(const Key* k1, const Key* k2) const
    {
        return k1->integer == k2->integer && k1->floating == k2->floating;
    }
};

struct KeyHash
{
    size_t operator()(const Key* k1) const
    {
        size_t seed = 0;
        boost::hash_combine(seed, boost::hash_value(k1->integer));
        boost::hash_combine(seed, boost::hash_value(k1->floating));
        boost::hash_combine(seed, boost::hash_value(k1->str));

        size_t seed2 = 0;
        boost::hash_combine(seed2, k1->integer);
        boost::hash_combine(seed2, k1->floating);
        boost::hash_combine(seed2, k1->str);
        assert(seed == seed2);

        std::cout << seed << std::endl;
        return seed;
    }
};

int main()
{
    // Custom hash, custom equal_to
    std::unordered_map<Key*, size_t, KeyHash, KeyEqual> hashMap;

    Key* k1 = new Key(42, 42.42, "42");
    Key* k2 = new Key(10, 5.7, "hello world");

    hashMap.insert({ k1, 42 });
    hashMap.insert({ k2, 85 });

    Key* k3 = new Key(42, 42.42, "42");

    auto it = hashMap.find(k3);
    if (it != std::end(hashMap))
    {
        std::cout << "Found" << std::endl;
    }
    else
    {
        std::cout << "Not found" << std::endl;
    }

    delete k1;
    delete k2;
    delete k3;

    int dummy;
    std::cin >> dummy;

	return 0;
}