from __future__ import division
import pygame
import time
import sys
from pygame.locals import *
import ship
import alien
import bullet
import random
import barrage
import coin
import crash


pygame.init()
pygame.mixer.init()

#creat the screen to show the game
bg_size = width,height = 470,690
screen = pygame.display.set_mode(bg_size,0,32)
#set the caption
pygame.display.set_caption("Space War")
game_icon=pygame.image.load("./images/game_icon.png")
pygame.display.set_icon(game_icon)
GRAY = (127,127,127)
GREEN = (0,255,0)
RED = (255,0,0)
WHITE = (255,255,255)
# load all music
pygame.mixer.music.load("./sound/game_music.mp3")
pygame.mixer.music.set_volume(0.2)
alien1_down_sound = pygame.mixer.Sound("./sound/alien1_down.ogg")
alien1_down_sound.set_volume(0.2)
alien2_down_sound = pygame.mixer.Sound("./sound/alien2_down.ogg")
alien2_down_sound.set_volume(0.2)
alien3_down_sound = pygame.mixer.Sound("./sound/alien3_down.ogg")
alien3_down_sound.set_volume(0.4)
alien3_fly_sound = pygame.mixer.Sound("./sound/effcet_ui_feijishengji.ogg")
alien3_fly_sound.set_volume(0.2)
ship_down_sound = pygame.mixer.Sound("./sound/ship_down.ogg")
ship_down_sound.set_volume(0.2)
coin_sound = pygame.mixer.Sound("./sound/coin_sound.ogg")
coin_sound.set_volume(0.2)
bullet_sound = pygame.mixer.Sound("./sound/bullet.ogg")
bullet_sound.set_volume(0.1)
# creat backgroud picture
background = pygame.image.load("./images/background.png")

def add_small_aliens(group1,group2,num):
    for i in range(num):
        e1 = alien.Smallalien(bg_size)
        group1.add(e1)
        group2.add(e1)

def add_mid_aliens(group1,group2,num):
    for i in range(num):
        e2 = alien.Midalien(bg_size)
        group1.add(e2)
        group2.add(e2)

def add_big_aliens(group1,group2,num):
    for i in range(num):
        e3 = alien.Bigalien(bg_size)
        group1.add(e3)
        group2.add(e3)

