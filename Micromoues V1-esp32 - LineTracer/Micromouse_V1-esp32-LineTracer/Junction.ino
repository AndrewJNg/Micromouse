
void Junction(int speed_junction, float kp, float ki, float kd, char type, char action) {

  switch (type) {

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 'L':
      do {
        PID(speed_junction, kp, ki, kd);
      } while (get_state[0] == 0);  // left junction 111xx
      choose_action(action, speed_junction, kp, ki, kd);
      break;

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 'M':
      do {
        PID(speed_junction, kp, ki, kd);
      } while (get_state[0] == 0 || get_state[4] == 0);  // middle junction 1xxx1
      choose_action(action, speed_junction, kp, ki, kd);
      break;

      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    case 'R':
      do {
        PID(speed_junction, kp, ki, kd);
      } while (get_state[4] == 0);  // right junction xx111
      choose_action(action, speed_junction, kp, ki, kd);
      break;

    default:
      break;
  }
}
