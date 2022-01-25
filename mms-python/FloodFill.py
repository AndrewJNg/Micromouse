from calendar import c
from random import random
from turtle import distance
import API
import sys

def log(string):
    sys.stderr.write("{}\n".format(string))
    sys.stderr.flush()



def setup():
    API.setColor(curr_X_coor, curr_Y_coor, "G")
    for i in range(16):
        setWall(0,i,"w")
        setWall(15,i,"e")
        setWall(i,0,"s")
        setWall(i,15,"n")

curr_X_coor = 0
curr_Y_coor = 0
target_X = [7,8]
target_Y = [7,8]
curr_dir = 0  
target_dir = 0
grid_layout = [[[300, 0, 0] for y in range(API.mazeHeight()+1)] for x in range(API.mazeWidth()+1)]
#[number]
grid_wall = [[[0, 0] for y in range(API.mazeHeight()+1)] for x in range(API.mazeWidth()+1)]
#[top_wall,right_wall]
grid_known_cell = [[[0] for y in range(API.mazeHeight()+1)] for x in range(API.mazeWidth()+1)]
#[known-cell (0-new cell, 1-old cell,-1-dead end cell)]

def update_mms():
    global grid_layout
    for x in range(API.mazeWidth()):
        for y in range(API.mazeHeight()):
            API.setText(x, y, grid_layout[x][y][0])
            
            if grid_known_cell[x][y] == 0:
                pass
            elif grid_known_cell[x][y] == 1:
                API.setColor(x,y,"G")
            elif grid_known_cell[x][y] == -1:
                API.setColor(x,y,"A")


    


def flood_fill(target_X,target_Y):
    
    #clear all previous readings
    for x in range(API.mazeWidth()):
        for y in range(API.mazeHeight()):
            grid_layout[x][y][0] = 300
    
    for x in target_X:
        for y in target_Y:
            API.setColor(x, y, "R")
            grid_layout[x][y][0] = 0
    
    global max_value
    value_flag =1
    value = 0
    while value_flag ==1:
        value_flag = 0
        for x in range(API.mazeWidth()):
            for y in range(API.mazeHeight()):
                if grid_layout[x][y][0]==value:  
                    if x < API.mazeWidth()-1 and grid_wall[x][y][1]==0 and grid_layout[x+1][y][0] > value:
                        grid_layout[x+1][y][0]=value+1 # looking to the right
                        value_flag = 1
                    if y < API.mazeHeight()-1 and grid_wall[x][y][0]==0 and grid_layout[x][y+1][0] > value:
                        grid_layout[x][y+1][0]=value+1 # looking to the top
                        value_flag = 1
                    if x > 0 and grid_wall[x-1][y][1]==0 and grid_layout[x-1][y][0] > value:  
                        grid_layout[x-1][y][0]=value+1 # looking to the left
                        value_flag = 1
                    if y > 0 and grid_wall[x][y-1][0]==0 and grid_layout[x][y-1][0] > value: 
                        grid_layout[x][y-1][0]=value+1 # looking to the bottom
                        value_flag = 1

        value = value+1                  
    max_value = value

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

def decide_path():
    # global variables needed
    global curr_X_coor
    global curr_Y_coor
    global curr_dir
    global target_dir


    
    # select best path
    
    current = grid_layout[curr_X_coor][curr_Y_coor][0]
    top = grid_layout[curr_X_coor][curr_Y_coor+1][0]
    left = grid_layout[curr_X_coor-1][curr_Y_coor][0]
    right = grid_layout[curr_X_coor+1][curr_Y_coor][0]
    bottom = grid_layout[curr_X_coor][curr_Y_coor-1][0]

    if  top  < current and grid_wall[curr_X_coor][curr_Y_coor][0] == 0:
        move(0)
    elif right < current and grid_wall[curr_X_coor][curr_Y_coor][1] == 0:
        move(1)
    elif bottom < current and grid_wall[curr_X_coor][curr_Y_coor-1][0] == 0:
        move(2)
    elif left < current and grid_wall[curr_X_coor-1][curr_Y_coor][1] == 0:
        move(3)
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
        grid_wall[x][y][0] = 1
    if D == "s":
        grid_wall[x][y-1][0] = 1
    if D == "w":
        grid_wall[x-1][y][1] = 1
    if D == "e":
        grid_wall[x][y][1] = 1

    
