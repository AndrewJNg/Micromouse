
const int mazeHeight = 3;
const int mazeWidth = 5;

int target_X[] = {1};
int target_Y[] = {1};

int curr_X_coor = 0;
int curr_Y_coor = 0;
byte curr_dir = 0  ;

byte target_dir = 0;



int grid_layout [mazeHeight + 1][mazeWidth + 1];
//#[number]

int grid_wall  [mazeHeight + 1][mazeWidth + 1][2];
//[bottom_wall,left_wall]

int grid_known_cell [mazeHeight + 1][mazeWidth + 1] ;
//#[known-cell (0-new cell, 1-old cell)]

int possible_route[2] = {0, 0};


void printMap() {
  OLED.clearDisplay();
  OLED.setTextSize(1);
  OLED.setTextColor(SSD1306_WHITE);
  OLED.setCursor(0, 0);     // Start at top-left corner

  for (int j = mazeHeight; j >= 0; j--)
  {
    //    Serial.print(j);
    //    Serial.print(" ");

    for (int i = 0; i < mazeWidth + 1 ; i++)
    {
      if (grid_wall[i][j][1] == 1)
      {
        OLED.print("|");
      }
      else
      {
        OLED.print(" ");
      }
      OLED.print("  ");
    }
    OLED.println();


    for (int i = 0; i < mazeWidth; i++)
    {
      OLED.print("o");
      if (grid_wall[i][j][0] == 1)
      {
        OLED.print("--");
      }
      else
      {
        OLED.print("  ");
      }
    }
    OLED.print("o");
    OLED.println();
  }
  OLED.println();
  //  Serial.println();
  OLED.display();
}

void printArray( ) {

  //  for (int j = mazeHeight - 1; j >= 0; j--)
  //  {
  //    //      Serial.print(j);
  //    //      Serial.print(" ");
  //    for (int i = 0; i < mazeWidth; i++)
  //    {
  //      Serial.print(grid_layout[i][j]);
  //      Serial.print(" ");
  //      //      Serial.print(grid_wallt[i][j][1]);
  //      Serial.print(" ");
  //
  //    }
  //    Serial.println();
  //  }
}

//void update_mms()
//{
//  for (int j = 0; j < mazeHeight ; j++)
//  {
//    for (int i = 0; i < mazeWidth ; i++)
//    {
//
//    }
//  }
//}


