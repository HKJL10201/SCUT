import pygame

class Barrage1(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/barrage1.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top += self.speed

class Barrage2_s(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage2_s.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top += self.speed

class Barrage2_sw(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage2_sw.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top += self.speed-1
        self.rect.x-=self.speed-1

class Barrage2_se(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage2_se.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top += self.speed-1
        self.rect.x+=self.speed-1

class Barrage2_n(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage2_n.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top -= self.speed

class Barrage2_nw(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage2_nw.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top -= self.speed-1
        self.rect.x-=self.speed-1

class Barrage2_ne(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage2_ne.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top -= self.speed-1
        self.rect.x+=self.speed-1

class Barrage2_w(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage2_w.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.x-=self.speed

class Barrage2_e(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage2_e.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 3
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.x+=self.speed

class Barrage3_slow(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage3_slow.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 5
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        if self.rect.bottom<self.height*0.8:
            self.rect.top += self.speed
        else:
            self.rect.top += self.speed-1

class Barrage3_fast(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage3_fast.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 5
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        if self.rect.bottom<self.height*0.7:
            self.rect.top += self.speed
        else:
            self.rect.top += self.speed+1

class Barrage3_sw(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage3_sw.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 4
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top += self.speed-1
        self.rect.x-=self.speed-1

class Barrage3_se(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage3_se.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 4
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top += self.speed-1
        self.rect.x+=self.speed-1

class Barrage3_nw(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage3_nw.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 4
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top -= self.speed-1
        self.rect.x-=self.speed-1

class Barrage3_ne(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage3_ne.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 4
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.top -= self.speed-1
        self.rect.x+=self.speed-1

class Barrage3_w(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage3_w.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 4
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.x-=self.speed

class Barrage3_e(pygame.sprite.Sprite):
    def __init__(self,position,bg_size):
        super().__init__()
        self.image = pygame.image.load("images/barrage/Barrage3_e.png")
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.speed = 4
        self.mask = pygame.mask.from_surface(self.image)
        self.width,self.height = bg_size[0],bg_size[1]
    def update(self):
        self.rect.x+=self.speed
