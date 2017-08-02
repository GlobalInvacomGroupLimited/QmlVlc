

#pragma once

struct FecStats {

    uint16_t blockNumber;
    uint32_t missingRTPPkts;
    uint32_t receivedRTPPkts;
    uint32_t missingTSPkts;
    uint32_t receivedTSPkts;
    bool recovered;

};

Q_DECLARE_METATYPE(FecStats)
