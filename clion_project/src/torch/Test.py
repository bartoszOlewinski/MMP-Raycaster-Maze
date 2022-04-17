# import MazeEnv.py
# import Actions.py

ACTION_TAKEN = -1

import time


def run():
    global ACTION_TAKEN

    ACTION_TAKEN = 2
    time.sleep(2000)
    ACTION_TAKEN = 3
    time.sleep(2000)
    ACTION_TAKEN = -1
