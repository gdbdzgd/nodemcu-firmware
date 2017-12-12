// Module for RTC time keeping

#include "module.h"
#include "lauxlib.h"
#include "lextra.h"
#include "platform.h"

#include <string.h>
#include <time.h>
#include <sys/time.h>

#include "lwip/err.h"


// sec, usec = rtctime.get ()
void rtctime_set (lua_State *L)
{
  struct timeval tv;
  gettimeofday (&tv, NULL);
  lua_pushnumber (L, tv.tv_sec);
  lua_pushnumber (L, tv.tv_usec);
}

// sec, usec = rtctime.get ()
static int rtctime_get (lua_State *L)
{
  struct timeval tv;
  gettimeofday (&tv, NULL);
  lua_pushnumber (L, tv.tv_sec);
  lua_pushnumber (L, tv.tv_usec);
  return 2;
}


#define ADD_TABLE_ITEM(L, key, val) \
  lua_pushinteger (L, val);	    \
  lua_setfield (L, -2, key);

// rtctime.epoch2cal (stamp)
static int rtctime_epoch2cal (lua_State *L)
{
  struct tm *date;
  time_t stamp = luaL_checkint (L, 1);
  luaL_argcheck (L, stamp >= 0, 1, "wrong arg range");

  date = gmtime (&stamp);

  /* construct Lua table */
  lua_createtable (L, 0, 8);
  ADD_TABLE_ITEM (L, "yday", date->tm_yday + 1);
  ADD_TABLE_ITEM (L, "wday", date->tm_wday + 1);
  ADD_TABLE_ITEM (L, "year", date->tm_year + 1900);
  ADD_TABLE_ITEM (L, "mon",  date->tm_mon + 1);
  ADD_TABLE_ITEM (L, "day",  date->tm_mday);
  ADD_TABLE_ITEM (L, "hour", date->tm_hour);
  ADD_TABLE_ITEM (L, "min",  date->tm_min);
  ADD_TABLE_ITEM (L, "sec",  date->tm_sec);

  return 1;
}

// Module function map
static const LUA_REG_TYPE rtctime_map[] = {
  { LSTRKEY("set"),            LFUNCVAL(rtctime_set) },
  { LSTRKEY("get"),            LFUNCVAL(rtctime_get) },
  { LSTRKEY("epoch2cal"),      LFUNCVAL(rtctime_epoch2cal) },
  { LNILKEY, LNILVAL }
};

NODEMCU_MODULE(RTCTIME, "rtctime", rtctime_map, NULL);
