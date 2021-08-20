#pragma once

#include <systemd/sd-bus.h>

int AcquireBus(sd_bus** ret);
void DbusCaptureThread();
