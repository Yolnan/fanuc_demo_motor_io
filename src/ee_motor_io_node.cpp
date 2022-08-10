#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>

int main(int argc, char* argv[])
{
    // Initialize Node
    ros::init(argc, argv, "motor_io_node");

    // Create a ROS node handle
    ros::NodeHandle nh;

    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener listener(buffer);
    const std::string target_frame = "base_link";
    const std::string source_frame = "sand_tcp";
    // const ros::Time time;
    // const ros::Duration timeout 
    ros::Rate loop_rate(10);
    geometry_msgs::TransformStamped tf;

    while (ros::ok())
    {   
        try 
        {
            tf = buffer.lookupTransform(target_frame, source_frame, ros::Time(0), ros::Duration(1.0));
            ROS_INFO_STREAM("z height: " << tf.transform.translation.z );
            ros::spinOnce();
            loop_rate.sleep();  
        } 
        catch (tf2::LookupException)
        {
            ROS_WARN_STREAM("tf2 LookupException");
        }
    }
       
}