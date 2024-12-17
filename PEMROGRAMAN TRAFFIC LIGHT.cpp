// Deklarasi pin untuk setiap lampu di jalur 1, 2, 3, dan 4
int red1 = 13, yellow1 = 12, green1 = 11; // Jalur 1
int red2 = 10, yellow2 = 9, green2 = 8;  // Jalur 2
int red3 = 7, yellow3 = 6, green3 = 5;   // Jalur 3
int red4 = 4, yellow4 = 3, green4 = 2;   // Jalur 4

// Variabel jumlah kendaraan
int vehicles1and3 = 0; // Kendaraan di jalur 1 dan 3
int vehicles2and4 = 0; // Kendaraan di jalur 2 dan 4

// Variabel simulasi
const int testCount = 10; // Jumlah percobaan
int testResults[testCount][3]; // Array untuk menyimpan hasil [Percobaan][Kendaraan1+3, Kendaraan2+4, Output]

void setup() {
  // Serial Monitor
  Serial.begin(9600);

  // Atur semua pin sebagai output
  pinMode(red1, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(green1, OUTPUT);

  pinMode(red2, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(green2, OUTPUT);

  pinMode(red3, OUTPUT);
  pinMode(yellow3, OUTPUT);
  pinMode(green3, OUTPUT);

  pinMode(red4, OUTPUT);
  pinMode(yellow4, OUTPUT);
  pinMode(green4, OUTPUT);

  // Jalankan simulasi
  simulateTraffic();
}

void loop() {
  // Setelah simulasi selesai, lampu kembali berjalan normal
  normalTrafficCycle();
}

// Fungsi simulasi lalu lintas
void simulateTraffic() {
  for (int i = 0; i < testCount; i++) {
    // Simulasi jumlah kendaraan acak
    vehicles1and3 = random(10, 30); // Kendaraan di jalur 1 dan 3
    vehicles2and4 = random(10, 30); // Kendaraan di jalur 2 dan 4

    // Tentukan jalur mana yang mendapatkan lampu hijau
    int greenOutput;
    if (abs(vehicles1and3 - vehicles2and4) <= 2) {
      // Jika jumlah kendaraan hampir sama, jalankan logika normal
      normalTrafficCycleOnce();
      greenOutput = 0; // Normal
    } else if (vehicles1and3 > vehicles2and4) {
      greenOutput = 1; // Jalur 1+3 mendapatkan lampu hijau
      activateTraffic(red2, yellow2, green2, red4, yellow4, green4, red1, yellow1, green1, red3, yellow3, green3);
    } else {
      greenOutput = 2; // Jalur 2+4 mendapatkan lampu hijau
      activateTraffic(red1, yellow1, green1, red3, yellow3, green3, red2, yellow2, green2, red4, yellow4, green4);
    }

    // Simpan hasil percobaan
    testResults[i][0] = vehicles1and3;
    testResults[i][1] = vehicles2and4;
    testResults[i][2] = greenOutput;
  }

  // Tampilkan hasil simulasi
  printResults();
}

// Fungsi untuk mengatur lampu lalu lintas
void activateTraffic(int redOpp1, int yellowOpp1, int greenOpp1, 
                     int redOpp2, int yellowOpp2, int greenOpp2, 
                     int redActive1, int yellowActive1, int greenActive1, 
                     int redActive2, int yellowActive2, int greenActive2) {

  // Jalur aktif (lampu hijau menyala)
  digitalWrite(redActive1, LOW);  // Mematikan lampu merah di jalur aktif
  digitalWrite(redActive2, LOW);  // Mematikan lampu merah di jalur aktif
  digitalWrite(greenActive1, HIGH);  // Menyalakan lampu hijau di jalur aktif
  digitalWrite(greenActive2, HIGH);  // Menyalakan lampu hijau di jalur aktif

  // Jalur lawan (lampu merah menyala)
  digitalWrite(redOpp1, HIGH);  // Menyalakan lampu merah di jalur lawan
  digitalWrite(redOpp2, HIGH);  // Menyalakan lampu merah di jalur lawan
  digitalWrite(greenOpp1, LOW);  // Mematikan lampu hijau di jalur lawan
  digitalWrite(greenOpp2, LOW);  // Mematikan lampu hijau di jalur lawan

  delay(5000); // Durasi lampu hijau (5 detik)

  // Jalur aktif (lampu kuning menyala)
  digitalWrite(greenActive1, LOW);  // Mematikan lampu hijau
  digitalWrite(greenActive2, LOW);  // Mematikan lampu hijau
  digitalWrite(yellowActive1, HIGH);  // Menyalakan lampu kuning
  digitalWrite(yellowActive2, HIGH);  // Menyalakan lampu kuning

  delay(3000); // Durasi lampu kuning (3 detik)

  // Jalur aktif (lampu merah menyala)
  digitalWrite(yellowActive1, LOW);  // Mematikan lampu kuning
  digitalWrite(yellowActive2, LOW);  // Mematikan lampu kuning
  digitalWrite(redActive1, HIGH);  // Menyalakan lampu merah
  digitalWrite(redActive2, HIGH);  // Menyalakan lampu merah
}

// Fungsi untuk satu siklus normal
void normalTrafficCycleOnce() {
  // Jalur 1 dan 3 menyala hijau, jalur 2 dan 4 merah
  activateTraffic(red2, yellow2, green2, red4, yellow4, green4, red1, yellow1, green1, red3, yellow3, green3);
  
  // Jalur 2 dan 4 menyala hijau, jalur 1 dan 3 merah
  activateTraffic(red1, yellow1, green1, red3, yellow3, green3, red2, yellow2, green2, red4, yellow4, green4);
}

// Fungsi untuk siklus normal tanpa batas
void normalTrafficCycle() {
  while (true) {
    normalTrafficCycleOnce();
  }
}

void printResults() {
  Serial.println("Hasil Percobaan:");
  Serial.println("Percobaan\tJalur 1+3\tJalur 2+4\tLampu Hijau di Jalur");

  for (int i = 0; i < testCount; i++) {
    Serial.print(i + 1);
    Serial.print("\t\t");
    Serial.print(testResults[i][0]); // Kendaraan Jalur 1+3
    Serial.print("\t\t");
    Serial.print(testResults[i][1]); // Kendaraan Jalur 2+4
    Serial.print("\t\t");
    if (testResults[i][2] == 0) {
      Serial.println("Normal"); // Siklus normal
    } else {
      Serial.println(testResults[i][2]); // Jalur yang mendapatkan lampu hijau
    }
  }
}