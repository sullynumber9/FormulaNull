// Use Serial for UART (assuming Arduino connected via Serial or Serial1)

// PWM Integers

int pwm[3] = {150, 200, 255};
int pwm_index = 1; // 1 is the default PWM speed


void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }  // Wait for Serial to initialize (optional)
  Serial.println("Ready to receive joystick data");
}

String inputLine = "";

void loop() {
  // Read data from UART until newline is received
  while (Serial.available() > 0) {
    char received = Serial.read();
    if (received == '\n') {
      // Process the full line here
      processJoystickData(inputLine);
      inputLine = "";  // Clear for next line
    } else {
      inputLine += received;
    }
  }
}

/*

PWM PINS:
- Board 1:
- IN1: D3
- IN2: D5
- IN3: D6
- IN4: D0

- Board 2:
- IN1: A0
- IN2: A1
- IN3: A2
- IN4: A3

// MANAN
- moveRight()
- moveLeft()

// ADAM
- gearUp()
- gearDown()
- eStop()
*/




void moveRight() {
  analogWrite(3, pwm*LT);
  analogWrite(5, pwm*LB);
}

void moveLeft() {

}

void gearUp() {


}

void gearDown() {


}

void eStop() {

}

// Function to parse and use joystick data string "lx,ly,lt,rt"
void processJoystickData(String data) {
  // Serial.print("Received data: ");
  Serial.println(data);

  int lt, rt, a, b, lb, rb;
  int parsed = sscanf(data.c_str(), "%d,%d,%d,%d,%d", &lt, &rt, &a, &b, &lb, &rb);

  

  
  if (parsed == 10) {
    Serial.print("Left Trigger: ");
    Serial.println(lt);
    Serial.print("Right Trigger: ");
    Serial.println(rt);
    Serial.print("A Button: ");
    Serial.println(a);
    Serial.print("B Button: ");
    Serial.println(b);
    Serial.print("Left Bumper: ");
    Serial.println(lb);
    Serial.print("Right Bumper: ");
    Serial.println(rb);

    return lt, rt, a, b, lb, rb;


    // Use the variables as needed in your code here
  }
}
