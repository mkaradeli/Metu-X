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

enum distance_unit	{
	mm
};

class Lidar {
	public:
		Lidar();
		void FrameHandler(uint8_t* frame, uint8_t size);
		void SaveConfig();
		void SetFrameRate(uint16_t rate);
		void Reset();
	private:
		uint16_t distance = 0;
		uint16_t strength = 0;
		uint16_t temperature = 0;
		uint8_t checksum = 0;
		uint32_t interval_us = 0;
		uint32_t flag_us = 0;
		bool status = false;
};





#endif /* DRIVERS_LIDAR_LIDAR_HPP_ */
