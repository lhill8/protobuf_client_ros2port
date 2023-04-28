#!/usr/bin/env python3

# Test app to publish test data to gateway


import rospy
from protobuf_client.msg import Gateway

pub_x = rospy.Publisher('/send_to_gateway', Gateway, queue_size=10)
pub_y = rospy.Publisher('/send_to_gateway', Gateway, queue_size=10)

#def gateway_cb(msg)

def main():
    rospy.init_node('send_to_gateway')
    rate = rospy.Rate(10) # 10 hz
    # create subscribers to different callbacks, based on data type and need
    #rospy.Subscriber('/some_msg_to_parse', Type, gateway_cb)
    # Just publish something quick to the topic for testing moos gateway receive
    nav_x = Gateway()
    nav_x.header.stamp = rospy.Time.now()
    nav_x.gateway_time = rospy.Time.now()
    nav_x.gateway_key = 'NAV_X'
    nav_x.gateway_double = 0.0
    

    nav_y = Gateway()
    nav_y.header.stamp = rospy.Time.now()
    nav_y.gateway_time = rospy.Time.now()
    nav_y.gateway_key = "NAV_Y"
    nav_y.gateway_double = 0.0

    

    while not rospy.is_shutdown():
        pub_x.publish(nav_x)
        pub_y.publish(nav_y)
        #rospy.spin()
        rate.sleep()

try:
    main()
except rospy.ROSInterruptException:
    pass
