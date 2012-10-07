//=============================================================================
//File Name: DriveKinect.h
//Description: Declares Kinect for driving robot
//Author: FRC Team 3512, Spartatroniks
//=============================================================================

#ifndef DRIVE_KINECT_H
#define DRIVE_KINECT_H

#include "KinectBase.h"

class DriveKinect : public KinectBase {
public:
    DriveKinect( sf::IpAddress IP , unsigned short portNumber );

    float getRight();
    float getLeft();

    void setRight( float var );
    void setLeft( float var );

    void clearValues(); // own definition of clearValues()

protected:
    // own definitions of packet manipulation functions
    void insertPacket();
    void insertPacketMutexless( sf::Packet& tempPacket );
    void extractPacket();

private:
    // Packet data
    float right;
    float left;
};

#endif // DRIVE_KINECT_H
