import pygame
import os
import Enemies.WaveBuilder
import Enemies.Enemy
import Buttons.ArcherButton
import Buttons.ArbaletButton
import Buttons.Command
import Towers.Towers
import Towers.Archer
import Towers.Arbalet
import time

pygame.init()

FPS = 500
places = [[281, 113], [447, 112], [656, 126],
          [546, 301], [270, 347],
          [363, 474], [539, 475]]

white = (255, 255, 255)
red = (255, 0, 0)
size_for_img = (50, 50)


def gr(st):
    img = pygame.image.load(os.path.join("Img", st + ".png"))
    img.set_colorkey(white)
    img = pygame.transform.scale(img, size_for_img)
    return img


def inRange(buttons):
    bo = True
    for but in buttons:
        if but.click():
            bo = False
    return bo


def text(temp):
    t = pygame.font.SysFont("arial", 50)
    t = t.render(str(temp), 1, white)
    return t


class Graphics:
    def __init__(self):
        self.star_img = gr("star")
        self.health_img = gr("health")

    def draw(self, win, money, health):
        win.blit(self.star_img, (20, 500))
        win.blit(text(money), (75, 500))
        win.blit(self.health_img, (20, 450))
        win.blit(text(health), (75, 450))


def makeWave(builder):
    builder.addGoblin()
    builder.addOgre()
    return builder.getResult()


def makeButtons():
    buttons = []
    button = Buttons.ArcherButton.ArcherButton()
    buttons.append(button)
    button = Buttons.ArbaletButton.ArbaletButton()
    buttons.append(button)
    return buttons


def makeTower(tower_place):
    pos = pygame.mouse.get_pos()
    bo = False
    pos1 = None
    pos2 = None
    for i in range(len(tower_place)):
        sel1 = abs(tower_place[i][0] - pos[0]) <= 25
        sel2 = abs(tower_place[i][1] - pos[1]) <= 20
        sel3 = tower_place[i][2]
        if sel1 and sel2 and not sel3:
            pos1 = tower_place[i][0]
            pos2 = tower_place[i][1]
            tower_place[i][2] = True
            bo = True
            break
    return (bo, pos1, pos2)


class Game:
    def __init__(self):
        self.width = 1000
        self.height = 562
        self.win = pygame.display.set_mode((self.width, self.height))
        builder = Enemies.WaveBuilder.Wave1Builder()
        self.wave = makeWave(builder)
        self.number_wave = 1
        self.buttons = makeButtons()
        self.bg = pygame.image.load(os.path.join("Img", "bg.png"))
        self.health = 10
        self.money = 500
        self.towers = []
        self.tower_place = places
        self.graph = Graphics()
        self.commands = []
        self.wn = False
        for i in self.tower_place:
            i.append(False)

    def run(self):
        game = True
        clock = pygame.time.Clock()
        while game:
            clock.tick(FPS)
            self.wave.move()
            if (len(self.wave.wave) == 0 and self.number_wave == 2):
                game = False
                self.wn = True
            elif (len(self.wave.wave) == 0):
                builder = Enemies.WaveBuilder.Wave2Builder()
                self.wave = makeWave(builder)
                self.number_wave += 1
            if self.health <= 0:
                game = False
            for events in pygame.event.get():
                if events.type == pygame.QUIT:
                    game = False
                for i in range(len(self.buttons)):
                    enough = self.money >= self.buttons[i].cost
                    if events.type == pygame.MOUSEBUTTONDOWN and self.buttons[i].click() and enough:
                        temp = Buttons.Command.Command1(self.win, self.buttons, self.tower_place)
                        self.commands.append(temp)
                        for but in self.buttons:
                            but.selected = False
                        self.buttons[i].selected = True
                    forif = events.type == pygame.MOUSEBUTTONDOWN
                    if inRange(self.buttons) and self.buttons[i].selected and forif and enough:
                        temp = makeTower(self.tower_place)
                        tow = None
                        if temp[0]:
                            self.money -= self.buttons[i].cost
                            if i == 0:
                                tow = Towers.Archer.Archer(temp[1], temp[2])
                            elif i == 1:
                                tow = Towers.Arbalet.Arbalet(temp[1], temp[2])
                            self.towers.append(tow)
                        self.buttons[i].selected = False
                        pygame.mouse.set_visible(True)
            for i in range(len(self.wave.wave)):
                if self.wave.wave[i].path_pos == len(Enemies.Enemy.path) - 1:
                    self.wave.wave.pop(i)
                    self.health -= 1
                    break
                if not self.wave.wave[i].live():
                    self.wave.wave.pop(i)
                    self.money += 50
                    break
            for t in self.towers:
                t.fire(self.wave.wave)
            self.draw()

    def draw(self):
        self.win.blit(self.bg, (0, 0))
        for button in self.buttons:
            button.draw(self.win)
        self.graph.draw(self.win, self.money, self.health)
        self.wave.draw(self.win)
        for tower in self.towers:
            tower.draw(self.win)
        for temp in self.commands:
            temp.execute()
        if self.wn:
            img = pygame.transform.scale(pygame.image.load(os.path.join("Img", "win.png")), (243, 100))
            x = self.width // 2 - img.get_width() // 2
            y = self.height // 2 - img.get_height() // 2
            self.win.blit(img, (x, y))
        pygame.display.update()
        if self.wn:
            time.sleep(1)


g = Game()
g.run()
