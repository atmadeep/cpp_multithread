import time
import cProfile
import pstats
from pynput.keyboard import Key, Controller
import image_pipeline
from argparse import ArgumentParser

def parse_arguments():
    parser = ArgumentParser()
    parser.add_argument("-p", "--profile", type=int, default=0, help="Profile the functions#")
    args = parser.parse_args()
    return args

count = 0
# Total number of times caps lock key should blink
blink_count = 2

def caps_control():
    keyboard = Controller()
    time.sleep(0.1)
    keyboard.press(Key.caps_lock)
    keyboard.release(Key.caps_lock)

def main():
    args = parse_arguments()
    if(args.profile):
        cProfile.run("caps_control()", "caps_control_stats")
        p1 = pstats.Stats("caps_control_stats")
        p1.sort_stats("cumulative").print_stats(5)
        time.sleep(1)
        cProfile.run("image_pipeline.pipeline_func()", "image_pipeline_stats")
        p2 = pstats.Stats("image_pipeline_stats")
        p2.sort_stats("cumulative").print_stats(5)
    else:
        caps_control()
        image_pipeline.pipeline_func()

if __name__ == "__main__":
    main()