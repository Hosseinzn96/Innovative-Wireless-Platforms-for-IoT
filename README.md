#ESP32 IoT Projects Series

This repository contains the complete documentation and source code for three laboratory exercises conducted under the guidance of Professor Daniele Trinchero at Politecnico di Torino. These projects are part of the "Innovative Wireless Platforms for IoT" course and demonstrate the application of ESP32 in various IoT scenarios using BLE and MQTT protocols.

Section 1: ESP32 GY-521 BLE Sensor Node
The project utilizes the ESP32-S3 module to control an RGB LED via Bluetooth Low Energy (BLE) communication, allowing for real-time color adjustments using the nRF smartphone application.
Features:
Utilizes BLE for low-energy communication to adjust LED colors through GATT protocol.
Enables the setting of RGB values individually through dedicated BLE characteristics.
Offers real-time interaction and color adjustment via connected BLE devices.
Setup and Configuration:
The project employs BLEDevice.h and BLEServer.h for setting up BLE communications and Adafruit_NeoPixel.h for controlling the RGB LED.
It defines service and characteristic UUIDs for unique identification and operation.
The setup() function initializes the BLE device, sets up the service and characteristics, and begins advertising.
The ColorCallbacks class handles the RGB color adjustments based on BLE characteristic writes.
Code Explanation:
The code includes comments explaining the major steps like initializing BLE services, defining UUIDs, and setting up color control characteristics. Additional documentation provides insights into the execution flow and BLE interactions.


Section 2: ESP32 NeoPixel BLE Control
Features:
Utilizes the GY-521 module to read real-time motion data including roll, pitch, and yaw angles.
Integrates BLE for wireless transmission of motion data, viewable through the nRF Connect application on multiple devices.
Employs I2C communication protocol for sensor data acquisition and uses Arduino for setup and configurations.
Setup and Configuration:
The ESP32 is set up as a BLE server that broadcasts sensor data continuously.
Sensor data is captured using the MPU6050 library and transmitted over BLE using custom service and characteristic UUIDs.
Code Description:
The code initializes necessary libraries and configurations for BLE communication and sensor data handling.
It reads motion data from the GY-521 sensor using the mpu.getMotion6 method which extracts accelerometer and gyroscope measurements.
Orientation (roll, pitch, yaw) is calculated from the sensor data and formatted for BLE broadcasting.
How it Works?
The sensor node reads continuous sensor data, calculates orientation, and transmits this information via BLE.
Devices equipped with the nRF Connect app can scan and connect to the ESP32 sensor node to receive real-time updates on the device’s orientation.
Application and Scope:
This project can serve as a foundation for applications requiring real-time orientation data over BLE, such as in navigation systems, motion analysis, and interactive interfaces.

Section 3: Integration and Performance of MQTT in IoT Applications
The project is divided into three tasks demonstrating the setup and functionality of MQTT for various IoT applications:
MQTT Messaging: Implementation of MQTT publishers and subscribers to handle custom JSON-formatted messages.
Dynamic Topic Publishing: Simulation of message sending and receiving based on dynamic MQTT topics tied to student IDs.
Temperature Sensor Simulation: Utilizing MQTT and the CayenneLPP format to simulate and transmit temperature sensor data.
Setup and Configuration:
The MQTT broker runs locally at the default port of 1883.
Utilizes Python for the simulation of sensor data and message handling.
Implements CayenneLPP for structured and efficient data encoding.
Key Features:
Custom MQTT Messaging: Implements subscribers and publishers that handle JSON messages, providing insights into data flow management.
Dynamic Topic Management: Dynamically assigns MQTT topics based on user input to simulate real-world applications where device identifiers dictate communication paths.
Sensor Data Simulation and Encoding: Simulates temperature readings, encodes them using CayenneLPP, and broadcasts via MQTT, demonstrating practical applications in IoT environments.
Code Description:
The repository includes detailed scripts for setting up MQTT clients for both publishing and subscribing to topics.
Demonstrates the encoding of data into CayenneLPP format and the decoding of the same for display.
Provides utilities for establishing robust MQTT connections and handling potential connectivity issues.
