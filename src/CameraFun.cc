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
	// get user defined initiation parameters.
	// if we defined the parameters in TADSim UI, override the default values here.

	// by subscribe our interested topics, we expect that the two corresponding messages which defined by
	// traffic.proto and location.proto would received in every Step callback.
	std::cerr << "Init...\n";
	
	
	// 从ui得到SourceSim,Height,Width三个参数
	std::string value = helper.GetParameter("SourceSim");
	if (value.empty()) {
		std::cerr << "Need sim camera address" << std::endl;
		return;
	}
	std::cerr << "SourceSim = " << value << std::endl;
	src_sim_.init(value, 10);

	
	value = helper.GetParameter("Width");
	if (value.empty()) {
		std::cerr << "Need image width" << std::endl;
		return;
	}
	w = std::atoi(value.c_str());
	std::cerr << "Width = " << w << std::endl;

	value = helper.GetParameter("Height");
	if (value.empty()) {
		std::cerr << "Need image height" << std::endl;
		return;
	}
	h = std::atoi(value.c_str());
	std::cerr << "Height = " << h << std::endl;

	// 一个制定大小，格式为8uc4的图像mat
	cvImg_ = cv::Mat(h, w, CV_8UC4);
	
	std::cerr << "Init ok.\n";

}

void CameraFun::Reset(tx_sim::ResetHelper& helper) {
	std::cerr << "Reseting...\n";
	// here we could get some information(e.g. the map which the scenario runs on, suggested local origin coordinate
	// and the destination of the ego car) of the current scenario.

	
	// 调用SharedMemoryReader类的reset()方法
	src_sim_.reset();	

	std::cerr << "Reset ok.\n";
}

void CameraFun::Step(tx_sim::StepHelper& helper) {
	
	std::vector<uint8_t> buffer_sim;
		int64_t timestamp_sim;
		// read()函数读取数据流
		bool flag = !src_sim_.read(buffer_sim, timestamp_sim);
		if (flag)
		{	
			// 读取不到数据的情况下输出
			std::cerr << "Cannot read buffer" << std::endl;			
			return;
		}
		std::cerr << "Timestamp[" << helper.timestamp() << "]: " << timestamp_sim << std::endl;
		// 数据读取成功，将数组buffer_sim中的数据传递给Init()函数中定义的图像mat cvImg_；
		memcpy(cvImg_.data, buffer_sim.data(), w * h * 4);
		std::cerr<<"[Width]: "<<cvImg_.cols<<"\n[Height]: "<<cvImg_.rows \
		<<"\n[Channels]: "<<cvImg_.channels()<<std::endl;

		// 发布话题
		sensor_msgs::ImagePtr msg = cv_bridge::CvImage(std_msgs::Header(),"bgra8",cvImg_).toImageMsg();
		msg->header.stamp = ros::Time::now();
		pub_.publish(msg);
}

void CameraFun::Stop(tx_sim::StopHelper& helper) {
	
	std::cerr << "CameraFun stopped." << std::endl;
	
}
TXSIM_MODULE(CameraFun)
