from Towers.Archer import *
from Towers.Arbalet import *

red = (255, 0, 0)


class Command:
    def execute(self):
        pass


class Command1(Command):
    def __init__(self, win, buttons, places):
        self.win = win
        self.buttons = buttons
        self.tower_place = places

    def execute(self):
        for i in range(len(self.buttons)):
            if self.buttons[i].selected:
                pygame.mouse.set_visible(False)
                pos = pygame.mouse.get_pos()
                temp = None
                if i == 0:
                    temp = Archer(*pygame.mouse.get_pos())
                if i == 1:
                    temp = Arbalet(*pygame.mouse.get_pos())
                x = pos[0] - temp.img.get_width() // 2
                y = pos[1] - temp.img.get_height() // 2
                self.win.blit(temp.img, (x, y))
                for tmp in self.tower_place:
                    if not tmp[2]:
                        x, y = (tmp[0], tmp[1] + 40)
                        rad = 10
                        pygame.draw.circle(self.win, red, (x, y), rad)


class Command2(Command):
    def __init__(self, tower):
        self.tower = tower

    def execute(self):
        self.tower.upgrade()
