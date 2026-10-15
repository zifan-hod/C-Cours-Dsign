#include "Record.h"
#include <cstdio>
#include <time.h>
using namespace std;
std::string GetNowTime() {

  time_t now = time(0);
  tm tmnow;
  localtime_r(&now, &tmnow);
  char stime[80];

  snprintf(stime, sizeof(stime), "%04d-%02d-%02d %02d:%02d:%02d",
           tmnow.tm_year + 1900, tmnow.tm_mon + 1, tmnow.tm_mday, tmnow.tm_hour,
           tmnow.tm_min, tmnow.tm_sec);

  return string(stime);


}
