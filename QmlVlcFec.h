

#pragma once

struct FecStats {

    uint16_t blockNumber;
    uint32_t preFecMissingRTPPkts;
    uint32_t preFecReceivedRTPPkts;
    uint32_t postFecMissingRTPPkts;
    uint32_t postFecReceivedTSPkts;
    bool recovered;

};

Q_DECLARE_METATYPE(FecStats)
