#include <cv_bridge/cv_bridge.h>
#include <opencv4/opencv2/opencv.hpp>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>

class ImgTransport : public rclcpp::Node {
public:
  ImgTransport() : rclcpp::Node("test") {
    this->create_subscription<sensor_msgs::msg::Image>(
        "/image", 1,
        std::bind(&ImgTransport::ImageRecieve_callback, this,
                  std::placeholders::_1));
  }

private:
  void
  ImageRecieve_callback(const sensor_msgs::msg::Image::SharedPtr msg) const {
    std::cout << "yes" << std::endl;
    cv_bridge::CvImageConstPtr ptr =
        cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8);
    cv::imshow("ros2", ptr->image);
  }
  rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr img_sub_;
};
int main(int argc, char **argv) {

  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ImgTransport>());

  return 0;
}
