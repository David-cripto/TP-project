import math
import pygame
import os

pygame.init()


def fill_img(num):
    img = pygame.image.load(os.path.join("Towers\Img", num + ".png"))
    img = pygame.transform.scale(img, (80, 120))
    return img


def fill_img_per(num1, num2):
    img_per = []
    for i in range(num1, num2):
        img_per.append(pygame.image.load(os.path.join("Towers\Img", str(i) + ".png")))
    for i in range(len(img_per)):
        img_per[i] = pygame.transform.scale(img_per[i], (25, 30))
    return img_per


class Towers:
    def draw(self, win):
        x = self.x - self.width // 2
        y = self.y - self.height // 2
        win.blit(self.img, (x, y))
        x = self.x - self.width // 2 + 25
        y = self.y - self.height // 2 - 10
        win.blit(self.img_per[self.frame], (x, y))
        if self.fire_b:
            self.frame += 1
            if self.frame >= len(self.img_per):
                self.frame = 0
        else:
            self.frame = 0

    def fire(self, enemies):

        for enemy in enemies:
            in_rad = math.sqrt((enemy.x - self.x) ** 2 + (enemy.y - self.y) ** 2) <= self.radius_damage
            if in_rad and enemy.live():
                enemy.set_health(self.damage)
                self.fire_b = True
                break
        else:
            self.fire_b = False
