//#include <SharpIR.h>
#include <Wire.h>
//#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define jumlah_servo 18
//#include <SharpIR.h>

#define ir A0
#define model 1080

//SharpIR SharpIR(ir, model);
//LiquidCrystal_I2C lcd(0x27, 16, 2);

int servoPins[] = {43, 44, 45, 42, 41, 40, 4, 3, 2, 53, 52, 51, 7, 6, 5, 50, 49, 22 };
int ss[]={138 ,40, 36, 89, 156, 58, 155, 78, 62, 140, 123, 62, 160, 25, 62, 164, 153, 53};

Servo servos[jumlah_servo];  
int sp = 10;
float kp = 1.18;
float ki = 0.67;
float kd = 0.15;
float Out,p,i,d,pid;
float error,errorx,sumerr;
const int ping_depan = 5;
const int ping_pjkanan =8;
const int ping_kanan = 9;
const int ping_pjkiri=10;
const int ping_kiri = 11; 
const int ping_kiriatas=14;
const int ping_kananatas=15;
const int ping_knn = 31;
const int ping_kri = 37;
int dka=34;
int dki=35;
int bka=33;
int bki=32;
int flame0=12;
int flame1=36;
int flame2=11;
int flame3a=10;
int flame3b=8;
int flame5=23;
int flame6=46;
int flame7=17;
int sound=30;
int button=29;
int led=28;
int en1=26;
int en2=27;
int perempatan=0;
int kondisi=0;
int hasil;
int r1=0,r2=0,r3=0,r4=0,ctr=0;
int logic_program=0,padam=0;
int sts=0,btn=0,snd=0,fire0=0,fire1=0,fire2=0,fire3a=0,fire3b=0,fire5=0,fire6=0,fire7=0,garis1=0,garis2=0,garis3=0,garis4=0,sh=0;
long duration_depan, duration_kanan, duration_kiri, duration_pjkanan, duration_pjkiri, duration_kiriatas, duration_kananatas, duration_knn, duration_kri, usdepan,uskanan,uskiri, uspojok_kanan, uspojok_kiri,uskiriatas,uskananatas,usknn,uskri;

long microsecondsToCentimeters(long microseconds)
{
  return floor(microseconds/29/2);
}

void initServos() 
{
  int i;
  for (i=0;i<jumlah_servo;i++) 
  {
    servos[i].attach(servoPins[i]); // servo setup
    servos[i].write(ss[i]);
  }
}

void us_kanan()
{
  pinMode(ping_kanan,OUTPUT);
  digitalWrite(ping_kanan,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_kanan,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_kanan,LOW);
  pinMode(ping_kanan,INPUT);
  duration_kanan=pulseIn(ping_kanan,HIGH);
  uskanan=microsecondsToCentimeters(duration_kanan);
  error=sp-uskanan;
  p=error*kp;
  sumerr=error+errorx; 
  i=ki*sumerr; 
  d=error-errorx;
  errorx=error;
  Out=p+i+d;
  pid=max(-5,min(Out,5));
}

void us_pjkanan()
{
  pinMode(ping_pjkanan,OUTPUT);
  digitalWrite(ping_pjkanan,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_pjkanan,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_pjkanan,LOW);
  pinMode(ping_pjkanan,INPUT);
  duration_pjkanan=pulseIn(ping_pjkanan,HIGH);
  uspojok_kanan=microsecondsToCentimeters(duration_pjkanan);
}

void us_depan()
{
  pinMode(ping_depan,OUTPUT);
  digitalWrite(ping_depan,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_depan,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_depan,LOW);
  pinMode(ping_depan,INPUT);
  duration_depan=pulseIn(ping_depan,HIGH);
  usdepan=microsecondsToCentimeters(duration_depan); 
}

