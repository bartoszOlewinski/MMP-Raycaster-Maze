import MazeEnv.py
import Actions.py

import time

def run():
    
    Actions.ACTION_TAKEN = 2
    time.sleep(2000)
    Actions.ACTION_TAKEN = 3
    time.sleep(2000)
    Actions.ACTION_TAKEN = -1
    
    print("Test print")