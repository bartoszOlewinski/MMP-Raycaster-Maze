import gym
from gym import spaces

import numpy as np

# NOT FINISHED
class RaycasterMazeEnv(gym.Env):
    ACTION = {"Up", "Down", "Left", "Right", "Space"}

    def __init__(self):
        # probably useless
        # super(RaycasterMazeEnv, self)._init_()

        # variables for observation space
        HEIGHT = 500
        WIDTH = 660,
        N_CHANNELS = 3

        # 0, 255 because it's pixel observing, shape is responsible for the box it's watching
        self.observation_space = spaces.Box(low=0, high=255,
                                            shape=(HEIGHT, WIDTH, N_CHANNELS), dtype=np.uint8)

        N_DISCRETE_ACTION_SPACE = 5
        self.action_space = spaces.Discrete(N_DISCRETE_ACTION_SPACE)

        # score, money bags
        self.score = 0

        # gold and silver keys
        self.gold_key = False
        self.silver_key = False

        # self.timer = 0

        self.has_finished = False

    def step(self, action):
        # pass the action to the txt file for c++
        f = open('actionToTake.txt', 'w')
        actionString = str
        if action == 1:
            actionString = '1'
        elif action == 2:
            actionString = '2'
        elif action == 3:
            actionString = '3'
        elif action == 4:
            actionString = '4'
        elif action == 5:
            actionString = '5'

        # write action to the text file
        f.write(actionString)
        f.close()

        # getting information from game
        points = int
        gold_key = bool
        silver_key = bool
        finished = bool

        iteration = 0

        # reward
        reward = 0

        # read text file to check agent information
        with open('agentInfo.txt') as fInfo:
            for line in fInfo:
                if iteration == 0:
                    points = int(line)
                elif iteration == 1:
                    gold_key = bool(line)
                elif iteration == 2:
                    silver_key = bool(line)
                elif iteration == 3:
                    finished = bool(line)

                iteration += 1

        # check if agent picked up money, if so reward
        if points > self.score:
            reward += 5
            self.score += (points - self.score)

        # check if agent picked up key and add reward accordingly
        if not self.gold_key and gold_key:
            reward += 30
        if not self.silver_key and silver_key:
            reward += 30

        # check if episode has finished
        if finished:
            reward += 100
            self.has_finished = finished

        # take screenshot from game and turn it into gym state object
        observation = {}

        return observation, reward, self.has_finished, {}

    def reset(self):
        self.score = 0

        # self.timer = 0

        self.gold_key = False

        self.silver_key = False

        self.has_finished = False

        # set RESET CODE FLAG for c++ to reset the map
        f = open('actionToTake.txt', 'w')
        f.write('-99')
        f.close()
