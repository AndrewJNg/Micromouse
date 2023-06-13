#include <Preferences.h>
Preferences preferences;

void read_memory() {
  preferences.begin("IR_Data", false);

  // retrieve saved data
  minIR[0] = preferences.getUInt("min0", 0);
  maxIR[0] = preferences.getUInt("max0", 0);
  minIR[1] = preferences.getUInt("min1", 0);
  maxIR[1] = preferences.getUInt("max1", 0);
  minIR[2] = preferences.getUInt("min2", 0);
  maxIR[2] = preferences.getUInt("max2", 0);

  minIR[3] = preferences.getUInt("min3", 0);
  maxIR[3] = preferences.getUInt("max3", 0);
  minIR[4] = preferences.getUInt("min4", 0);
  maxIR[4] = preferences.getUInt("max4", 0);
  minIR[5] = preferences.getUInt("min5", 0);
  maxIR[5] = preferences.getUInt("max5", 0);

  preferences.end();
}

void store_memory_IR() {
  preferences.begin("IR_Data", false);

  preferences.putUInt("min0", minIR[0]);
  preferences.putUInt("max0", maxIR[0]);

  delay(100);
  preferences.putUInt("min1", minIR[1]);
  preferences.putUInt("max1", maxIR[1]);

  delay(100);
  preferences.putUInt("min2", minIR[2]);
  preferences.putUInt("max2", maxIR[2]);

  delay(100);
  preferences.putUInt("min3", minIR[3]);
  preferences.putUInt("max3", maxIR[3]);

  delay(100);
  preferences.putUInt("min4", minIR[4]);
  preferences.putUInt("max4", maxIR[4]);

  delay(100);
  preferences.putUInt("min5", minIR[5]);
  preferences.putUInt("max5", maxIR[5]);

  delay(100);
  preferences.end();
}
