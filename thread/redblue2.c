#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

/* tag
WHITE 0
RED 1
BLUE 2
OUT 3
IN 4
*/

// struct for thread data
struct thread_data {
  int id;
  int row_column_begin;
  int row_column_end;
  int tile_begin;
  int tile_end;
};

// struct for barrier function
typedef struct {
  pthread_mutex_t count_lock;
  pthread_cond_t ok_to_proceed;
  int count;
} mylib_barrier_t;

int *grid_1D;                         // one-dimension version of grid
int **grid;                           // two-dimension grid
int *grid_1D_copy;                    // the copy of one-dimension version of grid
int **grid_copy;                              // the copy of the initial two-dimension grid
int num_threads, n, t, max_iters;
float c;
int tile_volume;                  // the number of tile in the grid
int tile_number;
int i, j;
int finished = 0;                     // the flag OF whether the iteration finished or not
int n_iters = 0;                              // the iteration times
int redcount = 0, bluecount = 0;          // the count of red and blue
mylib_barrier_t barrier;               // barrier struct

// barrier initialization
void mylib_barrier_init(mylib_barrier_t *b)
{
  b->count = 0;
  pthread_mutex_init(&(b->count_lock), NULL);
  pthread_cond_init(&(b->ok_to_proceed), NULL);
}

// barrier function
void mylib_barrier(mylib_barrier_t *b, int num_threads)
{
  pthread_mutex_lock(&(b->count_lock));
  b->count = b->count + 1;
  if (b->count == num_threads)
    {
      b->count = 0;
      pthread_cond_broadcast(&(b->ok_to_proceed));
    }
  else
    {
      while (pthread_cond_wait(&(b->ok_to_proceed), &(b->count_lock)) != 0)
        ;
    }
  pthread_mutex_unlock(&(b->count_lock));
}

// barrier destroy
void mylib_barrier_destroy(mylib_barrier_t *b)
{
  pthread_mutex_destroy(&(b->count_lock));
  pthread_cond_destroy(&(b->ok_to_proceed));
}

// create 2-D array and corresponding 1-D array
void creat_gird(int col, int row, int **grid_1D, int ***grid)
{
  int count = col * row;

  *grid_1D = (int*)malloc(sizeof(int) * count);
  *grid = (int**)malloc(sizeof(int *) * row);
  int i;

  for (i = 0; i < row; i++)
    {
      (*grid)[i] = &((*grid_1D)[i * col]);
    }
}

// initialize the grid
void init_grid(int n, int ***grid)
{
  time_t s;

  srand((unsigned)time(&s));
  int i, j;

  for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
        {
          (*grid)[i][j] = rand() % 3;
        }
    }
}

// print the grid
void print_grid(int n, int ***grid)
{
  int i, j;

  for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
        {
          printf("%d", (*grid)[i][j]);
        }
      printf("\n");
    }
}

// calculate the tasks distributed to each thread
int *distribute_task_for_processes(int num_threads, int num_tasks)
{
  int *task = (int*)malloc(sizeof(int) * (num_threads));
  int base = num_tasks / num_threads;
  int remaining = num_tasks % num_threads;
  int i;

  for (i = 0; i < num_threads; i++){
      task[i] = base;
  }

  for (i = 0; i < remaining; i++)
    {
      task[i] = task[i] + 1;
    }

  return task;
}

// red color movement
void red_move(int col, int begin, int end, int ***grid)
{
  int i, j;

  for (i = begin; i < end; i++)
    {
      if ((*grid)[i][0] == 1 && (*grid)[i][1] == 0)
        {
          (*grid)[i][0] = 4;
          (*grid)[i][1] = 3;
        }
      for (j = 1; j < col; j++)
        {
          if ((*grid)[i][j] == 1 && ((*grid)[i][(j + 1) % col] == 0))
            {
              (*grid)[i][j] = 0;
              (*grid)[i][(j + 1) % col] = 3;
            }
          else if ((*grid)[i][j] == 3)
            (*grid)[i][j] = 1;
        }
      if ((*grid)[i][0] == 3)
        (*grid)[i][0] = 1;
      else if ((*grid)[i][0] == 4)
        (*grid)[i][0] = 0;
    }
}

