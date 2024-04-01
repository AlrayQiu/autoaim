#include <cv_bridge/cv_bridge.h>
#include <iostream>
#include <opencv4/opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp/utilities.hpp>
#include <sensor_msgs/msg/image.hpp>

class ImgTransport : public rclcpp::Node {
public:
  ImgTransport() : rclcpp::Node("test") {
    img_sub_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image", 10,
        std::bind(&ImgTransport::ImageRecieve_callback, this,
                  std::placeholders::_1));
  }

private:
  void
  ImageRecieve_callback(const sensor_msgs::msg::Image::SharedPtr msg) const {
    cv_bridge::CvImageConstPtr ptr =
        cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8);
    cv::imshow("ros2", ptr->image);

    std::cout << "image get" << std::endl;
  }
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;
};
int main(int argc, char **argv) {
  std::cout << "init success" << std::endl;

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImgTransport>());
  rclcpp::shutdown();

  return 0;
}
