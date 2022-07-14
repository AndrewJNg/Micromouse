
const int mazeWidth = 4 ;
const int mazeHeight = 3;

int target_X[] = {3};
int target_Y[] = {2};

int start_X[] = {0};
int start_Y[] = {0};

int curr_X_coor = 0;
int curr_Y_coor = 0;
byte curr_dir = 0  ;

byte target_dir = 0;


int possible_route[2] = {0, 0};

struct cell
{
  int cost;
  bool bottomCell;
  bool leftCell;
  bool visitCell;
};

struct cell ***mazePtr = NULL; // pointer pointing to first node in queue


void printMap() {
  OLED.clearDisplay();
  OLED.setTextSize(1);
  OLED.setTextColor(SSD1306_WHITE);
  OLED.setCursor(0, 0);     // Start at top-left corner

  // draw top layer of the maze
  for (int x = 0; x < mazeWidth ; x++)
  {
    Serial.print("o");
    OLED.print("o");
    if (mazePtr[x][mazeHeight]->bottomCell == 1)
    {
      //      Serial.print("---");
      OLED.print("--");
    }
    else
    {
      //      Serial.print("   ");
      OLED.print("  ");
    }
  }
  //  Serial.print("o");
  //  Serial.println();
  OLED.print("o");
  OLED.println();


  for (int y = mazeHeight - 1; y >= 0; y--)
  {
    for (int x = 0; x < mazeWidth + 1; x++ )
    {
      //      Serial.print(" ");
      if (mazePtr[x][y]->leftCell == 1)
      {
        //        Serial.print("|");
        OLED.print("|");
      }
      else
      {
        //        Serial.print(" ");
        OLED.print(" ");
      }
      //      Serial.print("    ");

      if (mazePtr[x][y]->cost == 0)
      {
        OLED.print(" X");
      }
      else if (x == curr_X_coor && y == curr_Y_coor)
      {
        if (curr_dir == 0)OLED.print(" ^");
        else if (curr_dir == 1)OLED.print(" >");
        else if (curr_dir == 2)OLED.print(" v");
        else if (curr_dir == 3)OLED.print(" <");

      }
      else if (mazePtr[x][y]->cost >= 100)
      {
        OLED.print("  ");
      }
      else if (mazePtr[x][y]->cost >= 10)
      {
        OLED.print(mazePtr[x][y]->cost);
      }
      else
      {
        OLED.print(" ");
        OLED.print(mazePtr[x][y]->cost);
      }
      //      OLED.print("  ");

    }
    //    Serial.println();
    OLED.println();

    for (int x = 0; x < mazeWidth ; x++)
    {
      //      Serial.print("o");
      OLED.print("o");
      if (mazePtr[x][y]->bottomCell == 1)
      {
        //        Serial.print("---");
        OLED.print("--");
      }
      else
      {
        //        Serial.print("   ");
        OLED.print("  ");
      }
    }
    //    Serial.print("o");
    OLED.print("o");
    //    Serial.println();
    OLED.println();
  }
  //  Serial.println();
  OLED.println();
  OLED.display();

}

void printArray( ) {
  //  for (int y = mazeHeight - 1; y >= 0; y--)
  //  {
  //    for (int x = 0; x < mazeWidth; x++)
  //    {
  //
  //      Serial.print(mazePtr[x][y]->cost);
  //      Serial.print("   ");
  //    }
  //    Serial.println();
  //  }

}

void update_mms()
{
  //  for (int j = 0; j < mazeHeight ; j++)
  //  {
  //    for (int i = 0; i < mazeWidth ; i++)
  //    {
  //
  //    }
  //  }
}


void setWall(int x, int y, char Dir)
{
  if (Dir == 'n')  mazePtr[x][y + 1] ->bottomCell = 1;
  else if (Dir == 's') mazePtr[x][y] ->bottomCell = 1;
  else if (Dir == 'w') mazePtr[x][y] ->leftCell = 1;
  else if (Dir == 'e') mazePtr[x + 1][y] ->leftCell  = 1;
}

