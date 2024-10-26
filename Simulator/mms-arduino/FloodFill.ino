

const int target_X[] = {7, 8};
const int target_Y[] = {7, 8};

int curr_X_coor = 0;
int curr_Y_coor = 0;
byte curr_dir = 0  ;

byte target_dir = 0;



int grid_layout [mazeheight][mazewidth];

int grid_wall  [mazeheight + 1][mazewidth + 1][2];
//int grid_wall_bottom  [mazeheight + 1][mazewidth + 1];
//int grid_wall_left  [mazeheight + 1][mazewidth + 1];

//int grid_known_cell [mazeheight][mazewidth] ;

int possible_route[2] = {0, 0};


void printArray( ) {

  for (int j = mazeheight - 1; j >= 0; j--)
  {
    //      Serial.print(j);
    //      Serial.print(" ");
    for (int i = 0; i < mazewidth; i++)
    {
      //      Serial.print(i);
      //      Serial.print(" ");
      Serial.print(grid_layout[i][j]);
      Serial.print(" ");

    }
    Serial.println();
  }
}

void update_mms()
{
//  log(grid_known_cell[0][0);
grid_known_cell[7][7] =-1;
  for (int y = 0; y < mazeheight ; y++)
  {
    for (int x = 0; x < mazewidth ; x++)
    {
//      setText(x, y, String(grid_layout[x][y]));
      if (grid_known_cell[x][y] == 0)
      {}
      else if (grid_known_cell[x][y] == 1)
       {setColor(x, y, 'G');}
      else if (grid_known_cell[x][y] == -1)
       {setColor(x, y, 'A');}
    }
  }
}


void SetWall(int x, int y, char Dir)
{
  if (Dir == 'n') grid_wall[x][y + 1][0] = 1;
  else if (Dir == 's') grid_wall[x][y ][0] = 1;
  else if (Dir == 'w') grid_wall[x ][y][1] = 1;
  else if (Dir == 'e') grid_wall[x + 1][y][1] = 1;


}
void flood_fill(int target_x[],  int target_y[], int Size)
{
  // reset all values to 255
  for (int x = 0; x < mazewidth; x++)
  {
    for (int y = 0; y < mazeheight; y++)
    {
      grid_layout[x][y] = 255;

    }
  }
  //  grid_layout[2][2] = 0;

  // set 0 for goal
  //  Serial.println("size :");
  //  Serial.println(Size);
  //  Serial.println(target_x[2]);

  //  Serial.println((sizeof(Array) / sizeof(Array[0] )));
  for (int x = 0; x < Size ; x++)
  {
    for (int y = 0; y < Size; y++)
    {
      grid_layout[target_x[x]][target_y[y]] = 0;
      //            Serial.print(target_X[x]);
      //            Serial.print("  " );
      //            Serial.print(target_Y[y]);
      //            Serial.print("  " );
    }

  }
  //  Serial.println();

  // set varaibles for floodfill
  boolean value_flag = 1;
  int value = 0;

  //  printArray();
  //  Serial.println("1");

  while (value_flag == 1)
  {
    value_flag = 0;

    for (int x = 0; x < mazewidth; x++)
    {
      for (int y = 0; y < mazeheight; y++)
      {


        if (grid_layout[x][y] == value)
        {
          if ((x < mazewidth - 1) && (grid_wall[x + 1][y][1] == 0) && (grid_layout[x + 1][y] > value))
          { // looking to the right
            grid_layout[x + 1][y] = value + 1;
            value_flag = 1;
          }
          if ((y < mazeheight - 1) && (grid_wall[x][y + 1][0] == 0) && (grid_layout[x][y + 1] > value))
          { // looking to the right
            grid_layout[x][y + 1] = value + 1;
            value_flag = 1;
          }
          if ((x > 0) && (grid_wall[x][y][1] == 0) && (grid_layout[x - 1][y] > value))
          { // looking to the right
            grid_layout[x - 1][y] = value + 1;
            value_flag = 1;
          }
          if ((y > 0) && (grid_wall[x][y][0] == 0) && (grid_layout[x][y - 1] > value))
          { // looking to the right
            grid_layout[x][y - 1] = value + 1;
            value_flag = 1;
          }
        }
      }
    }
    value = value + 1 ;


  }
  printArray();
  Serial.println();
  Serial.println();





}

