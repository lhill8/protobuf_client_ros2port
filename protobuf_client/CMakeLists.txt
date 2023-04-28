cmake_minimum_required(VERSION 3.5)
project(protobuf_client)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

#add_compile_options(-std=c++14)
set(CMAKE_CXX_STANDARD 14) 

## Find catkin and any catkin packages
#find_package(catkin REQUIRED COMPONENTS
#		    roscpp
#		    std_msgs
#		    genmsg
#		    rospy
#		    )

find_package(ament_cmake REQUIRED)
find_package(ament_cmake_python REQUIRED)
find_package(rclcpp REQUIRED)
find_package(protobuf_messages REQUIRED)
find_package(rclpy REQUIRED)

#find_package(rosidl_default_generators REQUIRED)


## System dependencies are found with CMake's conventions                                               
find_package(Boost REQUIRED COMPONENTS system)
find_package(Protobuf REQUIRED)                                                                    


message("libprotobuf >= 2.5.0")                                                                       
set(PROTOBUF_ALLOW_ALIAS "option allow_alias = true;")
set(Protobuf_INCLUDE_DIRS include/protobuf_client)
#set(protobuf_messages_DIR ../protobuf_messages)

## Generate messages in the 'msg' folder
#add_message_files(
#  FILES
#  Gateway.msg
#  )

#find_package(message_package REQUIRED)
find_package(protobuf_messages REQUIRED)


## Generate added messages and services
#rosidl_generate_interfaces(DEPENDENCIES std_msgs)

## Declare a catkin package
#catkin_package()

## Build 
include_directories(include include/protobuf_client include/lib_gateway_tcp
			    #${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS}
				rclcpp ${Boost_INCLUDE_DIRS} ${PROTOBUF_INCLUDE_DIRS})
# lib/proto is a directory to store the raw gateway.proto msg
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS include/protobuf_client/ lib/proto/gateway.proto)
# NOTE: need to fix proto generation so it builds to correct directory
# Had to copy in the .pb.h .pb.c files into my include from build/protobuf_client/ 



add_library(gateway_protobuf include/protobuf_client/gateway.pb.cc)
add_library(gateway_tcp
	lib/lib_gateway_tcp/tcp_client.cpp
	lib/lib_gateway_tcp/tcp_server.cpp
	lib/lib_gateway_tcp/tcp_session.cpp
	include/lib_gateway_tcp/tcp_client.h
	include/lib_gateway_tcp/tcp_server.h
	include/lib_gateway_tcp/tcp_session.h
	)



target_link_libraries(gateway_tcp ${Boost_LIBRARIES}
				  rclcpp
				  ${PROTOBUF_LIBRARY}
				  ${B64_LIBRARIES})

add_executable(protobuf_client
  nodes/protobuf_client.cpp
  nodes/protobuf_client_node.cpp)

#target_include_directories(protobuf_client
#  PUBLIC
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:include>)
  
#target_link_libraries(protobuf_client ${catkin_LIBRARIES}
#				      gateway_protobuf
#				      ${PROTOBUF_LIBRARY}
#				      gateway_tcp
#				      )  # ${Boost_LIBRARIES}
#target_link_libraries(protobuf_client
ament_target_dependencies(protobuf_client
					  rclcpp
					  #protobuf_messages
					  std_msgs
					  rclpy
				      #gateway_protobuf
				      ${PROTOBUF_LIBRARY}
				      gateway_tcp
				      )



#catkin_install_python(PROGRAMS scripts/publish_to_gateway.py
ament_python_install_package(${PROJECT_NAME})
install(PROGRAMS 
	scripts/publish_to_gateway.py
    #DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
  	DESTINATION lib/${PROJECT_NAME}
)

ament_package()
