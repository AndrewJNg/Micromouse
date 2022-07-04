from calendar import c
from pickle import FALSE
from random import random
from turtle import distance
import API
import sys

def log(string):
    sys.stderr.write("{}\n".format(string))
    sys.stderr.flush()



def setup():
    API.setColor(curr_X_coor, curr_Y_coor, "G")
    for i in range(API.mazeHeight()):
        setWall(0,i,"w")
        setWall(API.mazeWidth()-1,i,"e")
        
    for i in range(API.mazeWidth()):
        setWall(i,0,"s")
        setWall(i,API.mazeHeight()-1,"n")

curr_X_coor = 0
curr_Y_coor = 0
target_X = [21,22,23]#[7,8]#[13,14]#[3]#[7,8]#[21,22,23]
target_Y = [25,26,27]#[7,8]#[5,6]#[1]#[7,8]#[25,26,27]
curr_dir = 0  
target_dir = 0



grid_layout = [[300 for y in range(API.mazeHeight()+1)] for x in range(API.mazeWidth()+1)]
#[number]
grid_wall = [[[0, 0] for y in range(API.mazeHeight()+1)] for x in range(API.mazeWidth()+1)]
#[bottom_wall,left_wall]
grid_known_cell = [[0 for y in range(API.mazeHeight()+1)] for x in range(API.mazeWidth()+1)]
#[known-cell (0-new cell, 1-old cell)]

possible_route = [0,0]

def update_mms():
    
    global grid_layout

    for x in range(API.mazeWidth()):
        for y in range(API.mazeHeight()):
            API.setText(x, y, grid_layout[x][y])
            if grid_known_cell[x][y] == 0:
                pass
            elif grid_known_cell[x][y] == 1:
                API.setColor(x,y,"G")
            elif grid_known_cell[x][y] == -1:
                API.setColor(x,y,"A")


    


def flood_fill(target_X,target_Y):
    
    flagX = []
    flagY = []

    #clear all previous readings
    for x in range(API.mazeWidth()):
        for y in range(API.mazeHeight()):
            grid_layout[x][y] = 300
    
    value =0
    for x in target_X:
        for y in target_Y:
            API.setColor(x, y, "R")
            grid_layout[x][y] = 0
            flagX.append(x)
            flagY.append(y)
            value +=1   

    # log(flagX)
    # log(flagY)   

    


    # while value_flag ==1:
        # value_flag = 0
    
    # flagX[0]
    # flagY[0]
    
        # for x in range(API.mazeWidth()):
            # for y in range(API.mazeHeight()):
                # if grid_layout[x][y]<grid_layout[curr_X_coor][curr_Y_coor]:  #enable for faster search
    
    value_flag =1
    value = 0
    
    while value_flag==1:
        value_flag =0
        listX = flagX.copy()
        listY = flagY.copy()

        flagX.clear()
        flagY.clear()

        for i in range(len(listX)):
            # log(i)
            x = listX[i]
            y = listY[i]

            # log("("+str(x)+","+str(y)+")")
            # flagValue = 0
            
            if grid_layout[x][y]==value:
                if grid_layout[x][y]<grid_layout[curr_X_coor][curr_Y_coor]:  #enable for faster search
                        if x < API.mazeWidth()-1 and grid_wall[x+1][y][1]==0 and grid_layout[x+1][y] > value:
                            if grid_layout[x+1][y]!=value+1:
                                grid_layout[x+1][y]=value+1 # looking to the right
                                value_flag = 1
                                flagX.append(x+1)
                                flagY.append(y)
                        if y < API.mazeHeight()-1 and grid_wall[x][y+1][0]==0 and grid_layout[x][y+1] > value:
                            if grid_layout[x][y+1]!=value+1:
                                grid_layout[x][y+1]=value+1 # looking to the top
                                value_flag = 1
                                flagX.append(x)
                                flagY.append(y+1)
                        if x > 0 and grid_wall[x][y][1]==0 and grid_layout[x-1][y] > value:  
                            if grid_layout[x-1][y]!=value+1:
                                grid_layout[x-1][y]=value+1 # looking to the left
                                value_flag = 1
                                flagX.append(x-1)
                                flagY.append(y)
                        if y > 0 and grid_wall[x][y][0]==0 and grid_layout[x][y-1] > value: 
                            if grid_layout[x][y-1]!=value+1:
                                grid_layout[x][y-1]=value+1 # looking to the bottom
                                value_flag = 1
                                flagX.append(x)
                                flagY.append(y-1)
             
        value += 1   
        # update_mms()
        # log(flagX)
        # log(flagY)
        # log("length: "+str(len(flagX)))
        # log(value)


        

    # log("done")





    # update_mms()
    
    # while True:
        # pass
   
