#include <mbed.h>

SPI spi(PF_9, PF_8, PF_7); // mosi, miso, sclk
DigitalOut cs(PC_1);
 
int main() {
  
    // Chip must be deselected
    cs = 1;
 
    // Setup the spi for 8 bit data, high steady state clock,
    // second edge capture, with a 1MHz clock rate
    spi.format(8,3);
    spi.frequency(1000000);
 
    cs = 0;

    // Set normal mode
    spi.write(0x20);

    int CTRL_REG1 = spi.write(0x0F);
    printf("CTRL_REG1 = %X\n", CTRL_REG1);

    cs = 1;

    while (1) {

      cs = 0;

      // Read X, Y, Z axis angular rate
      spi.write(0xE8);
  
      int OUT_X_L = spi.write(0x00);
      int OUT_X_H = spi.write(0x00);
      int OUT_Y_L = spi.write(0x00);
      int OUT_Y_H = spi.write(0x00);
      int OUT_Z_L = spi.write(0x00);
      int OUT_Z_H = spi.write(0x00);
      int X_angular_rate = (OUT_X_H << 8) + OUT_X_L;
      int Y_angular_rate = (OUT_Y_H << 8) + OUT_Y_L;
      int Z_angular_rate = (OUT_Z_H << 8) + OUT_Z_L;
      printf("OUT_X_H = %d\n", OUT_X_H);
      printf("OUT_X_L = %d\n", OUT_X_L);
      printf("X-axis angular rate = %d\n", X_angular_rate);
      printf("Y-axis angular rate = %d\n", Y_angular_rate);
      printf("Z-axis angular rate = %d\n", Z_angular_rate);

      cs = 1;

      wait_us(500000);

    }
    
}