// blue color movement
void blue_move(int row, int begin, int end, int ***grid)
{
  int i, j;

  for (j = begin; j < end; j++)
    {
      if ((*grid)[0][j] == 2 && (*grid)[1][j] == 0)
        {
          (*grid)[0][j] = 4;
          (*grid)[1][j] = 3;
        }
      for (i = 1; i < row; i++)
        {
          if ((*grid)[i][j] == 2 && (*grid)[(i + 1) % row][j] == 0)
            {
              (*grid)[i][j] = 0;
              (*grid)[(i + 1) % row][j] = 3;
            }
          else if ((*grid)[i][j] == 3)
            (*grid)[i][j] = 2;
        }
      if ((*grid)[0][j] == 3)
        (*grid)[0][j] = 2;
      else if ((*grid)[0][j] == 4)
        (*grid)[0][j] = 0;
    }
}

// check whether there is any tile over the threshold
int analyze_result(int ***grid, int begin, int end, int tile_volume, int n, int t, float c)
{
  int tile_row, tile_column;
  int redcount = 0, bluecount = 0;
  float red_ratio, blue_ratio;
  int finished = 0;
  int i, j, k;

  for (i = begin; i < end; i++)
    {
      tile_row = i / t;
      tile_column = i % t;
      for (j = (n / t) * tile_row; j < (n / t) * tile_row + (n / t); j++)
        {
          for (k = (n / t) * tile_column; k < (n / t) * tile_column + (n / t); k++)
            {
              if ((*grid)[j][k] == 1)
                {
                  redcount = redcount + 1;
                }
              if ((*grid)[j][k] == 2)
                {
                  bluecount = bluecount + 1;
                }
            }
        }

      red_ratio = redcount * 100 / tile_volume;
      blue_ratio = bluecount * 100 / tile_volume;
      if (blue_ratio > c && red_ratio > c)
        {
          printf("In tile %d, both the red and the blue over the threshold.\n", i + 1);
          finished = 1;
        }

      if (blue_ratio < c && red_ratio > c)
        {
          printf("In tile %d, the red color over the threshold.\n", i + 1);
          finished = 1;
        }

      if (blue_ratio > c && red_ratio < c)
        {
          printf("In tile %d, the blue color over the threshold.\n", i + 1);
          finished = 1;
        }
      redcount = 0;
      bluecount = 0;
    }
  return finished;
}

void *red_blue_computation(void *thread_arg)
{
  int finished_flag = 0;
  int iters_p = 0;   // the iteration times
  struct thread_data *my_data = (struct thread_data *)thread_arg;

  while (!finished && iters_p < max_iters)
    {
      iters_p = iters_p + 1;   // renew the iteration number

      red_move(n, my_data->row_column_begin, my_data->row_column_end, &grid);
      mylib_barrier(&barrier, num_threads);
      blue_move(n, my_data->row_column_begin, my_data->row_column_end, &grid);
      mylib_barrier(&barrier, num_threads);
      finished_flag = analyze_result(&grid, my_data->tile_begin, my_data->tile_end, tile_volume, n, t, c);
      if (finished_flag == 1)
        {
          finished = finished_flag;
        }
      mylib_barrier(&barrier, num_threads);
    }

  if (my_data->id == 0)
    {
      n_iters = iters_p;
    }

  pthread_exit(NULL);
}

// sequential movement
void sequential_computation(int ***grid, int n, int t, float c, int max_iters)
{
  int finished = 0;
  int iters = 0;

  printf("\n");
  printf("The sequential computation result: \n");

  while (!finished && iters < max_iters)
    {
      iters = iters + 1;// count for the iteration number

      red_move(n, 0, n, grid);
      blue_move(n, 0, n, grid);

      finished = analyze_result(grid, 0, tile_number, tile_volume, n, t, c);
    }
  printf("After %d interations, the final grid: \n", iters);
  print_grid(n, grid);
}

