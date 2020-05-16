import pygame

pygame.init()

arch_cor = (945, 100)
arb_cor = (945, 250)


class Button:

    def click(self):
        pos = pygame.mouse.get_pos()
        x1 = pos[0] >= self.x - self.width // 2
        x2 = pos[0] <= self.x + self.width // 2
        y1 = pos[1] <= self.y + self.height // 2
        y2 = pos[1] >= self.y - self.height // 2
        if x1 and x2 and y1 and y2:
            return True
        return False

    def draw(self, win):
        x = self.x - self.width // 2
        y = self.y - self.height // 2
        win.blit(self.img, (x, y))
        f = pygame.font.SysFont('arial', 25)
        text = f.render(str(self.cost), 1, (255, 255, 255))
        win.blit(text, (self.x, self.y + self.height // 2 + 5))
        win.blit(self.star_img, (self.x - 35, 7 + self.y + self.height // 2))