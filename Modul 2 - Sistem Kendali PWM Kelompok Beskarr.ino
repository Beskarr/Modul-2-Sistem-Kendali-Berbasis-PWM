//deklarasi pin sensor
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int dataSensor[6];

//deklarasi pin enable
int leftEN = 4;
int rightEN = 2;

//deklarasi pin motor kiri
int leftMotor1 = 5;
int leftMotor2 = 6;

//deklarasi pin motor kanan
int rightMotor1 = 3;
int rightMotor2 = 11;

//deklarasi variabel untuk menyimpan nilai error
int errorDetector = 0;// nilai error berarti tidak ada error yang terjadi  

//Variabel untuk menyimpan nilai analog output
int valnilai1 = 0; //motor kanan
int valnilai2 = 0;
int valnilai3 = 0; //motor kiri
int valnilai4 = 0;

void setup()
{
  //inisialisasi pin sensor
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  pinMode(sensor3, INPUT);
  pinMode(sensor4, INPUT);
  pinMode(sensor5, INPUT);
  pinMode(sensor6, INPUT);
  
  //inisialisasi pin enable
  pinMode(leftEN, OUTPUT);
  pinMode(rightEN, OUTPUT);
  
  //inisialisasi pin motor kiri
  pinMode(leftMotor1, OUTPUT);
  pinMode(leftMotor2, OUTPUT);
  
  //inisialisasi pin motor kanan
  pinMode(rightMotor1, OUTPUT);
  pinMode(rightMotor2, OUTPUT);  
  Serial.begin(9600);
}
void readSensor(){
  dataSensor[0] = analogRead(sensor1);
  dataSensor[1] = analogRead(sensor2);
  dataSensor[2] = analogRead(sensor3);
  dataSensor[3] = analogRead(sensor4);
  dataSensor[4] = analogRead(sensor5);
  dataSensor[5] = analogRead(sensor6);
  delay(1000);
  //perulangan untuk menampilkan masing-masing nilai sensor
  for(int i=0; i<6; i++){
    Serial.print("Sensor");
    Serial.print(i+1);
    Serial.print(": ");
    Serial.print(dataSensor[i]);
    Serial.print("\n");
  } 
}
void loop()
{
  //maxData = 686
  //minData = 33
  readSensor();
  Serial.print("Nilai Last Error: ");
  Serial.print(errorDetector);
  Serial.print("\n");
  errorDetector = 0;
 
  //sensor 1 & 2 mendeteksi gelap
  //motor kanan berputar dengan duty cycle 50%
  if( dataSensor[0] < 35 &&
      dataSensor[1] < 35 &&
      dataSensor[2] > 35 &&
      dataSensor[3] > 35 && 
      dataSensor[4] > 35 &&
      dataSensor[5] > 35){

    valnilai1 = 127;
    valnilai2 = 0;
    valnilai3 = 0;
    valnilai4 = 0;

    
  }
  
  //sensor 2 & 3 mendeteksi gelap
  //motor kanan berputar dengan duty cycle 50% & motor kiri 20%
  if(dataSensor[0] > 35 && dataSensor[1] < 35 &&
     dataSensor[2] < 35 && dataSensor[3] > 35 && 
     dataSensor[4] > 35 && dataSensor[5] > 35){
    valnilai1 = 127;
    valnilai2 = 0;
    valnilai3 = 51;
    valnilai4 = 0;

  }
  
  //sensor 3 & 4 mendeteksi gelap
  //motor kanan & motor kiri berputar dengan duty cycle 60%
  if(dataSensor[0] > 35 && dataSensor[1] > 35 &&
     dataSensor[2] < 35 && dataSensor[3] < 35 && 
     dataSensor[4] > 35 && dataSensor[5] > 35){
    valnilai1 = 153;
    valnilai2 = 0;
    valnilai3 = 153;
    valnilai4 = 0;

  }
  
  //sensor 4 & 5 mendeteksi gelap
  //motor kanan berputar dengan duty cycle 20% & motor kiri 50%
  if(dataSensor[0] > 35 && dataSensor[1] > 35 &&
     dataSensor[2] > 35 && dataSensor[3] < 35 && 
     dataSensor[4] < 35 && dataSensor[5] > 35){
    valnilai1 = 51;
    valnilai2 = 0;
    valnilai3 = 127;
    valnilai4 = 0;

  }
  
  //sensor 5 & 6 mendeteksi gelap
  //motor kiri berputar dengan duty cycle 50%
  if(dataSensor[0] > 35 && dataSensor[1] > 35 &&
     dataSensor[2] > 35 && dataSensor[3] > 35 &&
     dataSensor[4] < 35 && dataSensor[5] < 35){
    valnilai1 = 0;
    valnilai2 = 0;
    valnilai3 = 127;
    valnilai4 = 0;

  }
  
  //semua sensor tidak mendeteksi gelap
  //kedua motor tidak berputar
  if(dataSensor[0] > 35 && dataSensor[1] > 35 && 
     dataSensor[2] > 35 && dataSensor[3] > 35 &&
     dataSensor[4] > 35 && dataSensor[5] > 35){
    valnilai1 = 0;
    valnilai2 = 0;
    valnilai3 = 0;
    valnilai4 = 0;

  }

  //Kasus Percobaan 2

//hanya sensor 1 yang mendeteksi gelap == kondisi sensor 1 & 2 mendeteksi gelap
  if((dataSensor[0] < 35 &&
      dataSensor[1] > 35 &&
      dataSensor[2] > 35 &&
      dataSensor[3] > 35 && 
      dataSensor[4] > 35 &&
      dataSensor[5] > 35)){

        valnilai1 = 127;
        valnilai2 = 0;
        valnilai3 = 0;
        valnilai4 = 0;

        //nilai error detector menjadi 1
        errorDetector = 1;
    }

//hanya sensor 2 yang mendeteksi gelap == kondisi sensor 2 & 3 mendeteksi gelap
    if((dataSensor[0] > 35 &&
      dataSensor[1] < 35 &&
      dataSensor[2] > 35 &&
      dataSensor[3] > 35 && 
      dataSensor[4] > 35 &&
      dataSensor[5] > 35)){

        valnilai1 = 127;
        valnilai2 = 0;
        valnilai3 = 51;
        valnilai4 = 0;

        //nilai error detector menjadi 1
        errorDetector = 1;
    }

//hanya sensor 3 yang mendeteksi gelap == kondisi sensor 3 & 4 mendeteksi gelap
    if((dataSensor[0] > 35 &&
      dataSensor[1] > 35 &&
      dataSensor[2] < 35 &&
      dataSensor[3] > 35 && 
      dataSensor[4] > 35 &&
      dataSensor[5] > 35)){

        valnilai1 = 153;
        valnilai2 = 0;
        valnilai3 = 153;
        valnilai4 = 0;

        //nilai error detector menjadi 1
        errorDetector = 1;
    }

//hanya sensor 4 yang mendeteksi gelap == kondisi sensor 4 & 5 mendeteksi gelap
    if((dataSensor[0] > 35 &&
      dataSensor[1] > 35 &&
      dataSensor[2] > 35 &&
      dataSensor[3] < 35 && 
      dataSensor[4] > 35 &&
      dataSensor[5] > 35)){

        valnilai1 = 51;
        valnilai2 = 0;
        valnilai3 = 127;
        valnilai4 = 0;

        //nilai error detector menjadi 1
        errorDetector = 1;
    }

//hanya sensor 5 / 6 yang mendeteksi gelap == kondisi sensor 5 & 6 mendeteksi gelap
    if((dataSensor[0] > 35 &&
      dataSensor[1] > 35 &&
      dataSensor[2] > 35 &&
      dataSensor[3] > 35 && 
      dataSensor[4] < 35 &&
      dataSensor[5] > 35) ||
      
      (dataSensor[0] > 35 &&
      dataSensor[1] > 35 &&
      dataSensor[2] > 35 &&
      dataSensor[3] > 35 && 
      dataSensor[4] > 35 &&
      dataSensor[5] < 35)){

        valnilai1 = 0;
        valnilai2 = 0;
        valnilai3 = 127;
        valnilai4 = 0;

        //nilai error detector menjadi 1
        errorDetector = 1;
    }


  digitalWrite(rightEN, HIGH);
  analogWrite(rightMotor1, valnilai1);
  analogWrite(rightMotor2, valnilai2);
    
  digitalWrite(leftEN, HIGH);
  analogWrite(leftMotor1, valnilai3);
  analogWrite(leftMotor2, valnilai4);
}