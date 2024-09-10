
#include <BLEServer.h>
#include <BLEDevice.h>

#include <Adafruit_NeoPixel.h>

#define LED_COUNT 1  // Number of NeoPixel LEDs
#define NEOPIXEL_PIN 48 // Pin connected to NeoPixel data input
Adafruit_NeoPixel strip(LED_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Service UUID
#define SERVICE_UUID "659f11b8-83a6-4dc8-b0c9-c540a19db995"
// Characteristic UUIDs for each color channel
#define RED_CHARACTERISTIC_UUID   "29f65805-fee8-457c-abba-bd93b5c176f4"
#define GREEN_CHARACTERISTIC_UUID "7af1d167-7628-4d81-97cd-e01ad8b0f13c"
#define BLUE_CHARACTERISTIC_UUID  "2d364af7-5315-4b55-850a-281ec984c076"

BLECharacteristic *pRedCharacteristic;
BLECharacteristic *pGreenCharacteristic;
BLECharacteristic *pBlueCharacteristic;

class MyServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) override {
    };

    void onDisconnect(BLEServer* pServer) override {
    }
};

class ColorCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) override {
        std::string value = pCharacteristic->getValue();

        if (value.length() >= 1) {
            // Assume the first byte is always present and represents a color intensity.
            uint8_t primaryColorIntensity = static_cast<uint8_t>(value[0]);

            // Initialize RGB components to zero.
            uint8_t red = 0, green = 0, blue = 0;

            // Determine which characteristic is being written to adjust colors.
            if (pCharacteristic == pRedCharacteristic) {
                red = primaryColorIntensity;
                // Add green if a second byte is present for mixing.
                if (value.length() > 1) green = static_cast<uint8_t>(value[1]);
            } else if (pCharacteristic == pGreenCharacteristic) {
                green = primaryColorIntensity;
                // Add blue if a second byte is present for mixing.
                if (value.length() > 1) blue = static_cast<uint8_t>(value[1]);
            } else if (pCharacteristic == pBlueCharacteristic) {
                blue = primaryColorIntensity;
                // Add red if a second byte is present for mixing.
                if (value.length() > 1) red = static_cast<uint8_t>(value[1]);
            }

            // Set the pixel color and show.
            strip.setPixelColor(0, strip.Color(red, green, blue));
            strip.show();
        }
    }
};

void setup() {
    Serial.begin(115200);

    // Initialize NeoPixel strip
    strip.begin();
    strip.fill(strip.Color(255, 255, 255)); // Set all pixels to white
    strip.show(); // Initialize all pixels to 'off'

    BLEDevice::init("RGB Controller Group3");
    BLEServer *pServer = BLEDevice::createServer();
    pServer->setCallbacks(new MyServerCallbacks());

    BLEService *pService = pServer->createService(SERVICE_UUID);

    // Create characteristics for each color channel and set their callbacks
    pRedCharacteristic = pService->createCharacteristic(
                            RED_CHARACTERISTIC_UUID,
                            BLECharacteristic::PROPERTY_WRITE);
    pGreenCharacteristic = pService->createCharacteristic(
                            GREEN_CHARACTERISTIC_UUID,
                            BLECharacteristic::PROPERTY_WRITE);
    pBlueCharacteristic = pService->createCharacteristic(
                            BLUE_CHARACTERISTIC_UUID,
                            BLECharacteristic::PROPERTY_WRITE);

    ColorCallbacks* colorCallbacks = new ColorCallbacks();
    pRedCharacteristic->setCallbacks(colorCallbacks);
    pGreenCharacteristic->setCallbacks(colorCallbacks);
    pBlueCharacteristic->setCallbacks(colorCallbacks);

    // Start the service
    pService->start();

    // Start advertising
    BLEAdvertising *pAdvertising = pServer->getAdvertising();
    pAdvertising->start();
}

void loop() {
    // No need for loop function since BLE interactions are handled by callbacks
}
