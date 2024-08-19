import cProfile
from argparse import ArgumentParser
import os
import psutil
from utils import *
import time


def parse_arguments():
    parser = ArgumentParser()
    parser.add_argument(
        "-p", "--profile", type=int, default=0, help="Profile the functions#"
    )
    args = parser.parse_args()
    return args


def main(args):
    if args.profile == 1:
        cProfile.run("driver_func()", "profile_output.pstats")
    else:
        driver_func()


if __name__ == "__main__":
    args = parse_arguments()
    if args.profile == 1:
        t1 = time.time()
        process = psutil.Process(os.getpid())
        main(args)
        t2 = time.time()
        print(f"Total run time = {t2-t1} seconds")
        mem_info = process.memory_full_info()
        print_memory_info(mem_info)

    else:
        main(args)
