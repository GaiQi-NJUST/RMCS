#include <rclcpp/node.hpp>
#include <rmcs_executor/component.hpp>
#include <cmath>
#include <chrono>
using namespace std;
namespace rmcs_core::controller::communication {

class Output
    : public rmcs_executor::Component
    , public rclcpp::Node {
public:
    Output()
        : Node(
              get_component_name(),
              rclcpp::NodeOptions{}.automatically_declare_parameters_from_overrides(true))
        , start_time_(this->now())  // record start time
    {
        omega_ = this->get_parameter("omega").as_double();
        register_output( get_parameter("name_sine").as_string(), sine_value_);
        register_output( get_parameter("name_cosine").as_string(), cosine_value_);
    }

    void update() override {
        
        auto current_time = this->now() - start_time_;
        double t = current_time.seconds();
        
        *sine_value_ = sin(omega_ * t);
        *cosine_value_ = cos(omega_ * t);
    }

private:
    double omega_;                  
    rclcpp::Time start_time_;            
    OutputInterface<double> sine_value_; 
    OutputInterface<double> cosine_value_;
};

}  // namespace rmcs_core::controller::communication

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(rmcs_core::controller::communication::Output, rmcs_executor::Component)