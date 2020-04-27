import pygame
from random import *

class Coin(pygame.sprite.Sprite):
    def __init__(self,position,bg_size,widmax):
        super().__init__()
        self.image = pygame.image.load("images/coin.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
        self.curr_speed=self.init_speed = randint(-6,-1)
        self.curr_time=self.init_time=0
        self.speedx_max=int(widmax/12)
        self.speedx=randint(0-self.speedx_max,self.speedx_max)
    def update(self):
        self.rect.x+=self.speedx
        if self.rect.left<=0 or self.rect.right>=self.width:
            self.speedx*=-1
        self.rect.top += self.curr_speed
        self.curr_speed=self.init_speed+(self.curr_time-self.init_time)*0.2
        self.curr_time+=1
