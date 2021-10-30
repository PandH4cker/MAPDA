# MAPDA 

MAPDA (aka Maze Automatic Path Detection Aiming) is a maze generator and solver.

Each maze cells are unsigned short int (16 bits) 
which contain infos about the cell configuration (walls) 
and also utilities infos that help the solver (visited cell, cell in the path, visited above..)
during the maze solving part.

## Installation:
### Windows:
You need to install [cmake](https://cmake.org/install/) first to then build the project.

```bash
git clone git@github.com:MrrRaph/MAPDA.git
cmake 
cd ./build
cmake --build .
./MAPDA
```

### Linux:
```bash
git clone git@github.com:MrrRaph/MAPDA.git
make
```

## Usage:
In order to generate a maze 20x40:
```bash
./MAPDA -r 20 40
```

Or from a file:
```bash
./MAPDA -f filename
```

![img.png](img.png)