void us_pjkiri()
{
  pinMode(ping_pjkiri,OUTPUT);
  digitalWrite(ping_pjkiri,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_pjkiri,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_pjkiri,LOW);
  pinMode(ping_pjkiri,INPUT);
  duration_pjkiri=pulseIn(ping_pjkiri,HIGH);
  uspojok_kiri=microsecondsToCentimeters(duration_pjkiri);
}

void us_kiri()
{
  pinMode(ping_kiri,OUTPUT);
  digitalWrite(ping_kiri,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_kiri,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_kiri,LOW);
  pinMode(ping_kiri,INPUT);
  duration_kiri=pulseIn(ping_kiri,HIGH);
  uskiri=microsecondsToCentimeters(duration_kiri);
  error=sp-uskiri;
  p=error*kp;
  sumerr=error+errorx; 
  i=ki*sumerr; 
  d=error-errorx;
  errorx=error;
  Out=p+i+d;
  pid=max(-5,min(Out,5));
}

void uskiri_atas()
{
  pinMode(ping_kiriatas,OUTPUT);
  digitalWrite(ping_kiriatas,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_kiriatas,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_kiriatas,LOW);
  pinMode(ping_kiriatas,INPUT);
  duration_kiriatas=pulseIn(ping_kiriatas,HIGH);
  uskiriatas=microsecondsToCentimeters(duration_kiriatas);
}

void uskanan_atas()
{
  pinMode(ping_kananatas,OUTPUT);
  digitalWrite(ping_kananatas,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_kananatas,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_kananatas,LOW);
  pinMode(ping_kananatas,INPUT);
  duration_kananatas=pulseIn(ping_kananatas,HIGH);
  uskananatas=microsecondsToCentimeters(duration_kananatas);
}

void us_knn()
{
  pinMode(ping_knn,OUTPUT);
  digitalWrite(ping_knn,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_knn,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_knn,LOW);
  pinMode(ping_knn,INPUT);
  duration_knn=pulseIn(ping_knn,HIGH);
  usknn=microsecondsToCentimeters(duration_knn);
}

void us_kri()
{
  pinMode(ping_kri,OUTPUT);
  digitalWrite(ping_kri,LOW);
  delayMicroseconds(2);
  digitalWrite(ping_kri,HIGH);
  delayMicroseconds(10);
  digitalWrite(ping_kri,LOW);
  pinMode(ping_kri,INPUT);
  duration_kri=pulseIn(ping_kri,HIGH);
  uskri=microsecondsToCentimeters(duration_kri);
}

void scand()
{
  us_kanan();
  us_depan();
  us_kiri();
  us_pjkanan();
  us_pjkiri();
  uskiri_atas();
  uskanan_atas();
  us_knn();
  us_kri();
}

void maju_biasa()
{
  setservo(ss[0], ss[1], ss[2]+10 , ss[3]+10, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]-10, ss[9]-10, ss[10], ss[11], ss[12], ss[13], ss[14]+10, ss[15]+10, ss[16]-11, ss[17]+9);
  delay(200);
  setservo(ss[0]-8, ss[1]+9, ss[2]-10, ss[3]-10, ss[4], ss[5], ss[6], ss[7], ss[8]+10, ss[9]+10, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]-10, ss[15]-10, ss[16], ss[17]);
  delay(200);
}

