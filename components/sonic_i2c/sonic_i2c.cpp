#include"sonic_i2c.h"
#include"esphome/core/log.h"

namespace esphome{
static const char * TAG = "sonic_i2c" ;
//static SONIC_I2C sensor ;
namespace sonic_i2c_sensor{

void SonicI2C::dump_config() {
  LOG_SENSOR(TAG, "Ultrasonic Sensor", this);
  ESP_LOGD(TAG , "Ultrasonic Sensor I2C Address :  %x", this->address_);
  LOG_UPDATE_INTERVAL(this);
}


float SonicI2C::getDistance(){
    uint32_t data;
    uint8_t val = 0x01 ;
    this->write( &val, 1);
    
    delay(120);
    uint8_t data_buffer[]={0,0,0,0,0};
    
    this->read(data_buffer,3);
    data = data_buffer[0]<< 16 | data_buffer[1]<< 8 | data_buffer[2];
    float Distance = float(data) / 1000;
    if (Distance > 4500.00) {
        return 4500.00;
    } else {
        return Distance;
    }
  return  0 ;
}

float SonicI2C::getLiters() {
    float radius = 10.0; // Replace with the actual radius value
    float tank_height = 110;
    float distance_mm = getDistance(); // Assuming getDistance returns distance in millimeters

    // Convert distance to volume in liters using the formula: pie * R^2 * L
    float volume_liters = 3.141592653589793 * radius * radius * distance_mm / 1000.0; // Convert from mm^3 to liters

    return volume_liters;
}

void SonicI2C::setup(){
    // Init the sensor 
    ESP_LOGI(TAG, "Ultrasonic Sensor Setup begin");
    
}


void SonicI2C::update() {
   
    float result = this->getLiters();   
    float result2 =  this->getDistance();
    //float resultLiters = this->getLiters();
    //if(result2>=4500|| result<=20)
    //{
            ESP_LOGI(TAG, "Incorrect Liters Reading - Litres");
    //     }else{
            ESP_LOGD(TAG, "%s - Got Liters: %.2f Lts", this->name_.c_str(), result);
            ESP_LOGD(TAG, "%s - Got Distance: %.2f Lts", this->name_.c_str(), result2);
            //ESP_LOGD(TAG, "%s - Got distance: %.2f mm", this->name_.c_str(), result , resultLiters);
            //ESP_LOGD(TAG, "%s - Got di %.2f mm, %.2f liters", this->name_.c_str(), result, resultLiters);

           
      //}
    
    publish_state(result2);
  
}

}

}
