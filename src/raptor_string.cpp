#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

class RaptorString {
  public:
    RaptorString();
    
  private:
    void raptorInCallback(const std_msgs::String::ConstPtr& receivedMsg);
    ros::Publisher pub;
    ros::Subscriber sub;
};

RaptorString::RaptorString() {
  ros::NodeHandle n;
  pub = n.advertise<std_msgs::String>("RaptorOUT", 1000);
  sub = n.subscribe("RaptorIN", 1000, &RaptorString::raptorInCallback, this);
}

void RaptorString::raptorInCallback(const std_msgs::String::ConstPtr& receivedMsg)
{
  ROS_INFO("I received: [%s]", receivedMsg->data.c_str());
  
  std_msgs::String newMsg;
  
  std::stringstream ss;
  ss << receivedMsg->data.c_str() << " Bartosz Mazurkiewicz " << ros::Time::now();
  
  newMsg.data = ss.str();
  
  pub.publish(newMsg);
  
  ROS_INFO("I published: [%s]", newMsg.data.c_str());
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "raptor_string");
  
  RaptorString raptorString;
  
  ros::spin();

  return 0;
}
