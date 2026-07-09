#pragma once

#include <cstdint>
#include <string>
#include <vector>

class UdpTelemetrySender {
    public:
        UdpTelemetrySender(
            std::string host = "127.0.0.1",
            std::uint16_t port = 5005
        );

        bool sendPacket(const std::vector<std::uint8_t>& packet) const;

        const std::string& getHost() const;
        std::uint16_t getPort() const; 
    private:
        std::string host_;
        std::uint16_t port_;
};