#pragma once
#include "../../Source/Emulator/Data/BitAPI.hxx"
#include <chrono>

namespace emulator::device {
class SerialHostTime : public BitAPI {
public:
    SerialHostTime() : BitAPI(true, 1) {}

    void collectPacket(bool *packet, size_t size) override {
        crashOnUnmet(32);

        if (packet[0]) {
            size_t unixTime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
            for (int i = 0; i < 32; i++) getReturnAPI()->funnelBit((unixTime >> i) & 1);
        }
    }
};
}