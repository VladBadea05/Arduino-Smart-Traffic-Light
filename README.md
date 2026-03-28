# Smart Traffic Light with Emergency Override 🚦

## About the Project
This is a personal learning project built to practice embedded programming concepts like **Finite State Machines (FSM)** and **non-blocking delays** in C++. It simulates a smart traffic light that operates normally but can be interrupted by a loud sound (simulating an emergency siren) to enter a safe state.

## Key Features
* **Finite State Machine Architecture:** The system transitions cleanly between Red, Green, Yellow, and Emergency states using a C++ `enum`.
* **Non-Blocking Logic:** Replaced standard `delay()` functions with `millis()` timers to ensure the microcontroller can constantly monitor the microphone without freezing.
* **Sensor Noise Filtering:** Averages multiple readings from the sound sensor to prevent false triggers.

## Hardware Used
* Arduino Uno
* Sound Sensor (Microphone)
* 16x2 LCD Display
* 3x LEDs (Red, Yellow, Green)

## Why I Built This
As a student passionate about embedded systems and the automotive industry, I wanted to move beyond basic linear code. This project helped me understand how real-world controllers manage multiple tasks simultaneously and prioritize emergency inputs gracefully.
