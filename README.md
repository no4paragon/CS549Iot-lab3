# Lab 2: **Highway Traffic Light**

<p align="center">Your task is to build a simplified traffic light (TL) controller using the ESP32 board and the provided set of sensors.
  The TL comprises three LEDs, a buzzer, and a touch button.</p>

<h2>Problem description:</h2>

- The TL goes from green through yellow to red, and from red through red-yellow to green. The TL remains in red for 10 seconds.
- The TL remains in yellow and red-yellow for 2 seconds.
- The TL has a touch button for pedestrians, it remains in green until the pedestrian button is pressed. The TL remains in green at least 5 seconds after the touch button has become active.
- The TL has a buzzer for visual impairment aid with two modes. When in green the buzzer must be 500 ms on and 1500 ms off; when in red the buzzer must be 250 ms on and 250 ms off. (NOTE: You can put a fingertip on the top of the buzzer to reduce the sound volume)


<h2>[Youtube lab2 video link](https://youtu.be/un2tvMwML1s)</h2>

<img src="https://github.com/no4paragon/CS549Iot-lab2/blob/main/Photo%20Mar%2009%202023%2C%2000%2035%2042.jpg" width="60%" height="60%">
<img src="https://github.com/no4paragon/CS549Iot-lab2/blob/main/Photo%20Mar%2009%202023%2C%2000%2035%2051.jpg" width="60%" height="60%">
<img src="https://github.com/no4paragon/CS549Iot-lab2/blob/main/Photo%20Mar%2009%202023%2C%2000%2036%2001.jpg" width="60%" height="60%">
