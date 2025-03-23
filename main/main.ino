#include <NewPing.h>

// Definisikan pin untuk push button, sensor ultrasonik, dan LED
const int buttonPin = 8; // Pin untuk push button
const int trigPin = 10;    // Pin untuk trigger sensor ultrasonik
const int echoPin = 9;    // Pin untuk echo sensor ultrasonik
const int ledPin = 13;     // Pin untuk LED

// Baudrate 
#define baudrate 115200

// Kondisi
#define on HIGH
#define off LOW

// Inisialisasi jarak maksimum
const int maxDistance = 30; // Jarak maksimum dalam cm
const int defaultDistance = 50; // Default jarak

// Inisialisasi objek NewPing dengan jarak maksimum
NewPing sonar(trigPin, echoPin, defaultDistance); // maxDistance adalah jarak maksimum

// Variabel untuk menyimpan status button
int buttonState = 0;

// Variabel untuk menyimpan waktu
unsigned long previousMillis = 0; 
const long interval = 100; // Interval pengukuran dalam milidetik

void setup() {
  // Inisialisasi pin
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT); // Set pin LED sebagai output
  Serial.begin(baudrate); // Mulai komunikasi serial
}

void loop() {
  // Membaca status button
  buttonState = digitalRead(buttonPin);

  // Menampilkan kondisi button
  displayButtonState(buttonState);

  // Mengambil waktu saat ini
  unsigned long currentMillis = millis();

  // Cek apakah interval waktu telah berlalu
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis; // Simpan waktu saat ini

    // Mengukur jarak menggunakan sensor ultrasonik
    float distance = readDistance();

    // Menampilkan kondisi jarak
    displayDistance(distance);

    // Mengontrol LED berdasarkan jarak
    controlLED(distance);
  }
}

// Fungsi untuk menampilkan kondisi tombol
void displayButtonState(int state) {
  if (state == off) {
    Serial.println("Button is pressed");
  } else {
    Serial.println("Button is not pressed");
  }
}

// Fungsi untuk menampilkan kondisi jarak
void displayDistance(float distance) {
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}

// Fungsi untuk membaca jarak menggunakan sensor ultrasonik
float readDistance() {
  unsigned int uS = sonar.ping(); // Mengukur waktu ping
  return uS / US_ROUNDTRIP_CM; // Menghitung jarak dalam cm
}

// Fungsi untuk mengontrol LED berdasarkan jarak
void controlLED(float distance) {
  if (distance < maxDistance) {
    digitalWrite(ledPin, on); // Nyalakan LED jika jarak kurang dari maxDistance
  } else {
    digitalWrite(ledPin, off); // Matikan LED jika jarak lebih dari atau sama dengan maxDistance
  }
}
