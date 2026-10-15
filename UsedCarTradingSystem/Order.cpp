#include "Order.h"

Order::Order() {}

Order::Order(const std::string &vin, const std::string &buyer,
             const std::string &seller)
    : carVin(vin), buyerId(buyer), sellerId(seller) {}

Order::~Order() {}


void Order::Print() const
{
  // 列宽（按"显示宽度"算，中文占 2 列）
  const int W_VIN    = 18;
  const int W_BUYER  = 12;
  const int W_SELLER = 12;
  const int W_TIME   = 20;

  // 表头
  printField("车架号",   W_VIN);
  printField("买家ID",   W_BUYER);
  printField("卖家ID",   W_SELLER);
  printField("下单时间", W_TIME);
  cout << "\n";

  // 分隔线
  cout << string(W_VIN + W_BUYER + W_SELLER + W_TIME, '-') << "\n";

  // 数据行（列宽与表头完全一致）
  printField(carVin,     W_VIN);
  printField(buyerId,    W_BUYER);
  printField(sellerId,   W_SELLER);
  printField(createTime, W_TIME);
  cout << "\n";
}


std::string Order::ToLine() const
{

  ostringstream os;
  os << carVin << ':' << buyerId << ':' << sellerId << ':' << createTime;
  return os.str();
}


Order Order::FromLine(const std::string &line)
{

  Order Orders;
  size_t pos = 0;
  size_t start = 0;
  ostringstream os;
  for (int i = 0; i < 3; i++)
  {
    pos = line.find(":", start);
    os << line.substr(start, pos - start) << " ";
    start = pos + 1;
  }
  istringstream is(os.str());
  is >> Orders.carVin >> Orders.buyerId >> Orders.sellerId;
  Orders.createTime = line.substr(start);
  return Orders;
}


std::string Order::GetKey() const { return carVin; }
