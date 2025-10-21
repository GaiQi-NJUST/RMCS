#include <rclcpp/node.hpp>
#include <rclcpp/logging.hpp>
#include <rmcs_executor/component.hpp>
#include <cmath>
#include <chrono>
using namespace std;

namespace rmcs_core::controller::communication {

class Input
    : public rmcs_executor::Component
    , public rclcpp::Node {
public:
    Input()
        : Node(
              get_component_name(),
              rclcpp::NodeOptions{}.automatically_declare_parameters_from_overrides(true))
        , start_time_(this->now())  // record start time
    {
        register_input(get_parameter("name_sine").as_string(), sine_value_);
        register_input(get_parameter("name_cosine").as_string(), cosine_value_);

        register_output(get_parameter("name_sum").as_string(), sum_value_);
    }

    void update() override {
        
        auto current_time = this->now() - start_time_;
        double t = current_time.seconds();
        
        double sin_val = *sine_value_;
        double cos_val = *cosine_value_;
        double sum_val = sin_val + cos_val;
        
        RCLCPP_INFO(this->get_logger(), 
                   "t=%.3f: sin=%.3f, cos=%.3f, sum=%.3f",
                   t, sin_val, cos_val, sum_val);
    }

private:              
    rclcpp::Time start_time_; 
               
    InputInterface<double> sine_value_; 
    InputInterface<double> cosine_value_;

    OutputInterface<double> sum_value_; 
};

}  // namespace rmcs_core::controller::communication

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS(rmcs_core::controller::communication::Input, rmcs_executor::Component)