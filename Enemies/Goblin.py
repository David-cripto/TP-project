from Enemies.Enemy import *


class Goblin(Enemy):
    def __init__(self,x,y):
        super(Goblin, self).__init__(x,y)
        self.vel = goblin_vel
        self.img_left = []
        self.img_right = []
        fill_img(self.img_left, self.img_right, "troll")
        self.width = self.img_right[0].get_width()
        self.height = self.img_right[0].get_height()
        self.health = health_goblin
        self.max_health = health_goblin
