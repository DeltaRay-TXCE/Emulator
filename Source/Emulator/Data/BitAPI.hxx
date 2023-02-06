#pragma once
#include <iostream>
#include <exception>
#include <initializer_list>

namespace emulator {
class BitAPI {
private:
    bool *m_packet;
    bool m_autoTrigger;
    bool m_detectCorruption = true;
    size_t m_packetSize;
    size_t m_newestBits {};

    BitAPI *m_returnAPI;

    void reset(bool reBuildPacket = true) {
        delete m_packet;
        m_newestBits = 0;
        if (reBuildPacket)
            m_packet = new bool[m_packetSize];
    }

public:
    explicit BitAPI(bool autoTrigger = false, size_t packetSize = 1) : m_autoTrigger(autoTrigger), m_packetSize(packetSize), m_newestBits(0), m_returnAPI(nullptr) {
        m_packet = new bool[packetSize];
    }

    virtual ~BitAPI() {
        reset(false);
    }

    void funnelBit(bool bit) {
        m_packet[m_newestBits] = bit;
        m_newestBits++;

        collectDirectDrive(bit);

        if (m_autoTrigger && m_newestBits == m_packetSize) {
            collectPacket(m_packet, m_packetSize);
            reset();
        }
    }

    void setTriggerMode(bool automatic = true) {
        m_autoTrigger = automatic;
    }

    void setReturnAPI(BitAPI *api) {
        m_returnAPI = api;
    }

    void setPacketSize(size_t size) {
        if (size > 0) m_packetSize = size;
    }

    void setDetectCorruption(bool detect = true) {
        m_detectCorruption = detect;
    }

    void writePacket(std::initializer_list<bool> packet) {
        for (bool bit : packet) funnelBit(bit);
    }

    void flush() {
        if (m_detectCorruption && m_newestBits > m_packetSize)
            throw std::runtime_error("Corrupted packet detected! (Packet size: " + std::to_string(m_packetSize) + ", Newest bits: " + std::to_string(m_newestBits) + ")");
        if (m_packetSize > 0 && m_newestBits < m_packetSize)
            for (size_t i = m_newestBits; i < m_packetSize; i++) m_packet[i] = false;

        collectPacket(m_packet, m_packetSize);
    }

    [[nodiscard]] constexpr bool getTriggerMode() const {
        return m_autoTrigger;
    }

    [[nodiscard]] constexpr size_t getPacketSize() const {
        return m_packetSize;
    }

    [[nodiscard]] constexpr bool *getPacket() const {
        return m_packet;
    }

    [[nodiscard]] constexpr size_t getNewestBits() const {
        return m_newestBits;
    }

    [[nodiscard]] constexpr bool getDetectCorruption() const {
        return m_detectCorruption;
    }

    [[nodiscard]] constexpr BitAPI *getReturnAPI() const {
        return m_returnAPI;
    }

    void crashOnUnmet(size_t bitExpectancy) {
        if (m_returnAPI != nullptr && m_returnAPI->getPacketSize() != bitExpectancy)
            throw std::runtime_error("Unmet bit expectation! (Expected: " + std::to_string(bitExpectancy) + ", Actual: " + std::to_string(m_returnAPI->getPacketSize()) + ")");
    }

    virtual void collectDirectDrive(bool value) {}
    virtual void collectPacket(bool *value, size_t size) {}
};
}