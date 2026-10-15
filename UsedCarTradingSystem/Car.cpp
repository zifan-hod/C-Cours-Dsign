#include "car.h"

Car::Car() : year(0), mileage(0), price(0.0) {}

Car::Car(const std::string &vin, const std::string &brand)
    : vin(vin), brand(brand), year(0), mileage(0), price(0.0) {}

Car::~Car() {}

void Car::Print() const
{
  // 列宽（按"显示宽度"算，中文占 2 列）
  const int W_VIN    = 8;
  const int W_BRAND  = 6;
  const int W_MODEL  = 6;
  const int W_YEAR   = 8;
  const int W_MILE   = 6;
  const int W_PRICE  = 6;
  const int W_SELLER = 8;
  const int W_STATUS = 6;
  const int W_STORE  = 7;
  const int W_TIME   = 19;

  // 表头
  printField("车架号",   W_VIN);
  printField("品牌",     W_BRAND);
  printField("型号",     W_MODEL);
  printField("上牌年份", W_YEAR);
  printField("里程",     W_MILE);
  printField("售价",     W_PRICE);
  printField("卖家ID",   W_SELLER);
  printField("状态",     W_STATUS);
  printField("门店",     W_STORE);
  printField("上架时间", W_TIME);
  cout << "\n";

  // 分隔线
  cout << string(W_VIN + W_BRAND + W_MODEL + W_YEAR + W_MILE + W_PRICE
               + W_SELLER + W_STATUS + W_STORE + W_TIME, '-')
       << "\n";

  // 数值转字符串
  ostringstream m, p;
  m << mileage;
  p << fixed;
  p.precision(0);            // 售价取整，避免 128000.000000
  p << price;

  // 数据行（列宽与表头完全一致）
  printField(vin,              W_VIN);
  printField(brand,            W_BRAND);
  printField(model,            W_MODEL);
  printField(to_string(year),  W_YEAR);
  printField(m.str(),          W_MILE);
  printField(p.str(),          W_PRICE);
  printField(sellerId,         W_SELLER);
  printField(status,           W_STATUS);
  printField(store,            W_STORE);
  printField(createTime,       W_TIME);
  cout << "\n";
}

std::string Car::ToLine() const
{

  ostringstream oss;
  oss << vin << ':' << brand << ':' << model << ':' << year << ':' << mileage
      << ':' << price << ':' << sellerId << ':' << status << ':' << store << ':'
      << createTime;

  return oss.str();
}

Car Car::FromLine(const std::string &line)
{
  Car cars;
  ostringstream os;
  size_t start = 0;
  while (true)
  {
    size_t pos = line.find(':', start);
    if (pos == string::npos)
      break;
    os << line.substr(start, pos - start) << ' ';
    start = pos + 1;
  }
  os << line.substr(start);

  istringstream is(os.str());

  is >> cars.vin >> cars.brand >> cars.model >> cars.year >> cars.mileage >>
      cars.price >> cars.sellerId >> cars.status >> cars.store;

  string datePart, hh, mm, ss;
  is >> datePart >> hh >> mm >> ss;
  cars.createTime = datePart + " " + hh + ":" + mm + ":" + ss;

  return cars;
}

std::string Car::GetKey() const { return vin; }
