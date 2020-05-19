from Enemies.Wave import *
from Enemies.Goblin import *
from Enemies.Ogre import *
from Enemies.Enemy import *


class WaveBuilder:
    def addGoblin(self):
        pass

    def addOgre(self):
        pass

    def getResult(self):
        pass


class Wave1Builder(WaveBuilder):
    def __init__(self):
        self.result = Wave()
        self.x = path[0][0]
        self.y = path[0][1]

    def addGoblin(self):
        for i in range(wave1_count_goblin):
            temp = Goblin(self.x, self.y)
            self.result.addEnemy(temp)
            self.x -= 50

    def addOgre(self):
        for i in range(wave1_count_ogre):
            temp = Ogre(self.x, self.y)
            self.result.addEnemy(temp)
            self.x -= 50

    def getResult(self):
        return self.result


class Wave2Builder(WaveBuilder):
    def __init__(self):
        self.result = Wave()
        self.x = path[0][0]
        self.y = path[0][1]

    def addGoblin(self):
        for i in range(wave2_count_goblin):
            temp = Goblin(self.x, self.y)
            self.result.addEnemy(temp)
            self.x -= 50

    def addOgre(self):
        for i in range(wave2_count_ogre):
            temp = Ogre(self.x, self.y)
            self.result.addEnemy(temp)
            self.x -= 50

    def getResult(self):
        return self.result
