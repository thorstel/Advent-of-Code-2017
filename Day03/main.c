#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************
 *                               PART 1                               *
 **********************************************************************/

/*
 * Distance pattern:
 * (1 2)         (1 2)         (1 2)     (1 2)
 * (3 2 3 4)     (3 2 3 4)     (3 2 3 4) (3 2 3 4)
 * (5 4 3 4 5 6) (5 4 3 4 5 6) ...
 */
static unsigned int calc_dist(unsigned int dest)
{
    assert(dest != 0);
    if (dest == 1) { return 1; }

    unsigned int curr_dist;
    unsigned int curr_width = 2;

    while (true)
    {
        for (size_t i = 0; i < 4; ++i)
        {
            curr_dist = curr_width;
            for (size_t j = 0; j < (curr_width / 2); ++j)
            {
                --curr_dist;
                --dest;
                if (dest == 1) { return curr_dist; }
            }

            for (size_t j = 0; j < (curr_width / 2); ++j)
            {
                ++curr_dist;
                --dest;
                if (dest == 1) { return curr_dist; }
            }
        }

        curr_width += 2;
    }
}

/**********************************************************************
 *                               PART 2                               *
 **********************************************************************/

enum direction
{
    MOVE_RIGHT   = 0,
    MOVE_UP      = 1,
    MOVE_LEFT    = 2,
    MOVE_DOWN    = 3,
    MOVE_DIR_MAX = 4
};

static inline enum direction next_dir(enum direction dir)
{
    return ((dir + 1) % MOVE_DIR_MAX);
}

static inline bool pos_in_bounds(int pos_x, int pos_y, size_t width)
{
    return ((pos_x >= 0) &&
            (pos_x < (int)width) &&
            (pos_y >= 0) &&
            (pos_y < (int)width));
}

static inline unsigned int neighbor_sum(
        const unsigned int* grid,
        int                 pos_x,
        int                 pos_y,
        size_t              width)
{
    unsigned int sum = 0u;
    for (int i = -1; i <= 1; ++i)
    {
        for (int j = -1; j <= 1; ++j)
        {
            if (pos_in_bounds((pos_x + j), (pos_y + i), width))
            {
                sum += grid[((pos_y + i) * width) + (pos_x + j)];
            }
        }
    }

    return sum;
}

static inline void direction_delta(
        enum direction dir,
        int*           delta_x,
        int*           delta_y)
{
    switch (dir)
    {
    case MOVE_DOWN:
        *delta_x = 0;
        *delta_y = 1;
        break;

    case MOVE_LEFT:
        *delta_x = -1;
        *delta_y = 0;
        break;

    case MOVE_RIGHT:
        *delta_x = 1;
        *delta_y = 0;
        break;

    case MOVE_UP:
        *delta_x = 0;
        *delta_y = -1;
        break;

    default:
        assert(false);
    }
}

static inline bool change_dir(
        const unsigned int* grid,
        enum direction      dir,
        int                 pos_x,
        int                 pos_y,
        size_t              width)
{
    int dir_x = 0;
    int dir_y = 0;
    direction_delta(next_dir(dir), &dir_x, &dir_y);

    if (pos_in_bounds((pos_x + dir_x), (pos_y + dir_y), width))
    {
        return (grid[((pos_y + dir_y) * (int)width) + (pos_x + dir_x)] == 0u);
    }
    else
    {
        return false;
    }
}

static void print_grid(const unsigned int* grid, size_t width)
{
    for (size_t i = 0; i < width; ++i)
    {
        for (size_t j = 0; j < width; ++j)
        {
            printf("%10u ", grid[(i * width) + j]);
        }
        printf("\n");
    }
}

static int64_t build_spiral(size_t radius, unsigned int threshold)
{
    const size_t  width = 1u + (2u * radius);
    unsigned int* grid  = NULL;

    if ((grid = calloc((width * width), sizeof(unsigned int))) == NULL)
    {
        return -1;
    }

    unsigned int   curr_value = 0u;
    enum direction curr_dir   = MOVE_RIGHT;
    int            pos_x      = (int)(width / 2);
    int            pos_y      = (int)(width / 2);
    int            dir_x      = 0;
    int            dir_y      = 0;

    direction_delta(curr_dir, &dir_x, &dir_y);
    grid[(pos_y * width) + pos_x] = 1;

    while (pos_in_bounds((pos_x + dir_x), (pos_y + dir_y), width))
    {
        pos_x += dir_x;
        pos_y += dir_y;

        curr_value = neighbor_sum(grid, pos_x, pos_y, width);
        grid[(pos_y * width) + pos_x] = curr_value;

        if (change_dir(grid, curr_dir, pos_x, pos_y, width))
        {
            curr_dir = next_dir(curr_dir);
            direction_delta(curr_dir, &dir_x, &dir_y);
        }

        if (curr_value > threshold) { break; }
    }

    print_grid(grid, width);
    free(grid);
    return (curr_value > threshold) ? (int64_t)curr_value : -1;
}

int main(int argc, const char* argv[])
{
    if (argc < 2)
    {
        printf("Pass input via argument!\n");
        return 1;
    }

    unsigned int input = (unsigned int)atoi(argv[1]);
    printf("dist = %u\n", calc_dist(input));
    printf("next = %I64d\n", build_spiral((argc > 2 ? atoi(argv[2]) : 5), input));
    return 0;
}

