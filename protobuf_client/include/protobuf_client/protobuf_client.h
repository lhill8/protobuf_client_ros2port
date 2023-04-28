#ifndef PROTOBUF_CLIENT_H
#define PROTOBUF_CLIENT_H
#define __APP_NAME__ "protobuf_client"

// ROS includes
//#include <ros/ros.h>                                                                                    
//#include <ros/console.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/String.h>
#include <std_msgs/Float64.h>
#include "protobuf_client/Gateway.h"
// Protobuf
#include "gateway.pb.h"
// Gateway Includes
#include "tcp_client.h"

class ProtobufClient
{
  ros::NodeHandle nh_;
  ros::Publisher pub_gateway_msg_;
  ros::Subscriber sub_to_gateway_;
  int gateway_port_;
  std::string gateway_ip_;
  std::string send_to_gateway_;
  boost::asio::io_service io_;
  std::shared_ptr<gateway::tcp_client> client_{gateway::tcp_client::create(io_)};
  
  void ToGatewayCallback(const protobuf_client::Gateway &msg);
  /** 
   * @brief callback to subscribe to client ros gateway msgs and post to MOOSDB
   * @param[in] msg
   **/

  void ConnectToGateway();
  /**
   * @brief Connect to the MOOSDB through TCP 
   **/

  void IngestGatewayMsg();
  /**
   * @brief Ingests msg from gateway and publishes as a custom Gateway ROS msg
   **/

  void Iterate();
  /**
   * @brief Loop continuously through the Iterate function at the desired rate
   **/

  void InitRosIO(ros::NodeHandle &in_private_nh);
  /**
   * @brief callback to inititialize parameters 
   * @param[in] in_private_nh
   **/

  
  
 public:
  void Run();
 ProtobufClient();
  virtual ~ProtobufClient();
};

#endif // PROTOBUF_CLIENT_H
