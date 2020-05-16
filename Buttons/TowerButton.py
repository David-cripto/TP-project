from Buttons.Button import *
import os


def fill_img(st):
    img_button = pygame.image.load(os.path.join("Buttons", st + ".png"))
    img_button = pygame.transform.scale(img_button, (70, 60))
    return img_button


def star_i():
    star_img = pygame.image.load(os.path.join("Img", "star.png"))
    star_img.set_colorkey((255, 255, 255))
    star_img = pygame.transform.scale(star_img, (20, 20))
    return star_img


class TowerButtons(Button):
    def __init__(self):
        self.cost = None
        self.img = None
        self.width = None
        self.height = None
        self.x = None
        self.y = None
        self.selected = False
        self.star_img = star_i()
