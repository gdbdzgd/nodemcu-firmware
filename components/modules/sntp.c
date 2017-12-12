// Module for RTC time keeping

#include "module.h"
#include "lauxlib.h"
#include "lextra.h"
#include "platform.h"

#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "esp_event_loop.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "apps/sntp/sntp.h"


static const char *TAG = "sntp";
// sntp.sync (server or nil, syncfn or nil, errfn or nil)
void sntp_sync (lua_State *L)
{
    ESP_LOGI(TAG, "Initializing SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}

// Module function map
static const LUA_REG_TYPE sntp_map[] = {
  { LSTRKEY("sync"),  LFUNCVAL(sntp_sync)  },
//#ifdef LUA_USE_MODULES_RTCTIME
//  { LSTRKEY("setoffset"),  LFUNCVAL(sntp_setoffset)  },
//  { LSTRKEY("getoffset"),  LFUNCVAL(sntp_getoffset)  },
//#endif
  { LNILKEY, LNILVAL }
};

NODEMCU_MODULE(SNTP, "sntp", sntp_map, NULL);
