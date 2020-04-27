#main.py
from ship import Ship
n=int(input('input:'))  #Total number n of ships for the simulation
ships=[]
total_idle=0
hartime_list=[]
waitime_list=[]
for i in range(n):
    s=Ship()
    ships.append(s)
    if i==0:
        s.set_arrive(s.between)
        s.set_start(s.arrive)
        s.set_idle(s.arrive)
        total_idle+=s.idle
        hartime_list.append(s.harbor)
        waitime_list.append(s.wait)
    else:
        s.set_arrive(ships[i-1].arrive+s.between)
for i in range(n-1):
    collision=[]
    coli_index=[]
    for j in range(i+1,n):
        if ships[j].arrive<=ships[i].finish:
            collision.append(ships[j].unload)
            coli_index.append(j)
        else:
            break
    if len(collision):
        mini=coli_index[collision.index(min(collision))]
        ships[i+1],ships[mini]=ships[mini],ships[i+1]
        ships[i+1].set_start(ships[i].finish)
    else:
        ships[i+1].set_start(ships[i+1].arrive)
        ships[i+1].set_idle(ships[i+1].arrive-ships[i].finish)
        total_idle+=ships[i+1].idle
    hartime_list.append(ships[i+1].harbor)
    waitime_list.append(ships[i+1].wait)
'''for i in range(n):
    print(str(ships[i].between)+' '+str(ships[i].unload)+' '+\
            str(ships[i].arrive)+' '+str(ships[i].start)+' '+\
            str(ships[i].finish)+' '+str(ships[i].harbor))'''
HARTIME=sum(hartime_list)/n #Average time per ship in the harbor
MAXHAR=max(hartime_list)    #Maximum time of a ship in the harbor
WAITIME=sum(waitime_list)/n #Average waiting time per ship before unloading
MAXWAIT=max(waitime_list)   #Maximum waiting time of a ship
IDLETIME=total_idle/ships[n-1].finish #Percentage of total simulation time unloading facilities are idle
print('HARTIME:'+str(HARTIME)+'\nMAXHAR:'+str(MAXHAR)+'\nWAITIME:'+str(WAITIME)+'\nMAXWAIT:'+str(MAXWAIT)+'\nIDLETIME:'+str(IDLETIME))