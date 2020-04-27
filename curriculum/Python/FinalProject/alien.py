import pygame
from random import *

class Smallalien(pygame.sprite.Sprite):
    def __init__(self,bg_size):
        pygame.sprite.Sprite.__init__(self)

        self.image = pygame.image.load("images/alien0.png")
        self.rect = self.image.get_rect()
        self.width,self.height = bg_size[0],bg_size[1]
        self.speed = 2
        self.active = True
        self.mask = pygame.mask.from_surface(self.image)
        self.rect.left,self.rect.top = randint(0,self.width-self.rect.width),\
                                        randint(-5*self.height,0)
        self.diretion_left=1
        self.diretion_down=1
        self.round_num=0
        self.across_flag=0
        self.barrage_begin_flag=0
        self.barrage_timer=0
    def move(self):
        if self.round_num < 3:
            self.rect.top += self.speed*self.diretion_down
            self.rect.x-=self.speed*0.5*self.diretion_left
            if self.rect.left<=0 or self.rect.right>=self.width:
                self.diretion_left*=-1
            if self.across_flag:
                if self.rect.top > self.height*0.6 or self.rect.top<=0:
                    self.diretion_down*=-1
                    self.round_num+=1
            else:
                if self.rect.top > self.height*0.6:
                    self.across_flag=1
                    self.diretion_down*=-1
                    self.round_num+=1
        else:
            if self.rect.bottom>0:
                self.rect.top -= self.speed
                self.rect.x-=self.speed*0.5*self.diretion_left
            else:
                self.reset()
        if not self.barrage_begin_flag and self.rect.top>0:
            self.barrage_begin_flag=1

    def reset(self):
        self.active = True
        self.rect.left, self.rect.top = randint(0, self.width - self.rect.width), \
                                        randint(-5 * self.height, 0)
        self.diretion_left=1
        self.diretion_down=1
        self.round_num=0
        self.across_flag=0
        self.barrage_begin_flag=0
        self.barrage_timer=0


class Midalien(pygame.sprite.Sprite):
    energy = 8
    def __init__(self,bg_size):
        pygame.sprite.Sprite.__init__(self)

        self.image = pygame.image.load("images/alien1.png")
        self.image_hit = pygame.image.load("images/alien1_hit.png")
        self.rect = self.image.get_rect()
        self.width,self.height = bg_size[0],bg_size[1]
        self.rect.left,self.rect.top = randint(0,self.width-self.rect.width),\
                                        randint(-10*self.height,-self.height)
        self.speed = 1
        self.active = True
        self.mask = pygame.mask.from_surface(self.image)
        self.energy = Midalien.energy
        self.hit = False
        self.diretion_left=1
        self.barrage_begin_flag=0
        self.barrage_timer=0
    def move(self):
        if self.rect.top < self.height:
            self.rect.top += self.speed
            self.rect.x-=self.speed*self.diretion_left
            if self.rect.left<=0 or self.rect.right>=self.width:
                self.diretion_left*=-1
        else:
            self.reset()
        if not self.barrage_begin_flag and self.rect.top>0:
            self.barrage_begin_flag=1

    def reset(self):
        self.active = True
        self.energy = Midalien.energy
        self.rect.left, self.rect.top = randint(0, self.width - self.rect.width), \
                                        randint(-10 * self.height,-self.height)
        self.diretion_left=1
        self.barrage_begin_flag=0
        self.barrage_timer=0

class Bigalien(pygame.sprite.Sprite):
    energy = 20
    def __init__(self,bg_size):
        pygame.sprite.Sprite.__init__(self)

        self.image1 = pygame.image.load("images/alien2.png")
        self.image2 = pygame.image.load("images/alien2_n2.png")
        self.image_hit = pygame.image.load("images/alien2_hit.png")
        self.rect = self.image1.get_rect()
        self.width,self.height = bg_size[0],bg_size[1]
        self.speed = 1
        self.active = True
        self.mask = pygame.mask.from_surface(self.image1)
        self.energy = Bigalien.energy
        self.hit = False
        self.rect.left,self.rect.top = randint(0,self.width-self.rect.width),\
                                        randint(-15*self.height,-5*self.height)
        self.round_num=0
        self.barrage_begin_flag=0
        self.diretion_flag='down'
        self.across_flag=0
        self.barrage_timer=0
    def move(self):
        if self.round_num < 3:
            if self.diretion_flag=='down':
                if self.rect.bottom >= self.height*0.6:
                    self.diretion_flag='right'
                    self.across_flag=1
                else:
                    self.rect.bottom += self.speed
            elif self.diretion_flag=='right':
                if self.rect.right>=self.width:
                    self.diretion_flag='up'
                else:
                    self.rect.x+=self.speed
            elif self.diretion_flag=='up':
                if self.rect.top<=0:
                    self.round_num+=1
                    self.diretion_flag='left'
                else:
                    self.rect.top -= self.speed
            elif self.diretion_flag=='left':
                if self.rect.left<=0:
                    self.diretion_flag='down'
                else:
                    self.rect.x-=self.speed
        else:
            if self.rect.bottom>0:
                self.rect.bottom -= self.speed
            else:
                self.reset()
        if not self.barrage_begin_flag and self.rect.top>0:
            self.barrage_begin_flag=1


    def reset(self):
        self.active = True
        self.energy = Bigalien.energy
        self.rect.left, self.rect.top = randint(0, self.width - self.rect.width), \
                                        randint(-15 * self.height, -5*self.height)
        
        self.round_num=0
        self.barrage_begin_flag=0
        self.diretion_flag='down'
        self.across_flag=0
        self.barrage_timer=0