void maju()
{
  us_kanan();
  if(uskanan>10)
  {
    //Data minus
    setservo(ss[0], ss[1], ((ss[2]+5)-(pid)) , ss[3]+3, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ((ss[8]-5)+(pid)), ((ss[9]-3)+(pid)), ss[10], ss[11], ss[12], ss[13], ((ss[14]+5)-(pid)), ss[15]+3, ss[16]-11, ss[17]+9);
    delay(200);
    setservo(ss[0]-8, ss[1]+9, ((ss[2]-5)+(pid)), ((ss[3]-3)+(pid)), ss[4], ss[5], ss[6], ss[7], ((ss[8]+5)-(pid)), ss[9]+3, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ((ss[14]-5)+(pid)), ((ss[15]-3)+(pid)), ss[16], ss[17]);
    delay(200);
  }
  else if(uskanan<10)
  {
    //Data positif
    setservo(ss[0], ss[1], ss[2]+3+pid , ss[3]+3+pid, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]-3, ss[9]-3-pid, ss[10], ss[11], ss[12], ss[13], ss[14]+3+pid, ss[15]+3+pid, ss[16]-11, ss[17]+9);
    delay(200);
    setservo(ss[0]-8, ss[1]+9, ss[2]-3, ss[3]-3-pid, ss[4], ss[5], ss[6], ss[7], ss[8]+3+pid, ss[9]+3+pid, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]-3, ss[15]-3-pid, ss[16], ss[17]);
    delay(200);
  }
  else
  {
    //Data normal
    setservo(ss[0], ss[1], ss[2]+10 , ss[3]+10, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]-10, ss[9]-10, ss[10], ss[11], ss[12], ss[13], ss[14]+10, ss[15]+10, ss[16]-11, ss[17]+9);
    delay(200);
    setservo(ss[0]-8, ss[1]+9, ss[2]-10, ss[3]-10, ss[4], ss[5], ss[6], ss[7], ss[8]+10, ss[9]+10, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]-10, ss[15]-10, ss[16], ss[17]);
    delay(200);
  }
}

void maju2()
{
  us_kiri();
  if(uskiri>10)
  { 
    //Data minus
    setservo(ss[0], ss[1], ((ss[2]+3)-(pid)) , ((ss[3]+5)-(pid)), ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]-3, ((ss[9]-5)+(pid)), ss[10], ss[11], ss[12], ss[13], ((ss[14]+3)-(pid)), ((ss[15]+5)+(pid)), ss[16]-11, ss[17]+9);
    delay(225);
    setservo(ss[0]-8, ss[1]+9, ss[2]-3, ((ss[3]-5)+(pid)), ss[4], ss[5], ss[6], ss[7], ((ss[8]+3)-(pid)), ((ss[9]+5)-(pid)), ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]-3, ((ss[15]-5)+(pid)), ss[16], ss[17]);
    delay(225);
  }
  else if(uskiri<10)
  { 
    // Data positif
    setservo(ss[0], ss[1], ss[2]+7+pid , ss[3]+3, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]-7-pid, ss[9]-3-pid, ss[10], ss[11], ss[12], ss[13], ss[14]+7+pid, ss[15]+3, ss[16]-11, ss[17]+9);
    delay(225);
    setservo(ss[0]-8, ss[1]+9, ss[2]-7-pid, ss[3]-3-pid, ss[4], ss[5], ss[6], ss[7], ss[8]+7+pid, ss[9]+3, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]-7-pid, ss[15]-3-pid, ss[16], ss[17]);
    delay(225);
  }
  else
  { 
    // Data normal
    setservo(ss[0], ss[1], ss[2]+10 , ss[3]+10, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]-10, ss[9]-10, ss[10], ss[11], ss[12], ss[13], ss[14]+10, ss[15]+10, ss[16]-11, ss[17]+9);
    delay(225);
    setservo(ss[0]-8, ss[1]+9, ss[2]-10, ss[3]-10, ss[4], ss[5], ss[6], ss[7], ss[8]+10, ss[9]+10, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]-10, ss[15]-10, ss[16], ss[17]);
    delay(225);
  }
}

void mundur()
{
  setservo(ss[0], ss[1], ss[2]-10 , ss[3]-10, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]+10, ss[9]+10, ss[10], ss[11], ss[12], ss[13], ss[14]-10, ss[15]-10, ss[16]-11, ss[17]+9);
  delay(200);
  setservo(ss[0]-8, ss[1]+9, ss[2]+10, ss[3]+10, ss[4], ss[5], ss[6], ss[7], ss[8]-10, ss[9]-10, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]+10, ss[15]+10, ss[16], ss[17]);
  delay(200);
}

