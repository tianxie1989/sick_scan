//
// Created by michael on 10/4/18.
//

#ifndef SICK_SCAN_SICK_GENERIC_IMU_H
#define SICK_SCAN_SICK_GENERIC_IMU_H

/*
 * Copyright (C) 2018, Ing.-Buero Dr. Michael Lehning, Hildesheim
 * Copyright (C) 2018, SICK AG, Waldkirch
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Osnabrück University nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *  Created on: 28th May 2018
 *
 *      Authors:
 *       Michael Lehning <michael.lehning@lehning.de>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/PointCloud.h>
#include <sensor_msgs/PointCloud2.h>
#include <std_msgs/String.h>

#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/publisher.h>
#include <sick_scan/sick_scan_common_nw.h>
#include <sick_scan/RadarScan.h> // generated by msg-generator

#ifndef _MSC_VER
#include <dynamic_reconfigure/server.h>
#include <sick_scan/SickScanConfig.h>
#endif
#include "sick_scan/sick_generic_parser.h"
#include "sick_scan/sick_scan_common_nw.h"
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include "softwarePLL.h"
namespace sick_scan
  {


      class SickScanImuValue
      {
      public:
          UINT64 TimeStamp() const { return timeStamp; }
          void TimeStamp(UINT64 val) { timeStamp = val; }
          float QuaternionX() const { return quaternionX; }
          void QuaternionX(float val) { quaternionX = val; }
          float QuaternionY() const { return quaternionY; }
          void QuaternionY(float val) { quaternionY = val; }
          float QuaternionZ() const { return quaternionZ; }
          void QuaternionZ(float val) { quaternionZ = val; }
          float QuaternionW() const { return quaternionW; }
          void QuaternionW(float val) { quaternionW = val; }

          float QuaternionAccuracy() const { return quaternionAccuracy; }
          void QuaternionAccuracy(float val) { quaternionAccuracy = val; }


          float AngularVelocityX() const { return velocityX; }
          void AngularVelocityX(float val) { velocityX = val; }
          float AngularVelocityY() const { return velocityY; }
          void AngularVelocityY(float val) { velocityY = val; }
          float AngularVelocityZ() const { return velocityZ; }
          void AngularVelocityZ(float val) { velocityZ = val; }

          UINT16 AngularVelocityReliability() const {return velocityReliability;}
          void AngularVelocityReliability(UINT16 val) {velocityReliability = val;}

          float LinearAccelerationX() const { return linearAccelerationX; }
          void LinearAccelerationX(float val) { linearAccelerationX = val; }
          float LinearAccelerationY() const { return linearAccelerationY; }
          void LinearAccelerationY(float val) { linearAccelerationY = val; }
          float LinearAccelerationZ() const { return linearAccelerationZ; }
          void LinearAccelerationZ(float val) { linearAccelerationZ = val; }

          UINT16 LinearAccelerationReliability() const {return linearAccelerationReliability;}
          void LinearAccelerationReliability(UINT16 val) {linearAccelerationReliability = val;}

      private:
          UINT32 timeStamp;
          float quaternionX;
          float quaternionY;
          float quaternionZ;
          float quaternionW;
          float quaternionAccuracy;
          float velocityX;
          float velocityY;
          float velocityZ;
          UINT16 velocityReliability;
          float linearAccelerationX;
          float linearAccelerationY;
          float linearAccelerationZ;
          UINT16 linearAccelerationReliability;

          };

      class SickScanImu
          {
      public:
          SickScanImu(SickScanCommon *commonPtr_)
            {
            commonPtr = commonPtr_;
            }
          bool isImuDatagram(char *datagram, size_t datagram_length);
          bool isImuBinaryDatagram(char *datagram, size_t datagram_length);
          bool isImuAsciiDatagram(char *datagram, size_t datagram_length);
          bool isImuAckDatagram(char *datagram, size_t datagram_length);

          int parseDatagram(ros::Time timeStamp, unsigned char *receiveBuffer, int actual_length, bool useBinaryProtocol);
          int parseAsciiDatagram(char* datagram, size_t datagram_length, SickScanImuValue *imValuePtr);
          int parseBinaryDatagram(char* datagram, size_t datagram_length, SickScanImuValue *imValuePtr);
          static void imuParserTest();
          double simpleFmodTwoPi(double angle);
      private:
          SoftwarePLL imuSoftwarePLL;
          SickScanCommon *commonPtr;
          bool emul;
          };

  } /* namespace sick_scan */


#endif //SICK_SCAN_SICK_GENERIC_IMU_H
