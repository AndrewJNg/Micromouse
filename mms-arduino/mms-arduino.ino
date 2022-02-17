const int mazeheight = 16;
const int mazewidth = 16;
int grid_known_cell [mazeheight][mazewidth] ;
void setup() {
  Serial.begin(19200);
  FloodFill_setup();
  //    update_mms();
  //setColor(7, 7, 'G');
  grid_known_cell[7][7] = -1;

}

void loop() {
 /* for (int y = 0; y < 16 ; y++)
  {
    for (int x = 0; x < 16 ; x++)
    {
      //      setText(x, y, String(grid_layout[x][y]));
       if (grid_known_cell[x][y] == 0)
        {}
        else if (grid_known_cell[x][y] == 1)
        {setColor(x, y, 'G');}
      if (grid_known_cell[x][y] == -1)
      {
        //        setColor(x, y, 'A');
//        log("value");
      }
    }
  }*/
  log("Running...");
  setColor(0, 0, 'G');
  setText(0, 0, "abc");
  while (true) {
    //    update_mms();
    if (!wallLeft()) {
      turnLeft();
    }
    while (wallFront()) {
      turnRight();
    }
    moveForward();
  }
  //    moveForward();
  //    first_Search();
}
