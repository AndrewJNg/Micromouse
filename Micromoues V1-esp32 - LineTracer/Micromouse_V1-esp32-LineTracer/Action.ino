void choose_action(char action_, int speed_junction_, float kp_, float ki_, float kd_) {
  switch (action_) {
    case 'i':  //ignore
      do {
        PID(speed_junction_, kp_, ki_, kd_);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      break;


    case 'L':  //left
      // leftTurn = 1;
      // rightTurn = 0;
      do {
        motor(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));


      do {
        motor(-100, 100);
      } while (get_state[0] == 0);
      do {
        motor(-100, 100);
      } while ((get_state[0] == 1) || (get_state[1] == 0));

      // leftTurn = 0;
      break;


    case 'l':  //left
      // leftTurn = 1;
      // rightTurn = 0;
      do {
        motor(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));


      do {
        motor(0, 255);
      } while (get_state[0] == 0);
      do {
        motor(0, 255);
      } while ((get_state[0] == 1) || (get_state[1] == 0));

      // leftTurn = 0;
      break;

    case 'T':  //left
      do {
        motor(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      do {
        motor(-80, 80);
      } while (get_state[0] == 0);
      do {
        motor(-80, 80);
      } while ((get_state[0] == 1) || (get_state[1] == 0));

      // leftTurn = 0;
      break;


    case 'r':  //right
      // rightTurn = 1;
      // leftTurn = 0;
      do {
        motor(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));


      do {
        motor(255, 0);
      } while (get_state[4] == 0);
      do {
        motor(255, 0);
      } while ((get_state[3] == 0) || (get_state[4] == 1));
      // rightTurn = 0;
      break;

    case 'R':  //right
      // rightTurn = 1;
      // leftTurn = 0;
      do {
        motor(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      do {
        motor(100, 100);
      } while (get_state[4] == 0);
      do {
        motor(100, 100);
      } while ((get_state[3] == 0) || (get_state[4] == 1));
      // rightTurn = 0;
      break;


    case 's':  //stop
      motor(0, 0);
      Start = false;
      break;


    case 'u':
      break;

    case 'A':
      break;

    case 'B':
      break;

    case 'c':  //change line
      whiteLine = !whiteLine;


      break;


    default:
      break;
  }
}