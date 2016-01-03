#include <SoftwareSerial.h>

#include <TinyGPS.h>
 
float lat,lon; // create variable for latitude and longitude object
float flat,flon;
SoftwareSerial gpsSerial(2, 3); // create gps sensor connection
SoftwareSerial gsm(8, 9);
TinyGPS gps; // create gps object
String msg="";

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 gsm.begin(9600);
 gpsSerial.begin(9600);
}

void loop() {
   while(gpsSerial.available()){ // check for gps data
   if(gps.encode(gpsSerial.read())){ // encode gps data
    gps.f_get_position(&lat,&lon); // get latitude and longitude
    // display position
    flat=lat;
    flon=lon;
    Serial.print("Position: ");
    Serial.print("lat: ");Serial.print(lat,6);Serial.print(" ");// print latitude
    Serial.print("lon: ");Serial.println(lon,6); // print longitude
    //Serial.print("akash");
 //   Serial.println(flon,6);
  msg="Latitude : "+(String)flat+" \nLongitude : "+(String)flon;  
 Serial.println(msg);
 gsmtest(msg); 

 }
  }
}

void gsmtest(String msg)
{
  Serial.println("set up comms");
 delay(5000);

 Serial.println("Switching to text mode");
 gsm.println("AT+CMGF=1");
 delay(1000);

 Serial.println("Selecting number");
 gsm.println("AT+CMGS=\"8600******\"");
 delay(1000);

 Serial.println("Typing message");
 gsm.println("Help me. See my location here.\n\nhttp://www.gps-coordinates.net/\n\n"+msg);
 delay(1000);

 Serial.println("sending ctrl-z");
 gsm.write(0x1A);
 delay(1000);

 gsm.println();
do{}while(1);
}

