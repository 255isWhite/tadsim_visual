#pragma once
#include "txsim_module.h"
#include "MemoryIO.h"
#include <string>
#include <mutex>
#include <limits.h>
#include <opencv2/core/core.hpp>

// ros头文件
#include <ros/ros.h>
#include <sensor_msgs/Image.h>
#include <cv_bridge/cv_bridge.h>
#include <image_transport/image_transport.h>

class CameraFun :
	public tx_sim::SimModule
{
public:
	CameraFun() ; // 必须是无参数默认构造函数
	CameraFun(const ros::NodeHandle& n); //重载

	void Init(tx_sim::InitHelper& helper) override;
	void Reset(tx_sim::ResetHelper& helper) override;
	void Step(tx_sim::StepHelper& helper) override;
	void Stop(tx_sim::StopHelper& helper) override;

	// ros句柄
	ros::NodeHandle nh_;

private:

	SharedMemoryReader src_sim_;
	int w=0, h=0;
	cv::Mat cvImg_;

	// imagetransport相关
	image_transport::ImageTransport it_;
	image_transport::Publisher pub_;
};

