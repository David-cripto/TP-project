from Towers.Towers import *


class Archer(Towers):
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.sell_pr = 200
        self.price = 250
        self.img = fill_img("7")
        self.width = self.img.get_width()
        self.height = self.img.get_height()
        self.damage = 25
        self.radius_damage = 160
        self.fire_b = False
        self.frame = 0
        self.img_per = fill_img_per(38, 44)