void flood_fill(int target_x[],  int target_y[], int Size)
{
  // reset all values to 300
  for (int x = 0; x < mazeWidth; x++)
  {
    for (int y = 0; y < mazeHeight; y++)
    {
      mazePtr[x][y] -> cost = 300;
    }
  }

  // set 0 for goal

  for (int x = 0; x < Size ; x++)
  {
    for (int y = 0; y < Size; y++)
    {
      mazePtr[target_x[x]][target_y[y]] -> cost = 0;
    }
  }

  // set varaibles for floodfill
  boolean value_flag = 1;
  int value = 0;

  //    printArray();

  while (value_flag == 1)
  {
    value_flag = 0;

    for (int x = 0; x < mazeWidth; x++)
    {
      for (int y = 0; y < mazeHeight; y++)
      {


        if (mazePtr[x][y]->cost == value)
        {
          if ((x < mazeWidth - 1) && ((mazePtr[x + 1][y]->leftCell) == 0) && ((mazePtr[x + 1][y]->cost) > value))
          { // looking to the right
            mazePtr[x + 1][y]->cost = value + 1;
            value_flag = 1;
          }
          if ((y < mazeHeight - 1) && ((mazePtr[x][y + 1]->bottomCell) == 0) && ((mazePtr[x][y + 1]->cost) > value))
          { // looking to the right
            mazePtr[x][y + 1]->cost = value + 1;
            value_flag = 1;
          }
          if ((x > 0) && ((mazePtr[x][y]->leftCell) == 0) && ((mazePtr[x - 1][y]->cost) > value))
          { // looking to the right
            mazePtr[x - 1][y]->cost = value + 1;
            value_flag = 1;
          }
          if ((y > 0) && ((mazePtr[x][y]->bottomCell) == 0) && ((mazePtr[x][y - 1]->cost) > value))
          { // looking to the right
            mazePtr[x][y - 1]->cost = value + 1;
            value_flag = 1;
          }
        }
      }
    }
    value = value + 1 ;

  }



  //  printArray();



}

void FloodFill_setup()
{

  // allocate space for the cells needed for the map size
  mazePtr = (struct cell ***)malloc(mazeHeight * mazeWidth * sizeof(struct cell));
  for (int x = 0; x < mazeWidth + 1; x++)
  {
    mazePtr[x] = (struct cell **)malloc(mazeHeight * sizeof(struct cell));
    for (int y = 0; y < mazeHeight + 1; y++)
    {
      mazePtr[x][y] = (struct cell *)malloc(sizeof(struct cell));
      mazePtr[x][y]->cost = 300;
      mazePtr[x][y]->leftCell = 0;
      mazePtr[x][y]->bottomCell = 0;
      mazePtr[x][y]->visitCell = 0;
    }
  }



  //add borders to the map
  // add horizontal borders at the top and bottom of the map
  for (int i = 0; i < mazeWidth ; i++) {
    setWall(i, 0, 's');
    setWall(i, mazeHeight - 1, 'n');
  }

  // add vertical borders at the left and right of the map
  for (int i = 0; i < mazeHeight ; i++) {
    setWall(0, i, 'w');
    setWall(mazeWidth - 1, i, 'e');
  }


  //  printArray();
}

// convert 0-3 to characters for north south east and west
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

