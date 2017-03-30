// Copyright (c) FRC Team 3512, Spartatroniks 2012-2017. All Rights Reserved.

#include "DriverStationDisplay.hpp"

#include <cstdlib>
#include <cstring>

DriverStationDisplay* DriverStationDisplay::m_dsDisplay = NULL;

DriverStationDisplay::~DriverStationDisplay() {
    m_socket.unbind();
    std::free(m_recvBuffer);
}

DriverStationDisplay* DriverStationDisplay::getInstance(uint16_t dsPort) {
    if (m_dsDisplay == NULL) {
        m_dsDisplay = new DriverStationDisplay(dsPort);
    }

    return m_dsDisplay;
}

void DriverStationDisplay::freeInstance() {
    delete m_dsDisplay;
    m_dsDisplay = NULL;
}

void DriverStationDisplay::sendToDS(sf::Packet* userData) {
    if (m_dsIP != sf::IpAddress::None) {
        if (userData == NULL) {
            m_socket.send(*static_cast<sf::Packet*>(this), m_dsIP, m_dsPort);
        } else {
            m_socket.send(*userData, m_dsIP, m_dsPort);
        }
    }

    // Used for testing purposes
    sf::IpAddress testIP(10, 35, 12, 42);
    if (userData == NULL) {
        m_socket.send(*static_cast<sf::Packet*>(this), testIP, m_dsPort);
    } else {
        m_socket.send(*userData, testIP, m_dsPort);
    }
}

const std::string DriverStationDisplay::receiveFromDS(void* userData) {
    if (m_socket.receive(m_recvBuffer, 256, m_recvAmount, m_recvIP,
                         m_recvPort) == sf::Socket::Done) {
        if (std::strncmp(m_recvBuffer, "connect\r\n", 9) == 0) {
            m_dsIP = m_recvIP;
            m_dsPort = m_recvPort;

            return "connect\r\n";
        } else if (std::strncmp(m_recvBuffer, "autonSelect\r\n", 13) == 0) {
            // Next byte after command is selection choice
            *static_cast<char*>(userData) = m_recvBuffer[13];

            return "autonSelect\r\n";
        }
    }

    return "NONE";
}

DriverStationDisplay::DriverStationDisplay(uint16_t portNumber)
    : m_dsIP(sf::IpAddress::None), m_dsPort(portNumber) {
    m_socket.bind(portNumber);
    m_socket.setBlocking(false);
    m_recvBuffer = static_cast<char*>(std::malloc(256));
}