#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <std_msgs/Bool.h>

int main(int argc, char* argv[])
{
    // Initialize Node
    ros::init(argc, argv, "motor_io_node");

    // Create a ROS node handle
    ros::NodeHandle nh;
    // Create tf2 objects
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    const std::string target_frame = "base_link";
    const std::string source_frame = "sand_tcp";
    ros::Rate loop_rate(10);
    geometry_msgs::TransformStamped tf;
    // Create Publisher
    ros::Publisher turnOnMotor_pub = nh.advertise<std_msgs::Bool>("/ee_motor_on", 10);
    std_msgs::Bool turnOnMotor;
    turnOnMotor.data = false;

    while (ros::ok())
    {   
        try 
        {
            tf = buffer.lookupTransform(target_frame, source_frame, ros::Time(0), ros::Duration(1.0));
            ROS_INFO_STREAM("z height: " << tf.transform.translation.z );
            if (tf.transform.translation.z > 1.0) 
            {
                turnOnMotor.data = true;
            } else {
                turnOnMotor.data = false;
            }
            turnOnMotor_pub.publish(turnOnMotor);
            ros::spinOnce();
            loop_rate.sleep();  
        } 
        catch (tf2::LookupException)
        {
            ROS_WARN_STREAM("tf2 LookupException");
        }
    }
       
}