def move(dir):
    global curr_dir
    global target_dir
    global curr_X_coor
    global curr_Y_coor

    target_dir =dir
    turn_value = target_dir-curr_dir 
    curr_dir = target_dir
    
    # make the necessary moves to turn in the correct direction
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
    
    grid_known_cell[curr_X_coor][curr_Y_coor] = 1
    


def sample_map_setup():
    for i in range(2,16):
        setWall(1,i,"e")
    #grid_known_cell[4][5] = 1

def mark_deadend():
    
    for x in range(API.mazeWidth()):
        for y in range(API.mazeHeight()):
            wall_mark = 0
            if x ==0 and y ==0:
                grid_known_cell[0][0] = 1
            else:
                if grid_wall[x][y][0] ==1 : wall_mark+=1
                if grid_wall[x][y][1] ==1 : wall_mark+=1
                if grid_wall[x][y-1][0] ==1 : wall_mark+=1
                if grid_wall[x-1][y][1] ==1 : wall_mark+=1

                if wall_mark >=3: # or grid_layout[x][y] == max_value
                    grid_known_cell[x][y] = -1
                    grid_wall[x][y][0] =1
                    grid_wall[x][y][1] =1
                    grid_wall[x][y-1][0]=1
                    grid_wall[x-1][y][1]=1

    for x in range(API.mazeWidth(),0,-1):
        for y in range(API.mazeHeight(),0,-1):
            wall_mark = 0
            if x ==0 and y ==0:
                grid_known_cell[0][0] = 1
            else:
                if grid_wall[x][y][0] ==1 : wall_mark+=1
                if grid_wall[x][y][1] ==1 : wall_mark+=1
                if grid_wall[x][y-1][0] ==1 : wall_mark+=1
                if grid_wall[x-1][y][1] ==1 : wall_mark+=1

                if wall_mark >=3: # or grid_layout[x][y] == max_value
                    grid_known_cell[x][y] = -1
                    grid_wall[x][y][0] =1
                    grid_wall[x][y][1] =1
                    grid_wall[x][y-1][0]=1
                    grid_wall[x-1][y][1]=1
def path_check():
    pass
        

        



def loop():
    global curr_X_coor
    global curr_Y_coor
    global curr_dir
    global start_square_value
    
    # first search
    while grid_layout[curr_X_coor][curr_Y_coor][0] != 0 :
        scan()
        flood_fill(target_X,target_Y)
        update_mms()
        decide_path()
        
    log("Goal")
    flood_fill([0],[0])
    #mark_deadend() 
    update_mms()
    
    # exit search
    while grid_layout[curr_X_coor][curr_Y_coor][0] != 1 :
        scan()
        flood_fill([0],[0])
        update_mms()
        decide_path()
    
    # search for better path
    log("searching for better path")
    flood_fill(target_X,target_Y)
    #mark_deadend()
    update_mms()

    #path_check()
    while grid_layout[curr_X_coor][curr_Y_coor][0] != 0 :
        scan()
        flood_fill(target_X,target_Y)
        update_mms()
        decide_path()
    while grid_layout[curr_X_coor][curr_Y_coor][0] != 0 :
        scan()
        flood_fill([0],[0])
        update_mms()
        decide_path()
    
    

    #speed run
    log("speed run")
    while True:
        mark_deadend()
        flood_fill(target_X,target_Y)
        update_mms()
        while grid_layout[curr_X_coor][curr_Y_coor][0] != 0 :
            decide_path()

        flood_fill([0],[0])
        update_mms()
        while grid_layout[curr_X_coor][curr_Y_coor][0] != 0 :
            scan()
            flood_fill([0],[0])
            update_mms()
            decide_path()
            
        update_mms()
  
    














def main():
    log("Running...")
    setup()
    
    while True:
        loop()

if __name__ == "__main__":
    main()
