import pygame

class Bullet1(pygame.sprite.Sprite):
    def __init__(self,position):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load("images/bullet1.png")
        self.rect = self.image.get_rect()
        self.rect.midtop = position
        self.speed = 12
        self.mask = pygame.mask.from_surface(self.image)
    def update(self):
        self.rect.top -= self.speed

class Bullet1_left(pygame.sprite.Sprite):
    def __init__(self,position):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load("images/bullet1_left.png")
        self.rect = self.image.get_rect()
        self.rect.midtop = position
        self.speed = 12
        self.mask = pygame.mask.from_surface(self.image)
    def update(self):
        self.rect.top -= self.speed
        self.rect.x -= self.speed-10

class Bullet1_right(pygame.sprite.Sprite):
    def __init__(self,position):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load("images/bullet1_right.png")
        self.rect = self.image.get_rect()
        self.rect.midtop = position
        self.speed = 12
        self.mask = pygame.mask.from_surface(self.image)
    def update(self):
        self.rect.top -= self.speed
        self.rect.x += self.speed-10

class Bullet2(pygame.sprite.Sprite):
    def __init__(self,position):
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.image.load("images/bullet2.png")
        self.rect = self.image.get_rect()
        self.rect.midtop = position
        self.speed = 14
        self.mask = pygame.mask.from_surface(self.image)
    def update(self):
        self.rect.top -= self.speed

