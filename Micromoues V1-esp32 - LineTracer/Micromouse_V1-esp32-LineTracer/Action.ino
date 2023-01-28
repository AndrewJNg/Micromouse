void choose_action(char action_, int speed_junction_, float kp_, float ki_, float kd_) {
  switch (action_) {
    case 'I':  //ignore

      // Serial.print("I ");
      do {
        PID(speed_junction_, kp_, ki_, kd_);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      break;


    case 'L':  //left
      // Serial.print("L ");
      do {
        motor(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));

      do {
        motor(-100, 100);
      } while (get_state[0] == 0);
      do {
        motor(-100, 100);
      } while ((get_state[0] == 1) || (get_state[1] == 0));
      break;


      // case 'l':  //left
      //   do {
      //     motor(100, 100);
      //   } while ((get_state[0] == 1) || (get_state[4] == 1));


      //   do {
      //     motor(0, 255);
      //   } while (get_state[0] == 0);
      //   do {
      //     motor(0, 255);
      //   } while ((get_state[0] == 1) || (get_state[1] == 0));

      //   break;

      // case 'T':  //left
      //   do {
      //     motor(100, 100);
      //   } while ((get_state[0] == 1) || (get_state[4] == 1));
      //   do {
      //     motor(-80, 80);
      //   } while (get_state[0] == 0);
      //   do {
      //     motor(-80, 80);
      //   } while ((get_state[0] == 1) || (get_state[1] == 0));

      //   break;


      // case 'r':  //right
      //   do {
      //     motor(100, 100);
      //   } while ((get_state[0] == 1) || (get_state[4] == 1));


      //   do {
      //     motor(255, 0);
      //   } while (get_state[4] == 0);
      //   do {
      //     motor(255, 0);
      //   } while ((get_state[3] == 0) || (get_state[4] == 1));
      //   break;

    case 'R':  //right
      do {
        motor(100, 100);
      } while ((get_state[0] == 1) || (get_state[4] == 1));
      do {
        motor(100, -100);
      } while (get_state[4] == 0);
      do {
        motor(100, -100);
      } while ((get_state[3] == 0) || (get_state[4] == 1));

      // Serial.print("R ");
      break;


    case 's':  //stop
      // Serial.print("S ");
      motor(0, 0);
      Start = false;
      break;

    case 'c':  //change line
      whiteLine = !whiteLine;
      break;

    default:
      break;
  }
}