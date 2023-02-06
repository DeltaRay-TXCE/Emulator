#include <iostream>
#include "../Emulator/Data/BitAPI.hxx"

class BitReader : public emulator::BitAPI {
public:
    BitReader() {
        setTriggerMode(false);
        setPacketSize(1);
    }

    void collectPacket(bool *packet, size_t size) override {
        for (size_t i = 0; i < size; i++) {
            std::cout << packet[i];
        }
        std::cout << std::endl;
    }

    void collectDirectDrive(bool bit) override {

    }
};

int main(const int argc, const char* argv[])
{
    BitReader reader;

    reader.funnelBit(true);

    reader.flush();

    return 0;
}