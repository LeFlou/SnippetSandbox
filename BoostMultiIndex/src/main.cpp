#include <iostream>
#include <memory>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

using namespace ::boost;
using namespace ::boost::multi_index;

enum class Way
{
    UNDEFINED,
    SELL,
    BUY
};

template <typename QuantityType, typename PriceType>
struct GenericOrder
{
    explicit GenericOrder(const Way way, const QuantityType& quantity, const PriceType& price, const long long& timestamp)
        : way_(way), quantity_(quantity), price_(price), timestamp_(timestamp)
    {
    }

    ~GenericOrder() = default;
    GenericOrder(const GenericOrder&) = delete;
    GenericOrder& operator=(const GenericOrder&) = delete;

    Way way_;
    QuantityType quantity_;
    PriceType price_;
    long long timestamp_ = -1;
};

// Aliases
using QuantityType = int;
using PriceType = int;
using OrderType = GenericOrder<QuantityType, PriceType>;
using PointerType = std::shared_ptr<OrderType>;

struct way {};
struct timestamp {};
struct price {};

using MultiIndexOrderContainer = multi_index_container<PointerType,
    indexed_by<
        ordered_non_unique<
            composite_key<
                OrderType,
                member<OrderType, decltype(OrderType::way_), &OrderType::way_>,
                member<OrderType, decltype(OrderType::price_), &OrderType::price_>,
                member<OrderType, decltype(OrderType::timestamp_), &OrderType::timestamp_>
            >
        >
    >
>;

template <typename QuantityType, typename PriceType>
std::ostream& operator<<(std::ostream& os, const GenericOrder<QuantityType, PriceType>& o)
{
    const char* way = nullptr;
    switch (o.way_)
    {
    case Way::UNDEFINED: way = "UNDEFINED"; break;
    case Way::BUY: way = "BUY"; break;
    case Way::SELL: way = "SELL"; break;
        default:
        {
            assert(!"Unknown way");
        }
    }
    
    return os << "[" << o.timestamp_ << "] " << way << " " << o.quantity_ << " @ " << o.price_;
}

int main()
{
    MultiIndexOrderContainer c;

    // Inserting some orders
    
    //c.insert(std::make_shared<OrderType>(Way::BUY, 10, 14, 0));
    //c.insert(std::make_shared<OrderType>(Way::BUY, 10, 13, 0));
    //c.insert(std::make_shared<OrderType>(Way::BUY, 10, 15, 0));
    //c.insert(std::make_shared<OrderType>(Way::BUY, 10, 12, 0));

    //c.insert(std::make_shared<OrderType>(Way::SELL, 10, 16, 3));
    //c.insert(std::make_shared<OrderType>(Way::SELL, 10, 17, 4));
    //c.insert(std::make_shared<OrderType>(Way::SELL, 10, 18, 5));



    c.insert(std::make_shared<OrderType>(Way::BUY, 10, 15, 6));
    c.insert(std::make_shared<OrderType>(Way::BUY, 10, 14, 1));
    c.insert(std::make_shared<OrderType>(Way::BUY, 10, 13, 2));
    //c.insert(std::make_shared<OrderType>(Way::BUY, 10, 11, 3));
    //c.insert(std::make_shared<OrderType>(Way::BUY, 10, 15, 4));

    c.insert(std::make_shared<OrderType>(Way::SELL, 10, 16, 3));
    c.insert(std::make_shared<OrderType>(Way::SELL, 10, 17, 4));
    c.insert(std::make_shared<OrderType>(Way::SELL, 10, 18, 5));

    //c.insert(std::make_shared<OrderType>(Way::UNDEFINED, 10, 25, 8));
    //c.insert(std::make_shared<OrderType>(Way::UNDEFINED, 10, 10, 10));

    // Pick lowest price from selling orders
    //auto it = c.lower_bound(Way::SELL);
    //if (it != c.end())
    //{
    //std::cout << **it << std::endl;
    //}

    {
        std::cout << "--- All buying orders ---" << std::endl;
        auto p = c.equal_range(std::make_tuple(Way::BUY));
        while (p.first != p.second)
        {
            std::cout << **p.first++ << std::endl;
        }
    }

    {
        std::cout << "--- All selling orders ---" << std::endl;
        auto p = c.equal_range(std::make_tuple(Way::SELL));
        while (p.first != p.second)
        {
            std::cout << **p.first++ << std::endl;
        }
    }

    static_assert(Way::UNDEFINED < Way::SELL, "");
    static_assert(Way::SELL < Way::BUY, "");

    {
        std::cout << "--- Highest buying price ---" << std::endl;

        // Ensure there is some orders
        if (c.size())
        {
            // Get last order
            auto it = c.upper_bound(Way::BUY); // O(log(n))
            if ((*--it)->way_ == Way::BUY)
            {
                std::cout << **it << std::endl;
            }
        }
    }

    {
        std::cout << "--- Lowest buying price ---" << std::endl;

        // Ensure there is some orders
        if (c.size())
        {
            // Get last order
            auto it = c.lower_bound(Way::BUY); // O(log(n))
            if (it == c.end())
            {
                std::cout << "There is no buy order" << std::endl;
            }
            else if ((*it)->way_ == Way::BUY)
            {
                std::cout << **it << std::endl;
            }
        }
    }

    {
        std::cout << "--- Highest selling price ---" << std::endl;

        // Ensure there is some orders
        if (c.size())
        {
            // Get last order
            auto it = c.upper_bound(Way::SELL); // O(log(n))
            if ((*--it)->way_ == Way::SELL)
            {
                std::cout << **it << std::endl;
            }
        }
    }

    {
        std::cout << "--- Lowest selling price ---" << std::endl;

        // Ensure there is some orders
        if (c.size())
        {
            // Get last order
            auto it = c.lower_bound(Way::SELL); // O(log(n))
            if (it == c.end())
            {
                std::cout << "There is no sell order" << std::endl;
            }
            else if ((*it)->way_ == Way::SELL)
            {
                std::cout << **it << std::endl;
            }
        }
    }

    {
        std::cout << "Buying orders for 15, sorted by timestamp\n";
        auto p = c.equal_range(std::make_tuple(Way::BUY, 15));
        while (p.first != p.second)
        {
            std::cout << **p.first++ << std::endl;
        }
    }

    //std::cout << **--c.upper_bound(Way::BUY) << std::endl;

    // Pick highest price from buying orders
    /*
    auto buyIt = c.upper_bound(Way::BUY);
    if (buyIt != c.end())
    {
        if (--buyIt == c.end()) // is there any buying order ?
        {
            std::cout << "lol" << std::endl;
        }
        else
        {
            std::cout << **buyIt << std::endl;
        }
    }
    else
    {
        std::cout << **--buyIt << std::endl;
    }
    */

    int dummy;
    std::cin >> dummy;

	return 0;
}