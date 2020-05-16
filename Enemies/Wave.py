from Enemies.InterfaceWave import *


class Wave(InterfaceWave):
    def __init__(self):
        self.wave = []

    def addEnemy(self, enemy):
        self.wave.append(enemy)

    def move(self):
        for i in self.wave:
            i.move()

    def empty(self):
        return len(self.wave) == 0

    def draw(self, win):
        for i in self.wave:
            i.draw(win)