def main():
    pygame.mixer.music.play(-1)
    clock = pygame.time.Clock()
    #initial the ship
    SpaceShip = ship.Ship(bg_size)
    #used to switch image
    switch_image = True
    #delay and timer
    delay = 100
    bullet_timer=0
    #index for destroying ship
    ship_destroy_index = 0

    #initial aliens
    aliens = pygame.sprite.Group()
    small_aliens = pygame.sprite.Group()
    add_small_aliens(small_aliens,aliens,15)
    mid_aliens = pygame.sprite.Group()
    add_mid_aliens(mid_aliens,aliens,4)
    big_aliens = pygame.sprite.Group()
    add_big_aliens(big_aliens,aliens,2)

    #record the score
    score = 0
    score_font =pygame.font.Font("font/fixedsys.ttf",36)
    new_record_font =pygame.font.Font("font/fixedsys.ttf",20)

    #coins
    coin_image = pygame.image.load("images/coin_icon.png")
    coin_rect = coin_image.get_rect()
    coin_font = pygame.font.Font("font/fixedsys.ttf",36)
    coin_num=0

    #mark game paused
    paused = False
    paused_nor_image = pygame.image.load("images/paused_nor.png")
    paused_pressed_image = pygame.image.load("images/paused_pressed.png")
    resume_nor_image = pygame.image.load("images/resume_nor.png")
    resume_pressed_image = pygame.image.load("images/resume_pressed.png")
    paused_rect = paused_nor_image.get_rect()
    paused_rect.left,paused_rect.top = width - paused_rect.width - 10 ,10
    paused_image = paused_nor_image

    #number of life
    life_image = pygame.image.load("images/life.png")
    life_rect = life_image.get_rect()
    life_num = 3

    #timer for invincible ship
    INVINCIBLE_TIME = USEREVENT + 2

    #open file flag
    recorded = False

    #captions for gameover screen
    gameover_font = pygame.font.Font("font/fixedsys.ttf",48)
    restart_image = pygame.image.load("images/restart_nor.png")
    restart_rect = restart_image.get_rect()
    quit_image = pygame.image.load("images/quit_nor.png")
    quit_rect = quit_image.get_rect()

    #all Group used
    bullets = pygame.sprite.Group()
    all_barrage = pygame.sprite.Group()
    coins = pygame.sprite.Group()
    crashes = pygame.sprite.Group()

    #temporary highest record
    with open("record.txt", "r") as f:
        temp_record_score = int(f.read())
    record_flag=False

    #main loop
    while True:
        # set backgroud
        screen.blit(background, (0, 0))

        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                sys.exit()
            elif event.type == MOUSEBUTTONDOWN:
                if life_num:
                    if event.button == 1 and paused_rect.collidepoint(event.pos):
                        paused = not paused
                        if paused:
                            pygame.mixer.music.pause()
                            pygame.mixer.pause()
                        else:
                            pygame.mixer.music.unpause()
                            pygame.mixer.unpause()

            elif event.type == MOUSEMOTION:
                if paused_rect.collidepoint(event.pos):
                    if paused:
                        paused_image = resume_pressed_image
                    else:
                        paused_image = paused_pressed_image
                else:
                    if paused:
                        paused_image = resume_nor_image
                    else:
                        paused_image = paused_nor_image
            elif event.type == KEYDOWN:
                if event.key==K_z:
                    bullet_timer=0
                    SpaceShip.shotting1=True
                    SpaceShip.shotting2=False
                if event.key==K_x:
                    bullet_timer=0
                    SpaceShip.shotting2=True
                    SpaceShip.shotting1=False
                if event.key==K_SPACE:
                    if life_num:
                        paused=not paused
                        if paused:
                            pygame.mixer.music.pause()
                            pygame.mixer.pause()
                        else:
                            pygame.mixer.music.unpause()
                            pygame.mixer.unpause()
            elif event.type==KEYUP:
                if event.key==K_z:
                    SpaceShip.shotting1=False
                if event.key==K_x:
                    SpaceShip.shotting2=False
            elif event.type == INVINCIBLE_TIME:
                SpaceShip.invincible = False
                pygame.time.set_timer(INVINCIBLE_TIME,0)

        if life_num and not paused:
            #events for keyboard
            key_pressed = pygame.key.get_pressed()
            if key_pressed[K_w] or key_pressed[K_UP]:
                SpaceShip.moveUp()
            if key_pressed[K_s] or key_pressed[K_DOWN]:
                SpaceShip.moveDown()
            if key_pressed[K_a] or key_pressed[K_LEFT]:
                SpaceShip.moveLeft()
            if key_pressed[K_d] or key_pressed[K_RIGHT]:
                SpaceShip.moveRight()
            
            # shotting
            if SpaceShip.shotting1:
                if not bullet_timer:
                    bullet_sound.play()
                    new_bullet=bullet.Bullet1(SpaceShip.rect.midtop)
                    bullets.add(new_bullet)
                    new_bullet=bullet.Bullet1_left(SpaceShip.rect.midtop)
                    bullets.add(new_bullet)
                    new_bullet=bullet.Bullet1_right(SpaceShip.rect.midtop)
                    bullets.add(new_bullet)
                bullet_timer=(bullet_timer+1)%15
            if SpaceShip.shotting2:
                if not bullet_timer:
                    bullet_sound.play()
                    new_bullet=bullet.Bullet2(SpaceShip.rect.midtop)
                    bullets.add(new_bullet)
                bullet_timer=(bullet_timer+1)%5
            bullets.update()
            for b in bullets.copy():
                if b.rect.bottom < 30 or b.rect.left>bg_size[1] or b.rect.right<0:
                    bullets.remove(b)
                else:
                    screen.blit(b.image,b.rect)
                    alien_hit = pygame.sprite.spritecollide(b,aliens,False,pygame.sprite.collide_mask)
                #check bullet&alien collision
                if alien_hit:
                    bullets.remove(b)
                    for e in alien_hit:
                        if e in mid_aliens or e in big_aliens:
                            e.hit = True
                            e.energy -= 1
                            if e.energy == 0:
                                e.active = False
                        else:
                            e.active = False
            
            #draw big alien
            for each in big_aliens:
                if each.diretion_flag=='right':
                    if not each.barrage_timer:
                        new_barrage=barrage.Barrage3_slow(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                elif each.diretion_flag=='left':
                    if not each.barrage_timer:
                        new_barrage=barrage.Barrage3_fast(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                elif each.diretion_flag=='down':
                    if not each.barrage_timer:
                        if each.across_flag:
                            new_barrage=barrage.Barrage3_se(each.rect.midbottom,bg_size)
                            all_barrage.add(new_barrage)
                            new_barrage=barrage.Barrage3_e(each.rect.midbottom,bg_size)
                            all_barrage.add(new_barrage)
                            new_barrage=barrage.Barrage3_ne(each.rect.midbottom,bg_size)
                            all_barrage.add(new_barrage)
                        else:
                            new_barrage=barrage.Barrage3_slow(each.rect.midbottom,bg_size)
                            all_barrage.add(new_barrage)
                            new_barrage=barrage.Barrage3_sw(each.rect.midbottom,bg_size)
                            all_barrage.add(new_barrage)
                            new_barrage=barrage.Barrage3_se(each.rect.midbottom,bg_size)
                            all_barrage.add(new_barrage)
                elif each.diretion_flag=='up':
                    if not each.barrage_timer:
                        new_barrage=barrage.Barrage3_sw(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage3_w(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage3_nw(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                if each.active:
                    each.move()
                    each.barrage_timer=(each.barrage_timer+1)%30
                    if each.hit:
                        screen.blit(each.image_hit,each.rect)
                        each.hit = False
                    else:
                        if switch_image:
                            screen.blit(each.image1,each.rect)
                        else:
                            screen.blit(each.image2,each.rect)
                    #draw energy bar
                    pygame.draw.line(screen,GRAY,\
                                     (each.rect.left,each.rect.top - 5),\
                                     (each.rect.right,each.rect.top - 5),\
                                     2)
                    #turn red when energy less than 20%, else green
                    energy_remain = each.energy / alien.Bigalien.energy
                    if energy_remain > 0.2:
                        energy_color = GREEN
                    else:
                        energy_color = RED
                    pygame.draw.line(screen,energy_color,\
                                     (each.rect.left,each.rect.top - 5),\
                                     (each.rect.left + each.rect.width * energy_remain,each.rect.top - 5),\
                                     2)
                    #play sound before it appear
                    if each.rect.bottom == -50:
                        alien3_fly_sound.play(-1)
                else:
                    #destroy
                    alien3_fly_sound.stop()
                    new_crash=crash.Crash_big_alien(each.rect.midbottom)
                    crashes.add(new_crash)
                    #coins
                    for i in range(10):
                        new_coin=coin.Coin(each.rect.midtop,bg_size,each.rect.width)
                        coins.add(new_coin)
                    alien3_down_sound.play()
                    score += 1000
                    each.reset()

            #mid alien
            for each in mid_aliens:
                #Barrage
                if each.barrage_begin_flag:
                    if not each.barrage_timer:
                        new_barrage=barrage.Barrage2_s(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage2_sw(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage2_se(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage2_n(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage2_nw(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage2_ne(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage2_w(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        new_barrage=barrage.Barrage2_e(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                if each.active:
                    each.move()
                    each.barrage_timer=(each.barrage_timer+1)%100
                    if each.hit:
                        screen.blit(each.image_hit,each.rect)
                        each.hit = False
                    else:
                        screen.blit(each.image,each.rect)
                    #draw energy bar
                    pygame.draw.line(screen,GRAY,\
                                     (each.rect.left,each.rect.top - 5),\
                                     (each.rect.right,each.rect.top - 5),\
                                     2)
                    #turn red when energy less than 20%, else green
                    energy_remain = each.energy / alien.Midalien.energy
                    if energy_remain > 0.2:
                        energy_color = GREEN
                    else:
                        energy_color = RED
                    pygame.draw.line(screen,energy_color,\
                                     (each.rect.left,each.rect.top - 5),\
                                     (each.rect.left + each.rect.width * energy_remain,each.rect.top - 5),\
                                     2)
                else:
                    #destroy
                    new_crash=crash.Crash_mid_alien(each.rect.midbottom)
                    crashes.add(new_crash)
                    #coins
                    for i in range(5):
                        new_coin=coin.Coin(each.rect.midtop,bg_size,each.rect.width)
                        coins.add(new_coin)
                    alien2_down_sound.play()
                    score += 500
                    each.reset()

            #small alien
            for each in small_aliens:
                #Barrage
                if each.barrage_begin_flag:
                    if not each.barrage_timer:
                        new_barrage=barrage.Barrage1(each.rect.midbottom,bg_size)
                        all_barrage.add(new_barrage)
                        
                if each.active:
                    each.move()
                    each.barrage_timer=(each.barrage_timer+1)%120
                    screen.blit(each.image,each.rect)
                else:
                    #destroy
                    new_crash=crash.Crash_small_alien(each.rect.midbottom)
                    crashes.add(new_crash)
                    #coins
                    new_coin=coin.Coin(each.rect.midtop,bg_size,each.rect.width)
                    coins.add(new_coin)
                    alien1_down_sound.play()
                    score += 100
                    each.reset()

            all_barrage.update()
            for b in all_barrage.copy():
                if b.rect.top >b.height or b.rect.bottom<0 or b.rect.left>b.width or b.rect.right<0:
                    all_barrage.remove(b)
                else:
                    screen.blit(b.image,b.rect)
            
            coins.update()
            for c in coins.copy():
                if c.rect.top >c.height:
                    coins.remove(c)
                else:
                    screen.blit(c.image,c.rect)
            
            crashes.update()
            for c in crashes.copy():
                if c.index<c.index_max:
                    screen.blit(c.image,c.rect)
                else:
                    crashes.remove(c)

            #check ship&aliens collision
            aliens_down = pygame.sprite.spritecollide(SpaceShip,aliens,False,pygame.sprite.collide_mask)
            if aliens_down and not SpaceShip.invincible:
                SpaceShip.active = False
                for e in aliens_down:
                    e.active = False
            
            #check ship&barrages collision
            aliens_down = pygame.sprite.spritecollide(SpaceShip,all_barrage,False,pygame.sprite.collide_mask)
            if aliens_down and not SpaceShip.invincible:
                SpaceShip.active = False
                for e in aliens_down:
                    all_barrage.remove(e)

            #check pick coins
            coins_pick = pygame.sprite.spritecollide(SpaceShip,coins,False,pygame.sprite.collide_mask)
            if coins_pick:
                for c in coins_pick:
                    coin_sound.play()
                    coins.remove(c)
                    coin_num+=1

            #draw space ship
            if SpaceShip.active:
                if not SpaceShip.invincible:
                    if switch_image:
                        screen.blit(SpaceShip.image1,SpaceShip.rect)
                    else:
                        screen.blit(SpaceShip.image2,SpaceShip.rect)
                else:
                    if switch_image:
                        screen.blit(SpaceShip.image1,SpaceShip.rect)
            else:
                #destroy
                if SpaceShip.down_sound_play_flag:
                    ship_down_sound.play()
                    SpaceShip.down_sound_play_flag=False
                if not (delay % 3):
                    screen.blit(SpaceShip.destroy_images[ship_destroy_index],SpaceShip.rect)
                    ship_destroy_index = (ship_destroy_index + 1) % 4
                    if ship_destroy_index == 0:
                        life_num -= 1
                        SpaceShip.reset()
                        pygame.time.set_timer( INVINCIBLE_TIME,3 * 1000)

            #draw life number
            if life_num:
                for i in range(life_num):
                    screen.blit(life_image,(width-10-(i+1)*life_rect.width,height-10-life_rect.height))

            #draw coin number
            coin_text = coin_font.render("x%d" % coin_num,True,WHITE)
            text_rect = coin_text.get_rect()
            screen.blit(coin_image,(10,height - 10 - coin_rect.height))
            screen.blit(coin_text,(20 + coin_rect.width,height - 5 - text_rect.height))

            #draw score
            score_text = score_font.render("Scroe:%s" % str(score),True,WHITE)
            screen.blit(score_text,(10,5))
        
        elif paused:
            for b in bullets.copy():
                screen.blit(b.image,b.rect)

            for b in all_barrage.copy():
                screen.blit(b.image,b.rect)
            
            for c in coins.copy():
                screen.blit(c.image,c.rect)
            
            for c in crashes.copy():
                if c.index<c.index_max:
                    screen.blit(c.image,c.rect)
                else:
                    crashes.remove(c)
            
            for e in small_aliens.copy():
                screen.blit(e.image,e.rect)

            for each in mid_aliens.copy():
                if each.active:
                    if each.hit:
                        screen.blit(each.image_hit,each.rect)
                    else:
                        screen.blit(each.image,each.rect)
                    #draw energy bar
                    pygame.draw.line(screen,GRAY,\
                                     (each.rect.left,each.rect.top - 5),\
                                     (each.rect.right,each.rect.top - 5),\
                                     2)
                    #turn red when energy less than 20%, else green
                    energy_remain = each.energy / alien.Midalien.energy
                    if energy_remain > 0.2:
                        energy_color = GREEN
                    else:
                        energy_color = RED
                    pygame.draw.line(screen,energy_color,\
                                     (each.rect.left,each.rect.top - 5),\
                                     (each.rect.left + each.rect.width * energy_remain,each.rect.top - 5),\
                                     2)

            for each in big_aliens.copy():
                if each.active:
                    if each.hit:
                        screen.blit(each.image_hit,each.rect)
                    else:
                        if switch_image:
                            screen.blit(each.image1,each.rect)
                        else:
                            screen.blit(each.image2,each.rect)
                    #draw energy bar
                    pygame.draw.line(screen,GRAY,\
                                     (each.rect.left,each.rect.top - 5),\
                                     (each.rect.right,each.rect.top - 5),\
                                     2)
                    #turn red when energy less than 20%, else green
                    energy_remain = each.energy / alien.Bigalien.energy
                    if energy_remain > 0.2:
                        energy_color = GREEN
                    else:
                        energy_color = RED
                    pygame.draw.line(screen,energy_color,\
                                     (each.rect.left,each.rect.top - 5),\
                                     (each.rect.left + each.rect.width * energy_remain,each.rect.top - 5),\
                                     2)

            #draw space ship
            if SpaceShip.active:
                if switch_image:
                    screen.blit(SpaceShip.image1,SpaceShip.rect)
                else:
                    screen.blit(SpaceShip.image2,SpaceShip.rect)
            else:
                #destroy
                screen.blit(SpaceShip.destroy_images[ship_destroy_index],SpaceShip.rect)

            #draw life number
            if life_num:
                for i in range(life_num):
                    screen.blit(life_image,(width-10-(i+1)*life_rect.width,height-10-life_rect.height))

            #draw coin number
            coin_text = coin_font.render("x%d" % coin_num,True,WHITE)
            text_rect = coin_text.get_rect()
            screen.blit(coin_image,(10,height - 10 - coin_rect.height))
            screen.blit(coin_text,(20 + coin_rect.width,height - 5 - text_rect.height))

            #draw score
            score_text = score_font.render("Scroe:%s" % str(score),True,WHITE)
            screen.blit(score_text,(10,5))

        #draw gameover screen
        elif life_num == 0:
            #stop bgm
            pygame.mixer.music.stop()
            #stop all sound
            pygame.mixer.stop()

            #highest
            record_score_text = score_font.render("Best:%d" % temp_record_score,True,WHITE)
            screen.blit(record_score_text,(50,50))
            #your score
            gameover_text1 = gameover_font.render("Your Score",True,WHITE)
            gameover_text1_rect = gameover_text1.get_rect()
            gameover_text1_rect.left,gameover_text1_rect.top = (width - gameover_text1_rect.width) //2,\
                                                               (height -gameover_text1_rect.height) // 4
            #new highest
            if not coin_num and record_flag:
                new_record1=new_record_font.render("New Highest!",True,WHITE)
                new_record2=new_record_font.render("New Highest!",True,GRAY)
                new_record1_rect=new_record1.get_rect()
                new_record2_rect=new_record2.get_rect()
                new_record1_rect.right,new_record1_rect.bottom=gameover_text1_rect.right,gameover_text1_rect.top+5
                new_record2_rect.right,new_record2_rect.bottom=gameover_text1_rect.right,gameover_text1_rect.top+5
                if delay%10>=5:
                    screen.blit(new_record1,new_record1_rect)
                else:
                    screen.blit(new_record2,new_record2_rect)
            screen.blit(gameover_text1,gameover_text1_rect)
            #score
            gameover_text2 = gameover_font.render(str(score),True,WHITE)
            gameover_text2_rect = gameover_text2.get_rect()
            gameover_text2_rect.left,gameover_text2_rect.top = (width - gameover_text2_rect.width) //2,\
                                                               gameover_text1_rect.bottom + 10
            screen.blit(gameover_text2,gameover_text2_rect)
            #coin and coin number
            gameover_coin_text = coin_font.render("x%d" % coin_num,True,WHITE)
            gameover_coin_text_rect = gameover_coin_text.get_rect()
            gameover_coin_rect=coin_image.get_rect()
            gameover_coin_rect.left,gameover_coin_rect.top=(width - gameover_coin_rect.width-gameover_coin_text_rect.width)//2,\
                                                            gameover_text2_rect.bottom + 10
            gameover_coin_text_rect.left,gameover_coin_text_rect.top=gameover_coin_rect.right+10,\
                                                                        gameover_coin_rect.top
            screen.blit(coin_image,gameover_coin_rect)
            screen.blit(gameover_coin_text,gameover_coin_text_rect)
            #restar botton
            restart_rect.left,restart_rect.top = (width - restart_rect.width) // 2,(gameover_coin_text_rect.bottom + 50)
            screen.blit(restart_image,restart_rect)
            #exit botton
            quit_rect.left, quit_rect.top = (width - quit_rect.width) // 2, restart_rect.bottom + 10
            screen.blit(quit_image,quit_rect)\
            
            if not coin_num and not recorded:
                recorded = True
                #read highest score
                with open("record.txt", "r") as f:
                    record_score = int(f.read())
                #if score higher than highest score, save
                if score > record_score:
                    with open("record.txt","w") as f:
                        f.write(str(score))
            #decrease coin number and add score
            if coin_num>0:
                #control speed of adding
                y=int(-0.04*coin_num+5)
                if y<1:
                    y=1
                if not(delay%y):
                    coin_num-=1
                    score+=100
                    if score>temp_record_score:
                        temp_record_score=score
                        if not record_flag:
                            record_flag=True

            #check mouse botton
            #if left botton pressed
            if pygame.mouse.get_pressed()[0]:
                #get mouse position
                pos = pygame.mouse.get_pos()
                #if click "Restart" botton, restart
                if restart_rect.left < pos[0] < restart_rect.right and restart_rect.top < pos[1] < restart_rect.bottom:
                    #reload main()
                    main()
                #if click "Exit"
                elif quit_rect.left < pos[0] < quit_rect.right and quit_rect.top < pos[1] < quit_rect.bottom:
                    pygame.quit()
                    sys.exit()


        #draw pause botton
        if life_num:
            screen.blit(paused_image,paused_rect)
        # flip the display screen
        pygame.display.flip()
        clock.tick(60)
        #switch pictures
        if not (delay % 5):
            switch_image = not switch_image
        delay -= 1
        if not delay:
            delay = 100
        #Increase delay to solve the problem of high cup occupancy rate
        time.sleep(0.01)

main()
