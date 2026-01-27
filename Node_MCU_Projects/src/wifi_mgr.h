#ifndef WIFI_MGR_H
#define WIFI_MGR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

void wifi_init(void);
void wifi_loop(void);
bool wifi_is_connected(void);
int  wifi_get_rssi(void);

#ifdef __cplusplus
}
#endif

#endif
