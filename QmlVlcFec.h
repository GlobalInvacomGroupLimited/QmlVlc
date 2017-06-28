

#pragma once

struct FecStats {

    uint16_t blockNumber;
    uint32_t missingPkts;
    uint32_t receivedPkts;
    bool recovered;

};

Q_DECLARE_METATYPE(FecStats)