// self-checking program
void self_check(int ***grid, int ***grid_copy, int n)
{
  int flag = 0;
  int i, j;

  for (i = 0; i < n; i++)
    {
      for (j = 0; j < n; j++)
        {
          if ((*grid)[i][j] != (*grid_copy)[i][j])
            {
              flag = 1;
              break;
            }
          if (flag == 1)
            {
              break;
            }
        }
    }

  printf("\n");
  if (flag == 0)
    {
      printf("Self-chech: The result of parallel program is the same as sequential program.\n");
      printf("            Means the result of the parallel movement is correct.\n");
    }
  else
    {
      printf("Self-chech: The result of parallel program is not the same as sequential program.\n");
      printf("            Means the result of the parallel movement is wrong.\n");
    }
  printf("\n");
}

int main(int argc, char **argv)
{
    if (argc != 6)
      {
        printf("Illegal arguments.\n");
        printf("Please enter the command in the following format:\n");
        printf("./pthreads_red_blue_computation [the number of threads] [cell grid size] [tile grid size] [terminating threshold(%)] [maximum number of iterations]\n");
        printf("Note: [cell grid size] %% [tile grid size] = 0; [the number of threads >= 0]\n");
        printf("\n");
        return 0;
      }

    num_threads = atoi(argv[1]);
    n = atoi(argv[2]);
    t = atoi(argv[3]);
    c = atoi(argv[4]);
    max_iters = atoi(argv[5]);

  if ((n % t != 0) || (num_threads < 0))
    {
      printf("Illegal arguments.\n");
      printf("Please enter the command in the following format:\n");
      printf("./pthreads_red_blue_computation [the number of threads] [cell grid size] [tile grid size] [terminating threshold] [maximum number of iterations]\n");
      printf("Note: [cell grid size] %% [tile grid size] = 0; [the number of threads >= 0]\n");
      printf("\n");
      return 0;
    }

  tile_volume = (n * n) / (t * t);
  tile_number = t * t;
  pthread_t threads[num_threads];        //id of pthread
  struct thread_data thread_data_array[num_threads];

  int *row_task = distribute_task_for_processes(num_threads, n);
  int *tile_task = distribute_task_for_processes(num_threads, tile_number);

  // initialize the barrier
  mylib_barrier_init(&barrier);

  creat_gird(n, n, &grid_1D, &grid);
  creat_gird(n, n, &grid_1D_copy, &grid_copy);

  init_grid(n, &grid);

  memcpy(grid_1D_copy, grid_1D, sizeof(int) * n * n);

  printf("The initial grid: \n");
  print_grid(n, &grid); // 打印grid

  // distribute the workload among the threads
  for (i = 0; i < num_threads; i++)
    {
      // initialize the struct argument
      thread_data_array[i].id = i;
      if (i == 0)
        {
          thread_data_array[i].row_column_begin = 0;
          thread_data_array[i].tile_begin = 0;
        }
      else
        {
          thread_data_array[i].row_column_begin = thread_data_array[i - 1].row_column_end;
          thread_data_array[i].tile_begin = thread_data_array[i - 1].tile_end;
        }
      thread_data_array[i].row_column_end = thread_data_array[i].row_column_begin + row_task[i];
      thread_data_array[i].tile_end = thread_data_array[i].tile_begin + tile_task[i];

      pthread_create(&threads[i], NULL, red_blue_computation, (void*)&thread_data_array[i]);
    }

  printf("\n");
  printf("The parallel computation result: \n");
  for (i = 0; i < num_threads; i++)
    {
      pthread_join(threads[i], NULL);
    }
  printf("After %d interations, the final grid: \n", n_iters);
  print_grid(n, &grid);

  //analyze_result(&grid, 0, tile_number, tile_volume, n, t, c);

  sequential_computation(&grid_copy, n, t, c, max_iters);
  self_check(&grid, &grid_copy, n);

  // clean up and exit
  mylib_barrier_destroy(&barrier);
  pthread_exit(NULL);
}