# value_flag =1
# value = 0
"""
    while value_flag ==1:
        value_flag = 0
        for x in range(API.mazeWidth()):
            for y in range(API.mazeHeight()):
                # if grid_layout[x][y]<grid_layout[curr_X_coor][curr_Y_coor]:  #enable for faster search
                    
                    if grid_layout[x][y]==value:  
                        if x < API.mazeWidth()-1 and grid_wall[x+1][y][1]==0 and grid_layout[x+1][y] > value:
                            grid_layout[x+1][y]=value+1 # looking to the right
                            value_flag = 1
                        if y < API.mazeHeight()-1 and grid_wall[x][y+1][0]==0 and grid_layout[x][y+1] > value:
                            grid_layout[x][y+1]=value+1 # looking to the top
                            value_flag = 1
                        if x > 0 and grid_wall[x][y][1]==0 and grid_layout[x-1][y] > value:  
                            grid_layout[x-1][y]=value+1 # looking to the left
                            value_flag = 1
                        if y > 0 and grid_wall[x][y][0]==0 and grid_layout[x][y-1] > value: 
                            grid_layout[x][y-1]=value+1 # looking to the bottom
                            value_flag = 1

        value = value+1   
"""



def dir2cardinal(dir):
    if dir == -1:
        dir = 3
    elif dir == 4:
        dir = 0

    if dir == 0:
        return "n"
    elif dir == 1:
        return "e"
    elif dir == 2:
        return "s"
    elif dir == 3:
        return "w"

def decide_path(virtual=0):
    # global variables needed
    global curr_X_coor
    global curr_Y_coor
    global curr_dir
    global target_dir


    
    # select best path
    
    current = grid_layout[curr_X_coor][curr_Y_coor]
    top = grid_layout[curr_X_coor][curr_Y_coor+1]
    left = grid_layout[curr_X_coor-1][curr_Y_coor]
    right = grid_layout[curr_X_coor+1][curr_Y_coor]
    bottom = grid_layout[curr_X_coor][curr_Y_coor-1]

    if  right < current and grid_wall[curr_X_coor+1][curr_Y_coor][1] == 0:
        move(1,virtual) #move right
    elif top  < current and grid_wall[curr_X_coor][curr_Y_coor+1][0] == 0:
        move(0,virtual) #move up
    elif left < current and grid_wall[curr_X_coor][curr_Y_coor][1] == 0:
        move(3, virtual) #move down
    elif bottom < current and grid_wall[curr_X_coor][curr_Y_coor][0] == 0:
        move(2,virtual) #move left
    else:
        log("help")   

    
    
    
def scan():
    if API.wallFront() == 1:
        setWall(curr_X_coor,curr_Y_coor,dir2cardinal(curr_dir))
        
    if API.wallLeft() == 1:
        setWall(curr_X_coor,curr_Y_coor,dir2cardinal(curr_dir-1))
        
    if API.wallRight() == 1:
        setWall(curr_X_coor,curr_Y_coor,dir2cardinal(curr_dir+1))
        

def setWall(x,y,D):
    API.setWall(x,y,D)
    if D == "n":
        grid_wall[x][y+1][0] = 1
    if D == "s":
        grid_wall[x][y][0] = 1
    if D == "w":
        grid_wall[x][y][1] = 1
    if D == "e":
        grid_wall[x+1][y][1] = 1

    
def move(dir,virtual):
    global curr_dir
    global target_dir
    global curr_X_coor
    global curr_Y_coor

    target_dir =dir
    turn_value = target_dir-curr_dir 
    curr_dir = target_dir
    
    # make the necessary moves to turn in the correct direction
    if virtual == 0:
        
        grid_known_cell[curr_X_coor][curr_Y_coor] = 1
        if turn_value == 0:
            API.moveForward()
            
        elif turn_value == 1 or turn_value == -3:
            API.turnRight()
            API.moveForward()
            
        elif turn_value == 2 or turn_value == -2:
            API.turnLeft()
            API.turnLeft()
            API.moveForward()
            
        elif turn_value == 3 or turn_value == -1:
            API.turnLeft()
            API.moveForward()

    
    # update our coordinate system
    if curr_dir == 0 :
            curr_Y_coor = curr_Y_coor + 1 
    elif curr_dir == 1 :
            curr_X_coor = curr_X_coor + 1 
    elif curr_dir == 2 :
            curr_Y_coor = curr_Y_coor - 1 
    elif curr_dir == 3 :
            curr_X_coor = curr_X_coor - 1
    
    

