from Buttons.TowerButton import *


class ArcherButton(TowerButtons):
    def __init__(self):
        super(ArcherButton, self).__init__()
        self.cost = 250
        self.img = fill_img("arch_img")
        self.width = self.img.get_width()
        self.height = self.img.get_width()
        self.x = arch_cor[0]
        self.y = arch_cor[1]
        self.selected = False
