import sys, pygame, time
import random
from pygame.locals import *
pygame.init()

class matrix:
    def __init__(self, path):
        f = open(path, 'r')
        lines = f.readlines()
        self.status = [[x == '1' for x in list(row)[0:len(row)-1]] for row in lines]
        #slice row to eliminate line feed.
        self.height = len(self.status)
        self.width = len(self.status[0])
        
        self.count = [[0]*self.width for row in range(self.height)]
        for y in range(self.height):
            for x in range(self.width):
                self.count[y][x] = self.__count__()
        #print(self.count)

        
    #def __adjacent__:
    
    
    def __count__(self):
        return random.randrange(0,8)

    def update_generation(self):
        
        for y in range(self.height):
            for x in range(self.width):
                if self.status[y][x] == False and self.count[y][x] == 3:
                        self.status[y][x] = True
                        #birth
                elif not (self.count[y][x] == 3 or self.count[y][x] == 3):
                        self.status[y][x] = False
                        #death

    def print_status(self):
        display.fill((255,255,255))
        
        for y in range(self.height):
            for x in range(self.width):
                if self.status[y][x] == True:
                    if self.count[y][x] == 3:
                        color = (25,100,40)
                    else:
                        color = (123,201,111)
                else: color = (240,240,240)
                pygame.draw.rect(display,color,(x*20+2,y*20+2,18,18),0)
        pygame.display.update()


#fname = input('insert a file name that contains initial matrix: ');
cells = matrix('map.txt')

resolution = width, height = cells.width*20+2,cells.height*20+2
display = pygame.display.set_mode(resolution);


t = int(input('how many cycle do you want?: '))
i = 0
while t > i:
    cells.print_status();
    i+=1
    cells.update_generation();
    time.sleep(5)
