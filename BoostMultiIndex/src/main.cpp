#include <memory>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>

using namespace ::boost;
using namespace ::boost::multi_index;

enum class Way
{
    UNDEFINED,
    BUY,
    SELL
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
    ordered_non_unique<tag<way>, member<OrderType, decltype(OrderType::way_), &OrderType::way_ >>,
    ordered_non_unique<tag<timestamp>, member<OrderType, decltype(OrderType::timestamp_), &OrderType::timestamp_ >>,
    ordered_non_unique<tag<price>, member<OrderType, decltype(OrderType::price_), &OrderType::price_>>
    >
>;

int main()
{
    MultiIndexOrderContainer c;

    // Inserting some orders
    c.insert(std::make_shared<OrderType>(Way::BUY, 10, 15, 0));
    c.insert(std::make_shared<OrderType>(Way::BUY, 10, 14, 1));
    c.insert(std::make_shared<OrderType>(Way::BUY, 10, 13, 2));
    c.insert(std::make_shared<OrderType>(Way::SELL, 10, 16, 3));
    c.insert(std::make_shared<OrderType>(Way::SELL, 10, 17, 4));
    c.insert(std::make_shared<OrderType>(Way::SELL, 10, 18, 5));

	return 0;
}