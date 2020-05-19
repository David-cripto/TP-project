import pygame
import math
from Enemies.InterfaceWave import *
import os

path = [(76, 80), (138, 56), (193, 80), (683, 79), (756, 152), (716, 241), (505, 265), (452, 309),
        (450, 555), (450, 600)]

red = (255, 0, 0)
green = (0, 255, 0)

length = 75
goblin_vel = 0.75
ogre_vel = 1

health_goblin = 8000
health_ogre = 5000

wave1_count_goblin = 3
wave1_count_ogre = 4

wave2_count_goblin = 5
wave2_count_ogre = 5


def fill_img(img_left, img_right, st):
    number = None
    if st == "troll":
        number = 21
    else:
        number = 12
    for i in range(1, number):
        img_left.append(pygame.image.load(os.path.join("Enemies\Img", "run_" + st + "_left (" + str(i) + ").png")))
        img_right.append(pygame.image.load(os.path.join("Enemies\Img", "run_" + st + "_right (" + str(i) + ").png")))
    for i in range(len(img_right)):
        img_right[i] = pygame.transform.scale(img_right[i], (94, 80))
    for i in range(len(img_left)):
        img_left[i] = pygame.transform.scale(img_left[i], (94, 80))


class Enemy(InterfaceWave):
    def __init__(self, x0, y0):
        self.vel = None
        self.path_pos = 0
        self.x = x0
        self.y = y0
        self.frame = 0
        self.img_left = None
        self.img_right = None
        self.width = None
        self.height = None
        self.health = None
        self.max_health = None

    def move(self):
        if (path[self.path_pos][0] - self.x) <= 5 and (path[self.path_pos][1] - self.y) <= 5:
            self.path_pos += 1
        x1, y1 = self.x, self.y
        x2, y2 = path[self.path_pos]
        hypothenuse = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
        self.x += (x2 - x1) / hypothenuse * self.vel
        self.y += (y2 - y1) / hypothenuse * self.vel

    def draw(self, win):
        temp_x = self.x - self.width // 2
        temp_y = self.y - self.height // 2
        left = path[self.path_pos][0] - self.x
        if left < 0:
            win.blit(self.img_left[self.frame], (temp_x, temp_y))
        else:
            win.blit(self.img_right[self.frame], (temp_x, temp_y))
        self.frame += 1
        if self.frame >= len(self.img_right):
            self.frame = 0
        self.health_bar(win)

    def health_bar(self, win):
        move_by = length / self.max_health
        health_bar = move_by * self.health
        rect_size_red = (self.x - self.width // 2, self.y - self.height // 2, length, 10)
        rect_size_green = (self.x - self.width // 2, self.y - self.height // 2, health_bar, 10)
        pygame.draw.rect(win, red, rect_size_red, 0)
        pygame.draw.rect(win, green, rect_size_green, 0)

    def live(self):
        return self.health > 0

    def set_health(self, damage):
        self.health -= damage
