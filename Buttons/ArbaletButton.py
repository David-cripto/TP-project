from Buttons.TowerButton import *


class ArbaletButton(TowerButtons):
    def __init__(self):
        super(ArbaletButton, self).__init__()
        self.cost = 300
        self.img = fill_img("arb_img")
        self.width = self.img.get_width()
        self.height = self.img.get_width()
        self.x = arb_cor[0]
        self.y = arb_cor[1]
        self.selected = False
