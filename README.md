# Demo 
![image](https://github.com/JinRhim/Prosthetic_hand_control_MQTT_SSDMobileNet/assets/93160540/b86a5f25-ff27-47cd-916b-64861b0105a2)

### Youtube Video 
[![Watch the video](https://img.youtube.com/vi/K1PvsZXECzM/0.jpg)](https://www.youtube.com/watch?v=K1PvsZXECzM)

<div style="display: flex; justify-content: space-between;">
  <img src="gif/autobrightness_adjusted_v1.gif" alt="Alt Text" width="250" height="250">
  <img src="gif/openmv_camera_1.gif" alt="Alt Text" width="250" height="250">
  <img src="gif/openmv_laptop_image_1.gif" alt="Alt Text" width="250" height="250">
</div>
<div style="display: flex; justify-content: space-between;">
  <img src="gif/openmvide_v1.gif" alt="Alt Text" width="250" height="250">
  <img src="gif/skewed_angle.gif" alt="Alt Text" width="250" height="250">
  <img src="gif/demo_v3.gif" alt="Alt Text" width="250" height="250">
</div>

### OpenMV IDE
<div style="display: flex; justify-content: space-between;">
  <img src="gif/autobrightness_adjusted_fullscreen.gif" alt="Alt Text" width="650" height="400">
  <img src="gif/autobrightness_adjusted_fullscreen_v2.gif" alt="Alt Text" width="650" height="400">
</div>

## EMG Sensor 
<div>
    <img src="https://github.com/JinRhim/Prosthetic_hand_control_MQTT_SSDMobileNet/assets/93160540/ed164638-3cb3-4249-92a0-e89609df2579" alt="Image 1" width="300" height="250">
    <img src="https://github.com/JinRhim/Prosthetic_hand_control_MQTT_SSDMobileNet/assets/93160540/090ed69c-f359-4cc0-bc3e-3802f43bf522" alt="Image 2" width="400" height="250">
</div>



<div style="display: flex; justify-content: space-between;">
  <img src="gif/emg_filter.gif" alt="Alt Text" width="650" height="400">
  <img src="gif/emg_7:11_3.gif" alt="Alt Text" width="650" height="400">
  <img src="gif/emg_7:11_4.gif" alt="Alt Text" width="650" height="400">
</div>


## How to install
1. Install OpenMV H7 WiFi Shield (The middle one is WIFI shield)

![제목](https://github.com/JinRhim/Prosthetic_hand_control_MQTT_SSDMobileNet/assets/93160540/56ad801f-3975-47ab-8180-b0c3d9950d4b)

2. Go to OpenMV IDE --> Tools --> Run Bootloader(Load Firmware) --> select edge_impulse_firmware_openmv_cam_h7.bin

![image](https://github.com/JinRhim/Prosthetic_hand_control_MQTT_SSDMobileNet/assets/93160540/e6981d82-9dd0-4bbe-8cf2-b13b7d55259c) 

3. Open distance_sender_auto_exposure.py --> tools --> save script to OpenMV Cam. Now the script is saved to OpenMV H7 so you can use external battery. Change SSID and PASSWORD as wifi ID and password

![image](https://github.com/JinRhim/Prosthetic_hand_control_MQTT_SSDMobileNet/assets/93160540/eb6586d9-5f41-4746-bf5d-4e478c7ea752)

4. Connect ESP32 and  flash the Arduino Code. (Select ESP32_WROOM_DA)
5. Open the MQTT Server  
- use below code to turn on local mosquito server: 
```
brew install mosquitto
/usr/local/opt/mosquitto/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf
```
- To check message sent, type the below code: 
```
mosquitto_sub -h test.mosquitto.org -t "openmv/test" -v
```

- The terminal should receive the distance in integer
```
OpenMV/test 70
OpenMV/test 69
OpenMV/test 69
...
```

6. Connect LiPO Battery to OpenMV. If OpenMV does not turn on, probably the + and - is flipped.


# Update 

#### Slides: https://docs.google.com/presentation/d/1eCgFYzyATt7UYBIcP0_li7qxv4ZbzFE2mWxo04YrdAs/edit?usp=sharing
#### Boards are designed by EAGLE 
#### Additional Documentation: https://jin-gitbook.gitbook.io/engineering-101/readme/how-to-make-ml-dataset-using-microsoft-vott


<div style="display: flex; justify-content: space-between;">
  <img src="gif/OYMotion_AD2_flexing1.gif" alt="OYMotion AD2 Flexing 1" width="500" height="300">
  <img src="gif/OYMotion_AD2_flexing2.gif" alt="OYMotion AD2 Flexing 2" width="500" height="300">
</div>
<div style="display: flex; justify-content: space-between;">
  <img src="gif/OYMotion_AD2_flexing4.gif" alt="OYMotion AD2 Flexing 4" width="450" height="300">
  <img src="gif/OYMotion_AD2_touching_table.gif" alt="OYMotion AD2 Touching Table" width="450" height="300">
</div>
<div style="display: flex; justify-content: space-between;">
  <img src="gif/OYMotion_threshold_system.gif" alt="OYMotion Threshold System" width="400" height="300">
  <img src="gif/OYMotion_threshold_system_2.gif" alt="OYMotion Threshold System 2" width="400" height="300">
</div>
<div style="display: flex; justify-content: space-between;">
  <img src="gif/coral_distance_1.gif" alt="Coral Distance 1" width="350" height="350">
  <img src="gif/coral_distance_2.gif" alt="Coral Distance 2" width="350" height="350">
  <img src="gif/coral_extension_board_uart.gif" alt="Coral Extension Board UART" width="700" height="400">
</div>
<div style="display: flex; justify-content: space-between;">
  <img src="gif/esp32_mainboard_v1.gif" alt="ESP32 Mainboard V1" width="500" height="300">
  <img src="gif/esp32_receiver_board.gif" alt="ESP32 Receiver Board" width="500" height="300">
</div>
<div style="display: flex; justify-content: space-between;">
  <img src="gif/esp32_mainboard_emg_test.gif" alt="ESP32 Mainboard EMG Test" width="800" height="600">
</div>
