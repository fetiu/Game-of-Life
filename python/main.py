import life
import time

if __name__ == "__main__":
    input = [
        [0,1,1,1,0],
        [0,0,0,0,0],
        [0,1,1,1,0],
        [0,0,0,0,0],
        [0,0,0,0,0],
    ]

    game = life.Game(input)

    for a in range(100):
        game.show()
        game.update()

        # cells = game.get_cells()

        # print(cells)

        time.sleep(5)

