#include "servoControl.h"

#define flexing_thumb 180 
#define flexing_index 180
#define flexing_pinky 180

#define clenching_thumb 60
#define clenching_index 0
#define clenching_pinky 0

#define half_clenching_thumb 120
#define half_clenching_index 90
#define half_clenching_pinky 90


void servoControl::attachServos() {
  myservo_thumb.attach(15);  // attaches the servo on pin GPIO 15 to the servo object
  myservo_index.attach(2); 
  myservo_pinky.attach(4); 
}

void servoControl::grab()
{
    myservo_thumb.write(clenching_thumb);
    myservo_index.write(clenching_index);
    myservo_pinky.write(clenching_pinky);
}

void servoControl::rest()
{
    myservo_thumb.write(flexing_thumb);
    myservo_index.write(flexing_index);
    myservo_pinky.write(flexing_pinky);
}

void servoControl::pinch()
{
    myservo_thumb.write(clenching_thumb);
    myservo_index.write(clenching_index);
    myservo_pinky.write(flexing_pinky);
}

void servoControl::half_clench()
{
    myservo_thumb.write(half_clenching_thumb);
    myservo_index.write(half_clenching_index);
    myservo_pinky.write(half_clenching_pinky);
}