void goyang()
{
  setservo(ss[0], ss[1], ss[2]+5, ss[3]+5, ss[4], ss[5], ss[6], ss[7], ss[8]+5, ss[9]+5, ss[10], ss[11], ss[12], ss[13], ss[14]+5, ss[15]+5, ss[16], ss[17]);
  delay(200);
  setservo(ss[0], ss[1], ss[2]-5, ss[3]-5, ss[4], ss[5], ss[6], ss[7], ss[8]-5, ss[9]-5, ss[10], ss[11], ss[12], ss[13], ss[14]-5, ss[15]-5, ss[16], ss[17]);
  delay(200);
}

void putarkanan()
{
  setservo(ss[0], ss[1], ss[2] , ss[3]-15, ss[4]-13, ss[5], ss[6], ss[7]+5, ss[8]-15, ss[9], ss[10], ss[11], ss[12], ss[13], ss[14], ss[15]-15, ss[16]-11, ss[17]);
  delay(200);
  setservo(ss[0], ss[1]+9, ss[2]-15, ss[3], ss[4], ss[5], ss[6], ss[7], ss[8], ss[9]-15, ss[10]-10, ss[11], ss[12], ss[13]+5, ss[14]-15, ss[15], ss[16], ss[17]);
  delay(200);
}

void putarkiri()
{
  setservo(ss[0], ss[1], ss[2] , ss[3]+15, ss[4]-15, ss[5], ss[6], ss[7]+8, ss[8]+15, ss[9], ss[10], ss[11], ss[12], ss[13], ss[14], ss[15]+15, ss[16]-11, ss[17]);
  delay(200);
  setservo(ss[0], ss[1]+7, ss[2]-15, ss[3], ss[4], ss[5], ss[6], ss[7], ss[8], ss[9]+15, ss[10]-10, ss[11], ss[12], ss[13]+8, ss[14]+15, ss[15], ss[16], ss[17]);
  delay(200);
}

void belokkanan()
{
  setservo(ss[0], ss[1], ss[2]+15 , ss[3]+3, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]-15, ss[9]-3, ss[10], ss[11], ss[12], ss[13], ss[14]+15, ss[15]+3, ss[16]-11, ss[17]+9);
  delay(200);
  setservo(ss[0]-8, ss[1]+9, ss[2]-15, ss[3]-3, ss[4], ss[5], ss[6], ss[7], ss[8]+15, ss[9]+3, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]-15, ss[15]-3, ss[16], ss[17]);
  delay(200);
}

void belokkiri()
{
  setservo(ss[0], ss[1], ss[2] , ss[3]+15, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8], ss[9]-15, ss[10], ss[11], ss[12], ss[13], ss[14], ss[15]+15, ss[16]-11, ss[17]+9);
  delay(200);
  setservo(ss[0]-8, ss[1]+9, ss[2], ss[3]-15, ss[4], ss[5], ss[6], ss[7], ss[8], ss[9]+15, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14], ss[15]-15, ss[16], ss[17]);
  delay(200);
}

void putarkananapi()
{
  setservo(ss[0], ss[1], ss[2] , ss[3]-15, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]-15, ss[9], ss[10], ss[11], ss[12], ss[13], ss[14], ss[15]-15, ss[16]-11, ss[17]+9);
  delay(350);
  setservo(ss[0]-8, ss[1]+9, ss[2]-15, ss[3], ss[4], ss[5], ss[6], ss[7], ss[8], ss[9]-15, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]-15, ss[15], ss[16], ss[17]);
  delay(350);
}

