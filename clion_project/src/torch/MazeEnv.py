import gym
from gym import spaces

import numpy as np


class RaycasterMazeEnv(gym.Env):
    ACTION = {"Up", "Down", "Left", "Right", "Space"}

    def _init_(self, arg1, arg2):
        super(RaycasterMazeEnv, self)._init_()

        HEIGHT = 500
        WIDTH = 660,
        N_CHANNELS = 3

        # 0, 255 because it's pixel observing, shape is responsible for the box it's watching
        self.observation_space = spaces.Box(low=0, high=255,
                                            shape=(HEIGHT, WIDTH, N_CHANNELS), dtype=np.uint8)

        N_DISCRETE_ACTION_SPACE = 5
        self.action_space = spaces.Discrete(N_DISCRETE_ACTION_SPACE)

        self.score = 0

        self.timer = 0

        self.hasFinished = False

    def step(self, action):
        pass
        # return self.state, reward, done, info

    def reset(self):
        self.score = 0

        self.timer = 0

        self.hasFinished = False
