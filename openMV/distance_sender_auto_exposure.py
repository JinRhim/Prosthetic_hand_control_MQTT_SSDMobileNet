"""
Install MQTT network in your computer.
OpenMV H7 and Laptop must be connected to same WIFI




Use below code to turn on local mosquito server:

/usr/local/opt/mosquitto/sbin/mosquitto -c /usr/local/etc/mosquitto/mosquitto.conf


Turn on another terminal, and type this command:

mosquitto_sub -h test.mosquitto.org -t "openmv/test" -v

"""




import sensor, image, time, os, tf, math, uos, gc
import network
from mqtt import MQTTClient

#SSID='MICLab' # Network SSID
#KEY='miclabedu2021'  # Network key

SSID='ICELab'
KEY='ICELab_Zhang'

SCREEN_SIZE = [128, 128]

sensor.reset()                         # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565)    # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.B128X128)      # Set frame size to QVGA (320x240)
# default is turned on. It will automatically lower the brightness if the screen is static
sensor.set_auto_exposure(False, 1)
sensor.set_framerate(5)


#sensor.set_framesize(sensor.QQVGA)      # Set frame size to QVGA (320x240)

#sensor.set_framesize(sensor.QQVGA2) # Special 128x160 framesize for LCD Shield.
sensor.skip_frames(time=2000)          # Let the camera adjust.
sensor.set_framebuffers(sensor.SINGLE_BUFFER)
# OpenMV Cam will allocate one frame buffer for receiving images.
# Boost FPS

net = None
labels = None
min_confidence = 0.4

try:
    # Load built in model
    labels, net = tf.load_builtin_model('trained')
except Exception as e:
    raise Exception(e)

colors = [
    (0,     0,   0),   # background
    (255,   0,   0),  # apple
    (  0, 255,   0),  # hand
    (0, 0, 255),       # Line
]

clock = time.clock()

# Connect to MQTTClient ==========================================================================
# Init wlan module and connect to network
print("Trying to connect to MQTT Client Terminal... (may take a while)...")
#
wlan = network.WINC()
wlan.connect(SSID, key=KEY, security=wlan.WPA_PSK)
#
client = MQTTClient("openmv", "test.mosquitto.org", port=1883)
# client.connect()
print("Connected to the client: (macbook) : ", wlan.ifconfig())
#
# ================================================================================================


hand_coord_x = 0
hand_coord_y = 0
apple_coord_x = 0
apple_coord_y = 0
counter = 0

while(True):
    print("===================Beginning of while loop================")

    clock.tick()

    img = sensor.snapshot()

    # detect() returns all objects found in the image (splitted out per class already)
    # we skip class index 0, as that is the background, and then draw circles of the center
    # of our objects

    for i, detection_list in enumerate(net.detect(img, thresholds=[(math.ceil(min_confidence * 255), 255)])):
        if (i == 0 or len(detection_list) == 0):
            counter+= 1
            if (counter > 3):
                apple_coord_x = 0
                apple_coord_y = 0
                hand_coord_x = 0
                hand_coord_y = 0
                counter = 0
                print('Coordinate reset')
        elif (i == 1):
                print("object detected: ", labels[i])
                for d in detection_list[:1]:
                    [x, y, w, h] = d.rect()
                    center_x = math.floor(x + (w / 2))
                    center_y = math.floor(y + (h / 2))
                    apple_coord_x = center_x
                    apple_coord_y = center_y
                    print('Apple Coordinate:  x: %d\ty: %d' % (center_x, center_y))
                    img.draw_circle((center_x, center_y, 3), color=colors[i], thickness=10)
        elif (i == 2):
                print("object detected: ", labels[i])
                for d in detection_list[:1]:
                    [x, y, w, h] = d.rect()
                    center_x = math.floor(x + (w / 2))
                    center_y = math.floor(y + (h / 2))
                    hand_coord_x = center_x
                    hand_coord_y = center_y
                    print('Hand Coordinate: x %d\ty %d' % (center_x, center_y))
                    img.draw_circle((center_x, center_y, 3), color=colors[i], thickness=10)
        else:
            print("i out of range:", i)

    # End of for loop

    dist=int(math.sqrt((apple_coord_x - hand_coord_x)**2 + (apple_coord_y - hand_coord_y)**2))
    # if distance less than 80, true
    print("distance: ", dist)
    print(f'4 coordinates: {apple_coord_x}, {apple_coord_y}, {hand_coord_x}, {hand_coord_y}')

    if (apple_coord_x != 0 and hand_coord_x != 0 ): # if bot coordinates are valid, draw the line
        img.draw_line((apple_coord_x, apple_coord_y,hand_coord_x, hand_coord_y), (0, 0, 255), thickness = 3)

    if(dist < 40 and dist > 1):
        img.draw_string(0, SCREEN_SIZE[1]-20, "Grab", color=(255, 255, 0), scale = 1)
        print("Grabbing..")

    else:
        img.draw_string(0, SCREEN_SIZE[1]-10, "release", color=(0, 255, 255), scale = 1)
        print("Releasing..")

    # SEND MQTT MSG ====================================================
    if (dist != 0):
        img.draw_string(SCREEN_SIZE[0]-50, SCREEN_SIZE[1]-10, str(dist), color=(255, 0, 255), scale = 1)
        try:
            client.connect()
            client.publish("openmv/test", str(dist))
            client.disconnect()
        except Exception as e:
            print("Failed to connect MQTT Error: ", e)


    print(clock.fps(), "fps", end="\n")