void FloodFill_setup()
{

  for (int j = mazeheight + 1; j > 0; j--)
  {
    for (int i = 0; i < mazewidth + 1; i++)
    {
      grid_layout[i][j] = 255;
      grid_wall[i][j][0] = 0;
      grid_wall[i][j][1] = 0;
      grid_known_cell[i][j] = 0;
    }
  }


  for (int i = 0; i < mazeheight ; i++)
  {
    SetWall(0, i, 'w');
    SetWall(mazewidth - 1, i, 'e');
  }
  for (int i = 0; i < mazewidth ; i++)
  {
    SetWall(i, 0, 's');
    SetWall(i, mazeheight, 'n');
  }

  //  flood_fill(target_X, target_Y, sizeof(target_X) / sizeof(target_X[0]));
  //  printArray();
}

int dir2cardinal(int dir)
{
  if (dir == -1) dir = 3;
  else if (dir == 4) dir = 0;

  if (dir == 0) dir = 'n';
  else if (dir == 1) dir = 'e';
  else if (dir == 2) dir = 's';
  else if (dir == 3) dir = 'w';
}

void Move(int dir, int Virtual)
{
  target_dir = dir;
  int turn_value = target_dir - curr_dir;
  curr_dir = target_dir;

  if (Virtual == 0)
  {
    grid_known_cell[curr_X_coor][curr_Y_coor] = 1;
    if (turn_value == 0)
      moveForward();

    else if ((turn_value == 1) || (turn_value == -3))
    {
      turnRight();
      moveForward();
    }
    else if ((turn_value == 2) || (turn_value == -2))
    {
      turnLeft();
      turnLeft();
      moveForward();
    }
    else if ((turn_value == 3) || (turn_value == -1))
    {
      turnLeft();
      moveForward();
    }
  }

  if (curr_dir == 0)
    curr_Y_coor = curr_Y_coor + 1 ;
  else if ( curr_dir == 1 )
    curr_X_coor = curr_X_coor + 1 ;
  else if ( curr_dir == 2 )
    curr_Y_coor = curr_Y_coor - 1 ;
  else if ( curr_dir == 3 )
    curr_X_coor = curr_X_coor - 1;


}

void decide_path(boolean Virtual)
{
  int Current = grid_layout[curr_X_coor][curr_Y_coor];
  int  top = grid_layout[curr_X_coor][curr_Y_coor + 1];
  int  left = grid_layout[curr_X_coor - 1][curr_Y_coor];
  int  right = grid_layout[curr_X_coor + 1][curr_Y_coor];
  int  bottom = grid_layout[curr_X_coor][curr_Y_coor - 1];

  if ((top < Current) && (grid_wall[curr_X_coor][curr_Y_coor + 1][0] == 0))
    Move(0, Virtual);
  else if ((right < Current) && (grid_wall[curr_X_coor + 1][curr_Y_coor][1] == 0))
    Move(1, Virtual);
  else if ((bottom < Current) && (grid_wall[curr_X_coor][curr_Y_coor][0] == 0))
    Move(2, Virtual);
  else if ((left < Current) && (grid_wall[curr_X_coor][curr_Y_coor][1] == 0))
    Move(3, Virtual);
  else
    Serial.println("help");
}

void scan()
{
  if (wallFront() == 1) // scan wallFront()
  {
    SetWall(curr_X_coor, curr_Y_coor, dir2cardinal(curr_dir));
  }
  if (wallLeft() == 1) // scan wallLeft()
  {
    SetWall(curr_X_coor, curr_Y_coor, dir2cardinal(curr_dir - 1));
  }
  if (wallRight() == 1) // scan wallRight()
  {
    SetWall(curr_X_coor, curr_Y_coor, dir2cardinal(curr_dir + 1));
  }
}

void first_Search()
{
  while (grid_layout[curr_X_coor][curr_Y_coor] != 0)
  {
    if (grid_known_cell[curr_X_coor][curr_Y_coor] == 1)
    {
      decide_path(0);
    }
    else
    {
      scan();
      flood_fill(target_X, target_Y, sizeof(target_X) / sizeof(target_X[0]));
      //      update_mms();
      decide_path(0);
      //      Serial.println("test");
    }
    //    motor_Speed[0] = 0;
    //    motor_Speed[1] = 0;
    //    motor(motor_Speed);
    //    delay(10000);
  }
  /*
    Serial.println("Goal");

    //return path
    flood_fill(0, 0, 1);
    while (grid_layout[curr_X_coor][curr_Y_coor] != 1)
    {
    if (grid_known_cell[curr_X_coor][curr_Y_coor] == 1)
    {
      decide_path(0);
    }
    else
    {
      scan();
      flood_fill(0, 0, 1);
      //      update_mms();
      decide_path(0);
    }
    }*/
}
