from multiprocessing import Process
import time
import image_pipeline
from pynput.keyboard import Key, Controller


keyboard = Controller()


def key_press():
    global keyboard
    keyboard.press(Key.caps_lock)
    time.sleep(0.5)
    keyboard.release(Key.caps_lock)
    time.sleep(0.5)


def key_depress():
    keyboard.release(Key.caps_lock)
    time.sleep(0.5)
    keyboard.press(Key.caps_lock)
    time.sleep(0.5)


def blink_key():
    i = 0
    while i < 2:
        print(f"pressed caps lock {i} times")
        key_press()
        key_depress()
        i += 1


def driver_func():
    p1 = Process(target=blink_key)
    p1.start()
    p2 = Process(target=image_pipeline.pipeline_func)
    p2.start()
    p1.join()
    p2.join()


def print_memory_info(mem_info):
    print(f"Resident Set Size (RSS): {mem_info.rss / (1024 ** 2):.2f} MB")
    print(f"Virtual Memory Size (VMS): {mem_info.vms / (1024 ** 2):.2f} MB")
    print(f"Shared Memory: {mem_info.shared / (1024 ** 2):.2f} MB")
    print(f"Text (Code) Memory: {mem_info.text / (1024 ** 2):.2f} MB")
    print(f"Data Memory: {mem_info.data / (1024 ** 2):.2f} MB")
    print(f"Unique Set Size (USS): {mem_info.uss / (1024 ** 2):.2f} MB")
    print(f"Proportional Set Size (PSS): {mem_info.pss / (1024 ** 2):.2f} MB")
    print(f"Swap: {mem_info.swap / (1024 ** 2):.2f} MB")