// move the robot given the direction and if the movement should be virtual (software move) or real (move robot in real world)
void move(int dir, int Virtual)
{
  target_dir = dir;
  int turn_value = target_dir - curr_dir;
  curr_dir = target_dir;

  if (Virtual == 0)
  {
        mazePtr[curr_X_coor][curr_Y_coor]->visitCell = 1;
    if (turn_value == 0)
    {
      //      Serial.println("Forward");
      move_forward_cells();
      // Serial.println("forward");
    }
    else if ((turn_value == 1) || (turn_value == -3))
    {
      //      Serial.print("TurnRight ");
      //      Serial.println("Forward");
      turn(90);
      move_forward_cells();
    }
    else if ((turn_value == 2) || (turn_value == -2))
    {
      //      Serial.print("TurnLeft ");
      //      Serial.print("TurnLeft ");
      //      Serial.println("Forward");

      turn(-90);
      turn(-90);
      move_forward_cells();
    }
    else if ((turn_value == 3) || (turn_value == -1))
    {
      //      Serial.print("TurnLeft ");
      //      Serial.println("Forward");
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
printMap();

}


void decide_path(boolean Virtual)
{
  int Current = mazePtr[curr_X_coor][curr_Y_coor]->cost;
  int  top = mazePtr[curr_X_coor][curr_Y_coor + 1]->cost;
  int  right = mazePtr[curr_X_coor + 1][curr_Y_coor]->cost;


  int  left = 1;
  if (curr_X_coor > 0) left = mazePtr[curr_X_coor - 1][curr_Y_coor]->cost;
  int  bottom = 1;
  if (curr_Y_coor > 0)   bottom = mazePtr[curr_X_coor][curr_Y_coor - 1]->cost;

  if ((top < Current) && (mazePtr[curr_X_coor][curr_Y_coor + 1]->bottomCell == 0))
    move(0, Virtual);
  else if ((right < Current) && (mazePtr[curr_X_coor + 1][curr_Y_coor]->leftCell == 0))
    move(1, Virtual);
  else if ((bottom < Current) && (mazePtr[curr_X_coor][curr_Y_coor]->bottomCell == 0))
    move(2, Virtual);
  else if ((left < Current) && (mazePtr[curr_X_coor][curr_Y_coor]->leftCell  == 0))
    move(3, Virtual);
  //  else
  //    Serial.println("help");
//    printMap();
  //  printArray();
}

void scan()
{
  if (IRVal[0] > 1000 && IRVal[5] > 1000) // scan wallFront()
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
  while (mazePtr[curr_X_coor][curr_Y_coor]->cost != 0)
  {
    //    Serial.print(curr_X_coor);
    //    Serial.print("  ");
    //    Serial.print(curr_Y_coor);
    //    Serial.println("  ");
    if (mazePtr[curr_X_coor][curr_Y_coor]->visitCell == 1)
    {
      decide_path(0);
    }
    else
    {
      scan();
      flood_fill(target_X, target_Y, sizeof(target_X) / sizeof(target_X[0]));
      decide_path(0);
    }
    printMap() ;
//    delay(1000);
  }
  //  delay(5000);
  //  Serial.println("Goal");

  //return path
  flood_fill(start_X, start_Y, sizeof(start_X) / sizeof(start_X[0]));
  printMap() ;
  //    while (grid_layout[curr_X_coor][curr_Y_coor] != 1)
  while (mazePtr[curr_X_coor][curr_Y_coor]->cost != 0)
  {
    if (mazePtr[curr_X_coor][curr_Y_coor]->visitCell == 1)
    {
      decide_path(0);
    }
    else
    {
      scan();
      flood_fill(start_X, start_Y, sizeof(start_X) / sizeof(start_X[0]));
      //      update_mms();
      decide_path(0);
    }
    printMap() ;
//    delay(1000);
  }

  // reset facing correct direction
  int target_dir = 0;
  int turn_value = target_dir - curr_dir;
  curr_dir = target_dir;
  if (turn_value == 0)
  {
    move_forward_cells();
  }
  else if ((turn_value == 1) || (turn_value == -3))
  {
    turn(90);
  }
  else if ((turn_value == 2) || (turn_value == -2))
  {
    turn(-90);
    turn(-90);
  }
  else if ((turn_value == 3) || (turn_value == -1))
  {
    turn(-90);
  }
}

void clearMap()
{
  // reset map conditions
  for (int x = 0; x < mazeWidth; x++)
  {
    for (int y = 0; y < mazeHeight; y++)
    {
      mazePtr[x][y] -> cost = 300;
      mazePtr[x][y] -> leftCell = 0;
      mazePtr[x][y] -> bottomCell = 0;
      mazePtr[x][y] -> visitCell = 0;
    }
  }

  //set know boundaries to the map
  // add horizontal borders at the top and bottom of the map
  for (int i = 0; i < mazeWidth ; i++) {
    setWall(i, 0, 's');
    setWall(i, mazeHeight - 1, 'n');
  }

  // add vertical borders at the left and right of the map
  for (int i = 0; i < mazeHeight ; i++) {
    setWall(0, i, 'w');
    setWall(mazeWidth - 1, i, 'e');
  }
}
