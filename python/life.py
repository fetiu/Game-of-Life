import copy
import pygame

def census(cells, x, y):
    count = 0;
    neighbors = [
        (x-1, y-1),
        (x-1, y),
        (x-1, y+1),
        (x, y-1),
        (x, y+1),
        (x+1, y-1),
        (x+1, y),
        (x+1, y+1),
    ]
    for cell in neighbors:
        if cell in cells:
            count+=1
            # print("near cell{}".format(cell))
    return count

class Game:
    def __init__(self, matrix):
        self.cells = []
        self.w = len(matrix)
        self.h = len(matrix)
        for y, line in enumerate(matrix):
            for x, v in enumerate(line):
                if v is not 0:
                    cell = (x,y)
                    self.cells.append(cell)
        print(self.cells)
        pygame.init()
        size = [self.w * 20 + 2, self.w * 20 + 2]
        self.canvas = pygame.display.set_mode(size)

    def update(self):
        tmp = copy.deepcopy(self.cells)
        for y in range(self.h):
            for x in range(self.w):
                n = census(tmp, x, y)
                cell = (x,y)
                alive = False;

                if cell in self.cells:
                    alive = True;

                if alive:
                    if not (n == 2 or n == 3):
                        self.cells.remove(cell)
                        # print("kill cell{}".format(cell))
                else:
                    if n == 3:
                        self.cells.append(cell)
                        # print("new cell{}".format(cell))

    def show(self):
        white = (255,255,255)
        self.canvas.fill(white)
        green = (25,100,40)
        for x,y in self.cells:
            pygame.draw.rect(self.canvas, green, (x*20+2,y*20+2,18,18), 0)
        pygame.display.update()






