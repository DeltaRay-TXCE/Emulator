#include <iostream>
#include "../../Device/SerialHostTime/Device.hxx"

class TimeReader : public emulator::BitAPI {
public:
    TimeReader() : BitAPI(true, 32) {}

    void collectPacket(bool *packet, size_t size) override {
        size_t unixTime = 0;
        for (int i = 0; i < 32; i++) unixTime |= packet[i] << i;
        std::cout << "Unix time: " << unixTime << std::endl;
    }
};

int main(const int argc, const char* argv[])
{
    emulator::device::SerialHostTime device;

    device.setReturnAPI(new TimeReader());

    device.funnelBit(true);

    return 0;
}