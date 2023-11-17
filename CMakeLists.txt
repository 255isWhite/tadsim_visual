cmake_minimum_required(VERSION 3.15)
project(tadsim_visual)
add_compile_options(-std=c++14)

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

protobuf_generate_cpp(PROTO_SRC_BASIC PROTO_HDR_BASIC msgs/basic.proto)
protobuf_generate_cpp(PROTO_SRC_LOC PROTO_HDR_LOC msgs/location.proto)
protobuf_generate_cpp(PROTO_SRC_TFC PROTO_HDR_TFC msgs/traffic.proto)
protobuf_generate_cpp(PROTO_SRC_TRJ PROTO_HDR_TRJ msgs/trajectory.proto)

message("camke binary " ${PROJECT_BINARY_DIR})
add_executable(camera_node
  src/CameraFun.cc
  src/MemoryIO.cc
  src/main.cc)

target_link_libraries(camera_node
  ${LIB_PROTOBUF}
  ${LIB_SYS}
  ${LIB_MOD}
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
  rt) 

target_compile_definitions(camera_node PRIVATE TXSIM_NO_EXPORTS)

add_library(CameraIO
  src/CameraFun.cc
  src/MemoryIO.cc
  src/main.cc)

target_link_libraries(CameraIO
  ${LIB_PROTOBUF}
  ${LIB_SYS}
  ${LIB_MOD}
  ${OpenCV_LIBS}
  ${catkin_LIBRARIES}
  rt) 

install(TARGETS CameraIO
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

