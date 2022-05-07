import random

ACTION_TAKEN = '2'


# function that tests interface between C++ and Python
def run():
    global ACTION_TAKEN
    fLog = open('pythonLog.txt', 'a')
    logString = str

    for (x) in range(1000):
        f = open('actionToTake.txt', 'w')
        fLog = open('pythonLog.txt', 'a+')
        act_int = random.randrange(1, 4)
        if act_int == 1:
            ACTION_TAKEN = '1'
            logString = ': go forwards'
        elif act_int == 2:
            ACTION_TAKEN = '2'
            logString = ': go backwards'
        elif act_int == 3:
            ACTION_TAKEN = '3'
            logString = ': turn left'
        elif act_int == 4:
            ACTION_TAKEN = '4'
            logString = ': turn right'

        fLog.write(logString)

        f.write(ACTION_TAKEN)

        f.close()

        fLog.close()

    # -99 is a reset map code
    # f2 = open('actionToTake.txt', 'w')
    # f2.write ('-99')
    # f2.close()
