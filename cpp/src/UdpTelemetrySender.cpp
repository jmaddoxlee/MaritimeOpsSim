#include "UdpTelemetrySender.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include <utility>

UdpTelemetrySender::UdpTelemetrySender(
    std::string host,
    std::uint16_t port
) :
    host_(std::move(host)),
    port_(port) {

    }

bool UdpTelemetrySender::sendPacket(
    const std::vector<std::uint8_t>& packet
) const {
    if (packet.empty()) {
        return false;
    }

    const int socketFd = ::socket(AF_INET, SOCK_DGRAM, 0);

    if (socketFd < 0) {
        return false;
    }

    sockaddr_in destination{};
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port_);

    const int addressResult = ::inet_pton(
        AF_INET,
        host_.c_str(),
        &destination.sin_addr
    );

    if (addressResult != 1) {
        ::close(socketFd);
        return false;
    }

    const ssize_t sentBytes = ::sendto(
        socketFd,
        packet.data(),
        packet.size(),
        0,
        reinterpret_cast<sockaddr*>(&destination),
        sizeof(destination)
    );

    ::close(socketFd);

    return sentBytes == static_cast<ssize_t>(packet.size());
}

const std::string& UdpTelemetrySender::getHost() const {
    return host_;
}

std::uint16_t UdpTelemetrySender::getPort() const {
    return port_;
}