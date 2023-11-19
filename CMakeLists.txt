cmake_minimum_required(VERSION 3.15)
project(tadsim_visual)
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  cv_bridge
  image_transport
  roscpp
  sensor_msgs
  message_filters
)
find_package(Protobuf REQUIRED)
find_package(OpenCV REQUIRED)


set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})  
set(IMAGE_PATH ${SOURCE_DIR}/images)  

# 将变量传递给 C++ 代码
configure_file(${SOURCE_DIR}/include/config.h.in ${SOURCE_DIR}/include/config.h)


## ros生成可执行文件
catkin_package()

include_directories(
  ./include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)
link_directories(
  ./lib
)
set(LIB_PROTOBUF protobuf pthread)
set(LIB_SYS dl)
set(LIB_MOD txsim-module-service)

# protobuf_generate_cpp(PROTO_SRC_IMG PROTO_HDR_IMG msgs/image.proto)
# protobuf_generate_cpp(PROTO_SRC_RAW PROTO_HDR_RAW msgs/sensor_raw.proto)

message("camke binary " ${PROJECT_BINARY_DIR})
add_executable(camera_node
  src/CameraFun.cc
  src/main.cc
  src/sensor_raw.pb.cc)

target_link_libraries(camera_node
  ${LIB_PROTOBUF}
  ${LIB_SYS}
  ${LIB_MOD}
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
  rt) 

target_compile_definitions(camera_node PRIVATE TXSIM_NO_EXPORTS)

# add_library(CameraIO
#   src/CameraFun.cc
#   src/MemoryIO.cc
#   src/main.cc
#   )

# target_link_libraries(CameraIO
#   ${LIB_PROTOBUF}
#   ${LIB_SYS}
#   ${LIB_MOD}
#   ${OpenCV_LIBS}
#   ${catkin_LIBRARIES}
#   rt) 

# install(TARGETS CameraIO
#   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
# )

