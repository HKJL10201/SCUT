import pygame

class Ship(pygame.sprite.Sprite):
    def __init__(self,bg_size):
        pygame.sprite.Sprite.__init__(self)
        self.image1 = pygame.image.load("images/ship1.png")
        self.image2 = pygame.image.load("images/ship2.png")
        self.destroy_images = []
        self.destroy_images.extend([pygame.image.load("images/ship_blowup_n1.png"),\
                                    pygame.image.load("images/ship_blowup_n2.png"), \
                                    pygame.image.load("images/ship_blowup_n3.png"), \
                                    pygame.image.load("images/ship_blowup_n4.png"), \
                                    ])
        self.rect = self.image1.get_rect()
        self.width,self.height = bg_size[0],bg_size[1]
        self.rect.left,self.rect.top = (self.width-self.rect.left)//2,\
                                       self.height-self.rect.height-60
        self.speed = 10
        self.active = True
        self.invincible = False
        self.mask = pygame.mask.from_surface(self.image1)
        self.shotting1=False
        self.shotting2=False
        self.down_sound_play_flag=True

    def moveUp(self):
        if self.rect.top > 0:
            self.rect.top -= self.speed
        else:
            self.rect.top = 0
    def moveDown(self):
        if self.rect.bottom < self.height - 60:
            self.rect.top += self.speed
        else:
            self.rect.bottom = self.height - 60
    def moveLeft(self):
        if self.rect.left > 0:
            self.rect.left -= self.speed
        else:
            self.rect.left = 0
    def moveRight(self):
        if self.rect.right <self.width:
            self.rect.left += self.speed
        else:
            self.rect.right = self.width
    def reset(self):
        self.rect.left, self.rect.top = (self.width - self.rect.width) // 2, \
                                        self.height - self.rect.height - 60
        self.active = True
        self.invincible = True
        self.down_sound_play_flag=True