void setWall(int x, int y, char Dir)
{
  if (Dir == 'n') grid_wall[x][y + 1][0] = 1;
  else if (Dir == 's') grid_wall[x][y ][0] = 1;
  else if (Dir == 'w') grid_wall[x ][y][1] = 1;
  else if (Dir == 'e') grid_wall[x + 1][y][1] = 1;


}
void flood_fill(int target_x[],  int target_y[], int Size)
{
  // reset all values to 255
  for (int x = 0; x < mazeWidth; x++)
  {
    for (int y = 0; y < mazeHeight; y++)
    {
      grid_layout[x][y] = 255;
    }
  }

  // set 0 for goal
  //  Serial.println("size :");
  //  Serial.println(Size);

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

    for (int x = 0; x < mazeWidth; x++)
    {
      for (int y = 0; y < mazeHeight; y++)
      {


        if (grid_layout[x][y] == value)
        {
          if ((x < mazeWidth - 1) && (grid_wall[x + 1][y][1] == 0) && (grid_layout[x + 1][y] > value))
          { // looking to the right
            grid_layout[x + 1][y] = value + 1;
            value_flag = 1;
          }
          if ((y < mazeHeight - 1) && (grid_wall[x][y + 1][0] == 0) && (grid_layout[x][y + 1] > value))
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





}

void FloodFill_setup()
{

  for (int j = mazeWidth; j >= 0; j--)
  {
    for (int i = 0; i < mazeHeight + 1; i++)
    {
      grid_layout[i][j] = 255;
      grid_wall[i][j][0] = 0;
      grid_wall[i][j][1] = 0;
      grid_known_cell[i][j] = 0;
    }
  }


    for (int i = 0; i < mazeWidth ; i++) {
      setWall(i,0, 's');
      setWall(i,mazeHeight-1, 'n');
    }
  
    for (int i = 0; i < mazeHeight ; i++) {
      setWall(0,i, 'w');
      setWall(mazeWidth-1,i, 'e');
    }
//  setWall(0, 0, 'n');
//  setWall(0, 0, 'w');
  //      grid_wall[0][3][0] = 1;
  //      grid_wall[0][3][1] = 1;
  //
  //    // add borders to the end of maze
  //    for (int j = mazeHeight + 1; j > 0; j--)
  //    {
  //      for (int i = 0; i < mazeWidth; i++)
  //      {
  //        grid_layout[i][j] = 255;
  //        grid_wall[i][j][0] = 0;  // bottom
  //        grid_wall[i][j][1] = 0; //left
  //        grid_known_cell[i][j] = 0;
  //      }
  //    }

  //    for (int i = 0 ; i < mazeHeight; i++)
  //    {
  //      setWall(0, i, 'w');
  //      setWall(mazeWidth - 1, i, 'e');
  //    }
  //    for (int i = 0 ; i < mazeWidth; i++)
  //    {
  //      setWall(i, 0, 's');
  //      setWall(i, mazeHeight - 1, 'n');
  //    }



  //  for (int i = 0; i < mazeHeight ; i++)
  //  {
  //    setWall(0, i, 'w');
  //    setWall(mazeWidth - 1, i, 'e');
  //  }
  //  for (int i = 0; i < mazeWidth ; i++)
  //  {
  //    setWall(i, 0, 's');
  //    setWall(i, mazeHeight, 'n');
  //  }

  //    setWall(0, 0, 'w');
  //  flood_fill(target_X, target_Y, sizeof(target_X) / sizeof(target_X[0]));
  //  printArray();
}

char dir2cardinal(int dir)
{
  char result = ' ';
  if (dir == -1) dir = 3;
  else if (dir == 4) dir = 0;

  if (dir == 0) result = 'n';
  else if (dir == 1) result = 'e';
  else if (dir == 2) result = 's';
  else if (dir == 3) result = 'w';
  return result;
}

void move(int dir, int Virtual)
{
  target_dir = dir;
  int turn_value = target_dir - curr_dir;
  curr_dir = target_dir;

  if (Virtual == 0)
  {
    grid_known_cell[curr_X_coor][curr_Y_coor] = 1;
    if (turn_value == 0)
      move_forward_cells();

    else if ((turn_value == 1) || (turn_value == -3))
    {
      turn(90);
      move_forward_cells();
    }
    else if ((turn_value == 2) || (turn_value == -2))
    {
      turn(-90);
      turn(-90);
      move_forward_cells();
    }
    else if ((turn_value == 3) || (turn_value == -1))
    {
      turn(-90);
      move_forward_cells();
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
    move(0, Virtual);
  else if ((right < Current) && (grid_wall[curr_X_coor + 1][curr_Y_coor][1] == 0))
    move(1, Virtual);
  else if ((bottom < Current) && (grid_wall[curr_X_coor][curr_Y_coor][0] == 0))
    move(2, Virtual);
  else if ((left < Current) && (grid_wall[curr_X_coor][curr_Y_coor][1] == 0))
    move(3, Virtual);
  //  else
  //    Serial.println("help");
  printMap();
  printArray();
}

void scan()
{
  if (IRVal[0] > 1000 || IRVal[5] > 1000) // scan wallFront()
  {
    setWall(curr_X_coor, curr_Y_coor, dir2cardinal(curr_dir));
  }
  if (IRVal[2] > 1000) // scan wallLeft()
  {
    setWall(curr_X_coor, curr_Y_coor, dir2cardinal(curr_dir - 1));
  }
  if (IRVal[3] > 1000) // scan wallRight()
  {
    setWall(curr_X_coor, curr_Y_coor, dir2cardinal(curr_dir + 1));
  }
}

void first_Search()
{
  flood_fill(target_X, target_Y, sizeof(target_X) / sizeof(target_X[0]));
  while (grid_layout[curr_X_coor][curr_Y_coor] != 0)
  {
    //    Serial.print(curr_X_coor);
    //    Serial.print("  ");
    //    Serial.print(curr_Y_coor);
    //    Serial.println("  ");
    if (grid_known_cell[curr_X_coor][curr_Y_coor] == 1)
    {
      decide_path(0);
    }
    else
    {
      scan();
      flood_fill(target_X, target_Y, sizeof(target_X) / sizeof(target_X[0]));
      decide_path(0);
    }

  }
  //  delay(5000);
  //  Serial.println("Goal");

  //return path
  flood_fill(0, 0, 1);
  //    while (grid_layout[curr_X_coor][curr_Y_coor] != 1)
  while (grid_layout[curr_X_coor][curr_Y_coor] != 0)
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
  }
}
