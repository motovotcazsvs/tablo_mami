#include <Max7219_matrix.h>
#include <iarduino_RTC.h>

Max7219_matrix disp(11, 13, 10, 16); //data, clk, cs
iarduino_RTC time(RTC_DS1307); //scl-a5, sda-a4

void setup() {
  time.begin();
}
unsigned char* stroka[7] = {"неділя", "понеділок", "вівторок", "середа", "четвер", "пятниця", "субота"};
int ot;
int temp = -1;
void loop() {
  disp.print(15, 0, 0, time.gettime("h"));
  disp.print(14, 6, 0, time.gettime("i"));
  disp.print(11, 0, 0, time.gettime("d"));
  disp.print(9, 0, 0, time.gettime("m"));
  
  
  for(int i = 0; i < 7; i++)
  {
    time.gettime();
    if(time.weekday == i)
    {
      if (time.weekday == 1)
        ot = 6;
      else
        ot = 5;
      if (time.weekday != temp)
      {
        for (int x = 0; x < 8; x++)
          disp.clearDriver(x);
        temp = time.weekday;
      }
      disp.print(ot, 0, 3, stroka[i]);
    }
  }
  disp.setLED(14, 1, 4, 1);
  disp.setLED(14, 3, 4, 1);
  delay(500);
  disp.setLED(14, 1, 4, 0);
  disp.setLED(14, 3, 4, 0);
  disp.setLED(10, 4, 5, 1);
}

