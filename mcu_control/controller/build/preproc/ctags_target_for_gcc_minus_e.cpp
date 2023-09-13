# 1 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino"
# 2 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino" 2
# 3 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino" 2
# 4 "C:\\Users\\victo\\Documents\\GitRepos\\BLDCMiniVehicle\\mcu_control\\controller\\controller.ino" 2

void _i2c_callback(){

}

void setup(){
 const char* TAG = "SETUP";
 do {} while(0);
 do {} while(0);

 // Initializing Pins Direction
 do {} while(0);
 pinMode(2, 0x03); // Built-in LED
 do {} while(0);
 pinMode(15, 0x03); // Controller Board On/Off Relay
 do {} while(0);

 // Intializing onboard WiFi
 wifi_start();

 // Intializing WebServer
 web_server_start();

 // Initializing I²C Bus
 // I²C Configuration -> Slave Addr = 0x52 / SDA = 21 / SCL = 22 / Clock = 100kHz
 Wire.begin(0x52, 21, 22, 100000);
 Wire.onRequest(_i2c_callback);
 do {} while(0);
 do {} while(0);
}

void loop(){

}
