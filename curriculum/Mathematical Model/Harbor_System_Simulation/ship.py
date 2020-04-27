#ship.py
import random

class Ship(object):
    def __init__(self):
        #Time between successive arrivals of Ships i and i - l 
        # (a random integer varying betweenl5 and 145 min)
        self.between=random.randint(15,145)
        #Time required to unload Ship i at the dock 
        # (a random integer varying between 45 and90 min)
        self.unload=random.randint(45,90)
        #Time from start of clock at t = 0 
        # when Ship i arrives at the harbor for unloading
        self.arrive=0
        #Time from start of clock at which Ship i commences its unloading
        self.start=0
        #Time for which dock facilities are idle immediately 
        # before commencement of unloading Ship i
        self.idle=0
        #Time Ship i waits in the harbor 
        # after arrival before unloading commences
        self.wait=self.start-self.arrive
        #Time from start of clock at which service for Ship i is completed 
        # at the unloading facilities
        self.finish=self.start+self.unload
        #Total time Ship i spends in the harbor
        self.harbor=self.finish-self.arrive

    def update(self):
        self.wait=self.start-self.arrive
        self.finish=self.start+self.unload
        self.harbor=self.finish-self.arrive
    
    def set_arrive(self,arrive):
        self.arrive=arrive

    def set_start(self,start):
        self.start=start
        self.update()

    def set_idle(self,idle):
        self.idle=idle