void putarkiriapi()
{
  setservo(ss[0], ss[1], ss[2] , ss[3]+15, ss[4]-13, ss[5]+10, ss[6]-4, ss[7]+5, ss[8]+15, ss[9], ss[10], ss[11], ss[12], ss[13], ss[14], ss[15]+15, ss[16]-11, ss[17]+9);
  delay(350);
  setservo(ss[0]-8, ss[1]+9, ss[2]-15, ss[3], ss[4], ss[5], ss[6], ss[7], ss[8], ss[9]+15, ss[10]-10, ss[11]+11, ss[12]-4, ss[13]+5, ss[14]+15, ss[15], ss[16], ss[17]);
  delay(350);
}

//#########################################################  S C A N D  K A N A N #######################################################################
void scand_kanan()
{
  scand();
  if(usdepan<=7)
  {
    for(int i=0; i<=20; i++)
    {
      putarkanan();
    }
  }
  if(usdepan>=18 && uskiri>=18 && uskanan>=5 && uskanan<=18 && uskananatas>=18 && uskiriatas>=18)
  {
    maju();
  }
  if(usdepan>=18 && uskiri>5 && uskanan>=5)
  {
    maju();
  }
  if(usknn<=8 && uspojok_kanan<=8 && usdepan<18 && uskri<=13 && uspojok_kiri<=13)
  {
    for(int i=0; i<=7; i++)
    {
      putarkiri(); // PATOKAN START
    }
  }
  if(usdepan>=18 && uskiri<5 && uskanan>=3 && uskanan<=18)
  {
    maju();
  }
  if(usdepan>18 && uskanan>=3 && uskanan<=18)
  {
    maju();
  }

  // KELUAR DARI POJOKAN
  if(usdepan<=18 && uspojok_kanan<=9 && uskanan>=7 && uspojok_kiri>=8)
  {
    putarkiri(); // PATOKAN START
  }
  if(usdepan>=18 && uspojok_kanan<=11 && uskanan>=10 && uspojok_kiri>=8)
  {
    putarkiri();
  }
  if(usdepan>=18 && uspojok_kanan<=11 && uskanan>=10 && uspojok_kiri>=8 && uskiri<=12)
  {
    putarkiri();
  }
 
 // PUTAR KIRI DI TIKUNGAN
  if(usdepan<=17 && uskananatas>=17 && uskananatas<=23 && uskiriatas>=18 && uskiri>=18 && uskanan<=20)
  {
    for(int i=0;i<=3;i++)
    {
      putarkiri();
    }
  }
  if(usdepan<=17 && uskananatas<=23 && uskiriatas>=18 && uskiri>=18 && uskanan>=5 && uskanan<=18)
  {
    for(int i=0;i<=3;i++)
    {
      putarkiri();
    }
  }
  if(uskananatas>=8 && uskananatas<=20)
  {
    for(int i=0;i<=2;i++)
    {
      putarkiri();
    }
  }
  if(uspojok_kanan>=8 && uspojok_kanan<=20)
  {
    for(int i=0;i<=3;i++)
    {
      putarkiri();
    }
  }

  //BELOK KANAN DI PEREMPATAN
  if(usdepan>=18 && uskanan>=18 && uskananatas>=18 && uskiriatas>=18 && uskiri>=15 && uskiri<=20)
  {
    belokkanan();
  }
  if(usdepan>=18 && uskanan>=18 && uskananatas>=18 && uskiriatas>=18 && uskiri>=18)
  {
    belokkanan();
  }
  if(usdepan>=18 && uskanan>=18 && uskananatas>=18 && uskiriatas>=18 && uskiri>8 && uskiri<15)
  {
    belokkanan();
  }

  //BELOK KANAN DI PERTIGAAN
  if(usdepan<25 && uskananatas>=20 && uspojok_kanan>=20 && uskanan>=20 && uskiriatas>=20 && uskiriatas<=25 && uspojok_kiri<20)
  {
    belokkanan();
  }
  if(usdepan<25 && usdepan>=20 && uskananatas>=20 && uspojok_kanan>=20 && uskanan>=20 && uskiriatas>=20 && uskiriatas<=25 && uspojok_kiri<20 && uskiri>=20)
  {
    belokkanan();
  }
  if(usdepan<25 && usdepan>=20 && uskananatas>=20 && uspojok_kanan>=20 && uskanan>=20 && uskiriatas>=15 && uskiriatas<=20 && uspojok_kiri>=15 && uskiri>=20)
  {
    belokkanan();
  }

  //TAMBAHAN
  if(usdepan>=18 && uspojok_kiri>=10 && uspojok_kiri<=15)
  {
    putarkanan();
  }
  if(usdepan>=18 && uskri>=3 && uskri<=6 && uskiri>=5)
  {
    putarkanan();
  }
}

