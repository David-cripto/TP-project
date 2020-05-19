from Towers.Towers import *


class Arbalet(Towers):
    def __init__(self, x, y):
        self.x = x
        self.y = y
        self.sell_pr = 200
        self.price = 300
        self.img = fill_img("12")
        self.width = self.img.get_width()
        self.height = self.img.get_height()
        self.damage = 38
        self.radius_damage = 120
        self.fire_b = False
        self.frame = 0
        self.img_per = fill_img_per(51, 64)
