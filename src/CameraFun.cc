#include "CameraFun.h"
#include <iostream>
#include <fstream>
#include <assert.h>
#include <thread>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <stdio.h>
#include <cstring>
#include <opencv2/highgui/highgui.hpp>

// ros相关头文件
#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>


// std::ofstream of("cam.txt");
// std::streambuf* cerr_buf = std::cerr.rdbuf(of.rdbuf());
  
CameraFun::CameraFun():it_(ros::NodeHandle()){
	std::cerr<<"default constructor\n";
}

// 重载构造函数
CameraFun::CameraFun(const ros::NodeHandle& n):it_(n){
	std::cerr<<"with handle constructor\n";
	pub_ = it_.advertise("tadsim_img",0);
}

void CameraFun::Init(tx_sim::InitHelper& helper)
{
	std::cerr << "Init...\n";
	
	
	// 从ui得到图像的Height,Width

	auto value = helper.GetParameter("Width");
	if (value.empty()) {
		std::cerr << "Need image width" << std::endl;
		return;
	}
	w_ = std::atoi(value.c_str());
	std::cerr << "Width = " << w_ << std::endl;

	value = helper.GetParameter("Height");
	if (value.empty()) {
		std::cerr << "Need image height" << std::endl;
		return;
	}
	h_ = std::atoi(value.c_str());
	std::cerr << "Height = " << h_ << std::endl;
	
	std::cerr << "Init ok.\n";

	helper.Subscribe(tx_sim::topic::kSensor);

}

void CameraFun::Reset(tx_sim::ResetHelper& helper) {
	std::cerr << "Reseting...\n";
	// here we could get some information(e.g. the map which the scenario runs on, suggested local origin coordinate
	// and the destination of the ego car) of the current scenario.

	std::cerr << "Reset ok.\n";
}

void CameraFun::Step(tx_sim::StepHelper& helper) {
	std::cerr << "[timestamp] "<<helper.timestamp() << "\n";
	helper.GetSubscribedMessage(tx_sim::topic::kSensor, payload_);

	sim_msg::SensorRaw sensorraw;
	if (payload_.empty() || !sensorraw.ParseFromString(payload_)){
		std::cerr << "Cannot parse sensorraw" << std::endl;
		return;
	}
	// std::cerr << " sensorraw.sensor length is :" << sensorraw.sensor().size() << std::endl;
	
	for(auto& sensor:sensorraw.sensor()){
		if(sensor.type() == sim_msg::SensorRaw::TYPE_CAMERA){

			sim_msg::CameraRaw camera;
			if (!camera.ParseFromString(sensor.raw()))
			{
				std::cerr << "camera error";
			}
			std::cerr<<"[Camera] data type is "<<camera.type()<<std::endl;
			        // Assuming camera type is JPEG
        	if (camera.type() == "JPEG") {

				std::fstream of(img_last_, std::ios::out | std::ios::binary);
				of.write(camera.image_data().c_str(), camera.image_data().size());
				of.close();

				cvImg_ = cv::imread(img_last_, cv::IMREAD_COLOR);
           		// Convert OpenCV image to ROS image message
            	sensor_msgs::ImagePtr ros_image = cv_bridge::CvImage(std_msgs::Header(), "bgr8", cvImg_).toImageMsg();

            	// Publish the ROS image message
            	pub_.publish(ros_image);

            	std::cerr << "[ROS] Publish image success" << std::endl;
			}
		}
	}
}

void CameraFun::Stop(tx_sim::StopHelper& helper) {
	
	std::cerr << "CameraFun stopped." << std::endl;
	
}
TXSIM_MODULE(CameraFun)
