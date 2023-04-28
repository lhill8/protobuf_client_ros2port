// 2022-11-09
// Author: Michael DeFilippo (mikedef@mit.edu), AUV Lab
// License: MIT

#include "protobuf_client.h"

int main(int argc, char **argv)
{
rclcpp::init(argc, argv, __APP_NAME__);

  ProtobufClient app;

  app.Run();

  return 0;
}