"""
def sample_map_setup():
    for i in range(2,16):
        setWall(1,i,"e")
    #grid_known_cell[4][5] = 1
"""
      
def first_Search():
    while grid_layout[curr_X_coor][curr_Y_coor] != 0 :
        if grid_known_cell[curr_X_coor][curr_Y_coor] ==1:
            decide_path()
        else :
            scan()
            flood_fill(target_X,target_Y)
            update_mms()
            decide_path()
    log("Goal")
    # exit search
    
    flood_fill([0],[0])
    while grid_layout[curr_X_coor][curr_Y_coor] != 1 :
        if grid_known_cell[curr_X_coor][curr_Y_coor] ==1:
            decide_path()
        else :
            scan()
            flood_fill([0],[0])
            update_mms()
            decide_path()
    
    
def possible_better_path():
    global curr_X_coor
    global curr_Y_coor
    global curr_dir  
    global target_X
    global target_Y
    global possible_route
    
    
    initial_X_coor = curr_X_coor
    initial_Y_coor = curr_Y_coor
    initial_dir = curr_dir 
    curr_X_coor = 0
    curr_Y_coor = 0
    curr_dir =0

    path_flag =1
    flood_fill(target_X,target_Y)
    while grid_layout[curr_X_coor][curr_Y_coor] != 0 :
        path_flag =0
        log("possible_better_path?")

        flood_fill(target_X,target_Y)
        while grid_layout[curr_X_coor][curr_Y_coor] != 0 :
            decide_path(virtual=1)
            if grid_known_cell[curr_X_coor][curr_Y_coor]==0: 
                path_flag+=1
                if path_flag ==1 :
                    possible_route = [curr_X_coor,curr_Y_coor]
                
                    
        flood_fill([0],[0])
        while grid_layout[curr_X_coor][curr_Y_coor] != 0 :
            decide_path(virtual=1)
            if grid_known_cell[curr_X_coor][curr_Y_coor]==0: 
                path_flag+=1
                if path_flag ==1 :
                        possible_route = [curr_X_coor,curr_Y_coor]
                
    curr_X_coor = initial_X_coor
    curr_Y_coor = initial_Y_coor
    curr_dir = initial_dir
    # log(path_flag)
    if path_flag > 0: return (path_flag)
    else: return (0)
        


def path_check():
    value = 1
    while value:
        value = possible_better_path()
        log(value)
        # if value <20:
        log(possible_route)
        travel(possible_route[0],possible_route[1])
            
        #move to the goal to update this cell
        scan()
        grid_known_cell[curr_X_coor][curr_Y_coor] = 1
        flood_fill(target_X,target_Y)
        #flood_fill([possible_route[0]],[possible_route[1]])
        update_mms()
            #decide_path()
        # else:
        #     travel(target_X[0],target_Y[0])
        #     flood_fill([0],[0])
        #     while grid_layout[curr_X_coor][curr_Y_coor] != 1 :
        #         if grid_known_cell[curr_X_coor][curr_Y_coor] ==1:
        #             decide_path()
        #         else :
        #             scan()
        #             flood_fill([0],[0])
        #             update_mms()
        #             decide_path()
    log("best path found")
    travel(0,0)
  
def speed_run():
    log("speed run")
    
    flood_fill(target_X,target_Y)
    update_mms()
    while grid_layout[curr_X_coor][curr_Y_coor] != 0 :
        decide_path()

    flood_fill([0],[0])
    update_mms()
    while grid_layout[curr_X_coor][curr_Y_coor] != 0 :
        decide_path()
            
    update_mms()

def travel(X,Y):
        flood_fill([X],[Y])
        while grid_layout[curr_X_coor][curr_Y_coor] != 0 :
            if grid_known_cell[curr_X_coor][curr_Y_coor] ==1:
                decide_path()
            else :
                scan()
                flood_fill([X],[Y])
                update_mms()
                decide_path()
        

def loop():
    
    # travel(2,0)
    # travel(6,0)
    # travel(4,2)
    # travel(7,2)
    # travel(6,4)
    # travel(0,1)
    # travel(1,4)
    # travel(0,7)
    # travel(3,6)
    # travel(6,7)
    # travel(0,0)
    
    # first search
    first_Search()
    
    # search for better path
    path_check()

    
    #speed run
    while True:
        speed_run()
        pass
   
        
    














def main():
    log("Running...")
    setup()
    
    while True:
        loop()

if __name__ == "__main__":
    main()
