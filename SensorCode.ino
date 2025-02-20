#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED Setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Ultrasonic Sensor Pins
#define TRIG_PIN 7
#define ECHO_PIN 6

void setup() {
    Serial.begin(115200);
    
    // Initialize OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        for (;;);
    }
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);

    // Initialize HC-SR04
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
}

void loop() {
    long duration;
    float distance;

    // Trigger the sensor
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Read the echo time
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2; // Convert time to distance (cm)

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    // Update OLED display
    display.clearDisplay();
    display.setCursor(10, 20);
    
    if (distance > 0 && distance <= 10) {
        display.setTextSize(1);
        display.print("Object Detected");
        
    } else {
        display.setTextSize(1);
        display.print("No Object detected.");
    }

    display.display(); // Show on OLED
    delay(500); // Wait before next reading
}
