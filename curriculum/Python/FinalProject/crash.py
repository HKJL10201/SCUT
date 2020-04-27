import pygame

class Crash_small_alien(pygame.sprite.Sprite):
    def __init__(self,position):
        super().__init__()
        self.destroy_images = []
        self.destroy_images.extend([pygame.image.load("images/alien0_down1.png"), \
                                    pygame.image.load("images/alien0_down2.png"), \
                                    pygame.image.load("images/alien0_down3.png"), \
                                    pygame.image.load("images/alien0_down4.png"), \
                                    ])
        self.index=0
        self.image = self.destroy_images[self.index]
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.mask = pygame.mask.from_surface(self.image)
        self.curr_time=self.init_time=0
        self.index_max=4
    def update(self):
        if (self.curr_time)%5==0:
            self.index+=1
            if self.index<4:
                self.image = self.destroy_images[self.index]
        self.curr_time+=1

class Crash_mid_alien(pygame.sprite.Sprite):
    def __init__(self,position):
        super().__init__()
        self.destroy_images = []
        self.destroy_images.extend([pygame.image.load("images/alien1_down1.png"), \
                                    pygame.image.load("images/alien1_down2.png"), \
                                    pygame.image.load("images/alien1_down3.png"), \
                                    pygame.image.load("images/alien1_down4.png"), \
                                    ])
        self.index=0
        self.image = self.destroy_images[self.index]
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.mask = pygame.mask.from_surface(self.image)
        self.curr_time=self.init_time=0
        self.index_max=4
    def update(self):
        if (self.curr_time)%5==0:
            self.index+=1
            if self.index<4:
                self.image = self.destroy_images[self.index]
        self.curr_time+=1

class Crash_big_alien(pygame.sprite.Sprite):
    def __init__(self,position):
        super().__init__()
        self.destroy_images = []
        self.destroy_images.extend([pygame.image.load("images/alien2_down1.png"), \
                                    pygame.image.load("images/alien2_down2.png"), \
                                    pygame.image.load("images/alien2_down3.png"), \
                                    pygame.image.load("images/alien2_down4.png"), \
                                    pygame.image.load("images/alien2_down5.png"), \
                                    pygame.image.load("images/alien2_down6.png"), \
                                    ])
        self.index=0
        self.image = self.destroy_images[self.index]
        self.rect = self.image.get_rect()
        self.rect.midbottom = position
        self.mask = pygame.mask.from_surface(self.image)
        self.curr_time=self.init_time=0
        self.index_max=6
    def update(self):
        if (self.curr_time)%3==0:
            self.index+=1
            if self.index<6:
                self.image = self.destroy_images[self.index]
        self.curr_time+=1
        