from Enemies.Enemy import *


class Ogre(Enemy):
    def __init__(self, x, y):
        super(Ogre, self).__init__(x, y)
        self.vel = ogre_vel
        self.img_left = []
        self.img_right = []
        fill_img(self.img_left, self.img_right, "ogre")
        self.width = self.img_right[0].get_width()
        self.height = self.img_right[0].get_height()
        self.health = health_ogre
        self.max_health = health_ogre
