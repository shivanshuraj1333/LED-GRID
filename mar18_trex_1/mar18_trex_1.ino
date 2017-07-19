#include <Adafruit_GFX.h>
#include <gfxfont.h>

#include <gamma.h>
#include <RGBmatrixPanel.h>


#define CLK 8
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);
int base =0;
int object=31;
int times=4;
int height = 6;
int jump=0;
int ancor = 3;
int game_over = 0;
int pushButton = 10;
int t1=100;
int randNumber=20;
boolean object_base[32];


void draw_object(){
  if(digitalRead(pushButton)){
      jump = digitalRead(pushButton);
    }
//shift objects to the left
  object_base[32]=LOW;
  for(int i=0;i<32;i++)
  {
   object_base[i]=object_base[i+1]; 
  } 
//If that base is high draw the object
  for(int i=0;i<32;i++)
  {
   if(object_base[i]==HIGH)
   {
     matrix.fillRect(i, 14, 2, 1, matrix.Color333(7, 0, 0));
     test_game_over(i);
   }
  }
  delay(t1);

  for(int i=0;i<32;i++)
  {
   matrix.fillRect(i, 14, 2, 1, matrix.Color333(0, 0, 0));
  }
  
  
  if(times==-4){
    times=4;
    jump=0;
  }
//  test_game_over();
  if(game_over==1){
      return;
    }
//  if(object>0){
//    draw_object();
//    }
//   else {
//    object=31;
//    draw_object();
//   }
   randNumber--;
   if(randNumber==0)
   {
       randNumber = random(5, 20);
       object_base[31]=HIGH;
   }
    draw_object();
}
void del_object(){
    matrix.fillRect(object, 14, 2, 1, matrix.Color333(0, 0, 0));
  }


void jump_rex() {
  if(jump==1){
      if(times>0){
          delete_rex();
          base++;
          draw_rex();
          times--;
          delay(100);
          draw_object();
        }
        else if(times>=-3){
            delete_rex();
            base--;
            draw_rex();
            times--;
            delay(100);
            draw_object();
          }
      
    }
}

void test_game_over(int j){
  
  if((ancor+1==j || ancor == j || ancor == j+1) && base<=1){
    //display game over
    game_over=1;
   return ;
  }
  if(jump==1){
    jump_rex();
  }
}

void setup() {
  // put your setup code here, to run once:
     for(int i=0;i<32;i++)
    {
     
     object_base[i]=LOW;
    } 
    object_base[31]=HIGH;
    matrix.begin();
    draw_rex();
    draw_object();
    pinMode(pushButton, INPUT);
    Serial.begin(9600);
    
}
void display_game_over() {
  matrix.fillRect(0, 0, 32, 16, matrix.Color333(0, 0, 2));
  matrix.setCursor(5, 0); 
  matrix.setTextSize(1);
  
  matrix.setTextColor(matrix.Color333(7,0,0));
  matrix.print('G');
  matrix.print('A');
  matrix.print('M');
  matrix.print('E');
  matrix.setCursor(5, 9);
  matrix.print('O');
  matrix.print('V');
  matrix.print('E');
  matrix.print('R');
  delay(60000);
}

void loop() {
//   put your main code here, to run repeatedly:
    display_game_over();
    
}
void draw_rex() {
 
  matrix.fillRect(ancor, 16-height-base, ancor-1, height, matrix.Color333(0, 7, 0));
  
}
void delete_rex() {
  
   matrix.fillRect(ancor, 16-height-base, ancor-1, height, matrix.Color333(0, 0, 0));
}