//#########################################################  S C A N D  K I R I #######################################################################
void scand_kiri()
{
  scand();
  if((usdepan>=18 && uskiri>=5 && uskanan>=3)&&((uskananatas>=5 && uskiriatas>=5)||(uspojok_kiri>=18 && uspojok_kanan>=18)))
  {
    maju2();
  }

  //NEW PUTAR KANAN
  int pk=0;
  pk=(usdepan<=7)?21:pk;
  pk=(usknn<=8 && uspojok_kanan<=8 && usdepan<18 && uskri<=13 && uspojok_kiri<=13)?8:pk;
  pk=(usdepan<18 && uskiri<=25)?7:pk;
  pk=(uspojok_kiri>=8 && uspojok_kiri<=15)?4:pk;
  pk=(uskiriatas>=8 && uskiriatas<=15)?2:pk;
  pk=(uskri>=8 && uskri<=10)?1:pk;
  for(int i=0;i<pk;i++)
  {
    putarkanan();
  }
  
  //NEW PUTAR KIRI
  int pk2=((uskananatas>=8 && uskananatas<=15)||(uspojok_kanan>=8 && uspojok_kanan<=15)||(usknn>=10 && usknn<=15))?1:0;
  for(int i=0;i<pk2;i++)
  {
    putarkiri();
  }

  //NEW BELOK KIRI
  int bk=0;
  bk=(usdepan>=18 && uskiri>=18 && uskiriatas>=18 && uskananatas>=18 && uskanan>=15 && uskanan<=18)?1:0;
  bk=(usdepan>=18 && uskiri>=18 && uskiriatas>=18 && uskananatas>=18 && uskanan>=18)?1:bk;
  bk=(usdepan>=18 && uskiri>=18 && uskiriatas>=18 && uskananatas>=18 && uskanan>8 && uskanan<15)?1:bk;
  bk=(uskiri>=18 && uskri>=18 && uspojok_kiri>=18 && uskiriatas>=18 && usdepan>=18 && uskananatas>=18 && uspojok_kanan>=18 && usknn>=18 && uskanan>=18)?1:bk;
  bk=(usdepan<=30 && uskanan>=20 && uskiri>=20)?1:bk;
  bk=(usdepan>=20 && uskananatas<=20 && uspojok_kanan<=20 && uskiri>=20)?1:bk;
  bk=(usdepan<=30 && uskanan<=15 && uskiri>=20)?1:bk;
  for(int i=0;i<bk;i++)
  {
    belokkiri();
  }
  
  //NEW BELOK KANAN
  int bk2=(usdepan>=18 && uskiri<5)?1:0;
  for(int i=0;i<bk2;i++)
  {
    belokkanan();
  }
}


void api()
{
  for(int i=0;i<=7;i++)
  {
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
    delay(100);
  }
}
 
void setup()
{
  Serial.begin(9600);
//  lcd.begin();
//  lcd.backlight();
  initServos();
  pinMode(led,OUTPUT);
  pinMode(sound,INPUT);
  pinMode(button,INPUT);
  pinMode(dka,INPUT);
  pinMode(dki,INPUT);
  pinMode(bka,INPUT);
  pinMode(bki,INPUT);
  pinMode(en1,OUTPUT);
  pinMode(en2,OUTPUT);
  digitalWrite(en1,LOW);
  digitalWrite(en2,LOW);
}

