// Use Serial for UART (assuming Arduino connected via Serial or Serial1)
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

// Function to parse and use joystick data string "lx,ly,lt,rt"
void processJoystickData(String data) {
  // Serial.print("Received data: ");
  Serial.println(data);

  float lt, rt, a, b, lb, rb;
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
haha
    // Use the variables as needed in your code here
  }
}
