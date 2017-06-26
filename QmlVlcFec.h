

#pragma once

typedef struct {

    uint16_t blockNumber;
    uint32_t missingPkts;
    uint32_t receivedPkts;
    bool recovered;

}fecstats_t;
