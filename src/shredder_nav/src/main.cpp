#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/String.h>
#include <ctime>

ros::Publisher goal_pub;

void callback (const std_msgs::String::ConstPtr& strmsg) {
    ROS_INFO("<%s",strmsg->data.c_str());

    geometry_msgs::PoseStamped msg;
    msg.header.seq = 1;
    msg.header.stamp = ros::Time::now();
    msg.header.frame_id = "map";

    msg.pose.position.x = 0.7;
    msg.pose.position.y = 0.7;

    msg.pose.orientation.x = 0;
    msg.pose.orientation.y = 0;
    msg.pose.orientation.z = 1;
    msg.pose.orientation.w = 0;

    goal_pub.publish(msg);
}

int main(int argc, char** argv) {
    ros::init(argc,argv,"shredder_nav");
    ros::NodeHandle n;

    ROS_INFO("advertising");
    goal_pub = n.advertise<geometry_msgs::PoseStamped>("move_base_simple/goal",100);
    ROS_INFO("dummy");
    ros::Publisher dummy = n.advertise<std_msgs::String>("shredder_nav/cmd",10);
    ROS_INFO("subscribing");
    ros::Subscriber cmd_sub = n.subscribe("/shredder_nav/cmd",10,callback);
    ROS_INFO("spinning");
    ros::spin();
    return 0;
}
