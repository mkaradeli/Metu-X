/*
 * Lidar.hpp
 *
 *  Created on: Aug 1, 2025
 *      Author: alica
 */

#ifndef DRIVERS_LIDAR_LIDAR_HPP_
#define DRIVERS_LIDAR_LIDAR_HPP_

#define LIDAR_FRAME_HEADER 0x59
#define LIDAR_FRAME_SIZE 9

#include <stdint.h>

class Lidar {
	public:
		Lidar();
		void FrameHandler(uint8_t* frame, uint8_t size);
	private:
		uint8_t distance = 0;
		uint8_t strength = 0;
		uint8_t temperature = 0;
		uint8_t checksum = 0;
		uint32_t interval_us = 0;
		uint32_t flag_us = 0;
		bool status = false;
};





#endif /* DRIVERS_LIDAR_LIDAR_HPP_ */
