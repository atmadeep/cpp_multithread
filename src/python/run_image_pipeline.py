import time
from pynput.keyboard import Key, Controller
import image_pipeline

count = 0
# Total number of times caps lock key should blink
blink_count = 2

def caps_control():
    keyboard = Controller()
    time.sleep(0.1)
    keyboard.press(Key.caps_lock)
    keyboard.release(Key.caps_lock)

def main():
    caps_control()
    image_pipeline.pipeline_func()

if __name__ == "__main__":
    main()