void loop()
{
  btn=digitalRead(29);
  snd=digitalRead(30);
  garis1=digitalRead(dka);
  garis2=digitalRead(dki);
  garis3=digitalRead(bka);
  garis4=digitalRead(bki);
  fire0=digitalRead(flame0);
  fire1=digitalRead(flame1);
  fire2=digitalRead(flame2);
  fire3a=digitalRead(flame3a);
  fire3b=digitalRead(flame3b);
  fire5=digitalRead(flame5);
  fire6=digitalRead(flame6);
  fire7=digitalRead(flame7);
//  int r1=0,r2=0,r3=0,r4=0,ctr=0,garis=0;

  if(snd==1 || btn==1){
    sts=1;
  }
  if(sts==1)
  {
    if(digitalRead(dka)==LOW)
    {
      Serial.print(garis1++);
      for(int i=0;i<=3;i++)
      {
        maju_biasa();
      }
      hasil=garis1;
      lcd.setCursor(0,0);
      lcd.print(hasil);
      Serial.print(hasil);
      while(digitalRead(dka)==LOW);
    }
    else if((fire0==LOW||fire1==LOW)&&(fire2==HIGH&&fire3a==HIGH&&fire3b==HIGH&&fire5==HIGH&&fire6==HIGH&&fire7==HIGH))
    {
      api();
      for(int i=0;i<=3;i++)
      {
        putarkananapi();
      }
    }
    else if((fire0==HIGH&&fire1==HIGH&&fire2==HIGH&&fire3a==HIGH&&fire3b==HIGH&&fire5==HIGH)&&(fire6==LOW||fire7==LOW))
    {
      api();
      for(int i=0;i<=3;i++)
      {
        putarkiriapi();
      }
    }
    else if((fire2==LOW||fire3a==LOW||fire3b==LOW||fire5==LOW)&&(fire0==HIGH&&fire1==HIGH&&fire6==HIGH&&fire7==HIGH))
    {     
      api();
      digitalWrite(led,HIGH);
      initServos();
      delay(1000);
      goyang();
      digitalWrite(en1,HIGH);
      digitalWrite(en2,LOW);
      delay(2000);
      logic_program=1;
    }
    else
    {
      digitalWrite(en1,LOW);
      digitalWrite(en2,LOW);
      digitalWrite(led,LOW);
      if(logic_program==0)
      {                                 
        scand_kiri();
      }
      if(logic_program==1)
      {
        scand_kanan();
      }
    }

    hasil=max(0,min(hasil,8));

    int tmp_LP[]={1,0,0,0,0,0,0,0,0};
    int tmp_R1[]={0,1,0,0,0,0,0,0,0};
    int tmp_R2[]={0,0,1,0,0,0,0,0,0};
    int tmp_R3[]={0,0,0,0,1,0,0,0,0};
    int tmp_R4[]={0,0,0,0,0,0,1,0,0};

    logic_program=tmp_LP[hasil];
    r1=tmp_R1[hasil];
    r2=tmp_R2[hasil];
    r3=tmp_R3[hasil];
    r4=tmp_R4[hasil];
  }
  else
  {
    initServos();
  }
}*/

void setservo(int deg1, int deg2, int deg3, int deg4, int deg5, int deg6, int deg7, int deg8, int deg9, int deg10, int deg11, int deg12,int deg13,int deg14,int deg15,int deg16, int deg17, int deg18)
{
  int i;
  int deg[]={deg1,deg2,deg3,deg4,deg5,deg6,deg7,deg8,deg9,deg10,deg11,deg12,deg13,deg14,deg15,deg16,deg17,deg18};
  for (i=0;i<18;i++)
  {
    servos[i].write(deg[i]);
  }
}
