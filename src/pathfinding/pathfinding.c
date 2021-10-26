//
// Created by drayr on 25/10/2021.
//

#include "../../includes/pathfinding/pathfinding.h"
#include "../../includes/utils/bits.h"

int findPath(Maze * maze)
{
    if (maze->cells[maze->entrypoint.y][maze->entrypoint.x].cellValue == 15 ||
        maze->cells[maze->out.y][maze->out.x].cellValue == 15)
        return -1;

    //Entry visited
    SET_BIT(maze->cells[maze->entrypoint.y][maze->entrypoint.x].cellValue, 8);

    if (maze->resolver.x != maze->out.x || maze->resolver.y != maze->out.y)
    {
        if (!isLeftUncrossable(maze->cells[maze->resolver.y][maze->resolver.x]) &&
            !CHECK_BIT(maze->cells[maze->resolver.y][maze->resolver.x - 1].cellValue, 8))
        {
            --maze->resolver.x;
            SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 6);
            SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 9);
        }

        else if (!isAboveUncrossable(maze->cells[maze->resolver.y][maze->resolver.x]) &&
                 !CHECK_BIT(maze->cells[maze->resolver.y - 1][maze->resolver.x].cellValue, 8))
        {
            --maze->resolver.y;
            SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 5);
            SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 9);
        }

        else if (!isRightUncrossable(maze->cells[maze->resolver.y][maze->resolver.x]) &&
                 !CHECK_BIT(maze->cells[maze->resolver.y][maze->resolver.x + 1].cellValue, 8))
        {
            ++maze->resolver.x;
            SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 4);
            SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 9);
        }

        else if (!isBelowUncrossable(maze->cells[maze->resolver.y][maze->resolver.x]) &&
                 !CHECK_BIT(maze->cells[maze->resolver.y + 1][maze->resolver.x].cellValue, 8))
        {
            ++maze->resolver.y;
            SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 7);
            SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 9);
        }

        else if (maze->resolver.x == maze->entrypoint.x && maze->resolver.y == maze->entrypoint.y)
            return -1;

        else
        {
            // Si je viens de la droite
            if (CHECK_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 6))
            {
                CLEAR_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 9);
                ++maze->resolver.x;
            }
            //Je retourne à droite
            //Si je viens du bas
            else if (CHECK_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 5))
            {
                CLEAR_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 9);
                ++maze->resolver.y;
            }
            else if (CHECK_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 4))
            {
                CLEAR_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 9);
                --maze->resolver.x;
            }
            else if (CHECK_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 7))
            {
                CLEAR_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 9);
                --maze->resolver.y;
            }
        }

        SET_BIT(maze->cells[maze->resolver.y][maze->resolver.x].cellValue, 8);
        return 1;
    }
    return 0;
}