// Use Serial for UART (assuming Arduino connected via Serial or Serial1)

// PWM Integers

#define SUBTRACTCONST 48
#define MAXINDEX 2
#define MININDEX 0

int pwm[3] = {50, 150, 255};
int pwm_index = 1; // 1 is the default PWM speed
bool active = true; // Flag to indicate if intended to be active

int lt = 0;
int rt = 0;
int a = 0;
int b = 0;
int lb = 0;
int rb = 0;


void setup() {
  Serial.begin(9600);
  while (!Serial) { ; }  // Wait for Serial to initialize (optional)
  Serial.println("Ready to receive joystick data");
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(10, OUTPUT);

  /*pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);*/

  String inputLine = "";

  while (active) {
      while (Serial.available() > 0) {
      char received = Serial.read();
      if (received == '\n') {
        // Process the full line here
        processJoystickData(inputLine);

        inputLine = "";  // Clear for next line
        // int lt = dataArray[0];
        // int rt = dataArray[1];
        // int a = dataArray[2];
        // int b = dataArray[3];
        // int lb = dataArray[4];
        // int rb = dataArray[5];

        Serial.print(lt);
        Serial.print(" ");
        Serial.print(rt);
        Serial.print(" ");
        Serial.print(a);
        Serial.print(" ");
        Serial.print(b);
        Serial.print(" ");
        Serial.print(lb);
        Serial.print(" ");
        Serial.println(rb);
        Serial.println(pwm_index);


        // Main logic goes here!

        if (lt || lb || a || b) {

          // Check for estop condition

          if (lt == 1 && rt == 1 && lb == 1 && rb == 1 && a == 1 && b == 1) {
            eStop();
          }
          // If no eStop run the functions
          else {

            // MoveLeft commands 
            moveLeft(lt, lb);
            //moveRight(rt, rb);

            // Gearing commands

            if(a) {
              gearDown();
            }

            if(b) {
              gearUp();
            }

          }

          // Brake command

        } else {
          Brake();
        }



        
        

      } else {
        inputLine += received;
      }




    }

  }


}

void loop() {
  // Read data from UART until newline is received
}

/*

PWM PINS:
- Board 1:
- IN1: D3
- IN2: D5
- IN3: D6
- IN4: D10

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


void Brake() {
  analogWrite(3, 255);
  analogWrite(5, 255);
  analogWrite(6, 255);
  analogWrite(10, 255);
  /*analogWrite(A0, 255);
  analogWrite(A1, 255);
  analogWrite(A2, 255);
  analogWrite(A3, 255);*/
}

/*void moveRight(int RT, int RB) {

  if (RT^RB) {
    analogWrite(3, pwm[pwm_index]*RT); // Set forwards
    analogWrite(5, pwm[pwm_index]*RB); // Set backwards
    analogWrite(6, pwm[pwm_index]*RT);
    analogWrite(10, pwm[pwm_index]*RB);
  }
}*/

void moveLeft(int LT, int LB) {
  if (LT^LB) {
    analogWrite(3, pwm[pwm_index]*LT);
    analogWrite(5, pwm[pwm_index]*LB);
    analogWrite(6, pwm[pwm_index]*LT);
    analogWrite(10, pwm[pwm_index]*LB);
  }
}

void gearUp() {

  if (pwm_index < 2) {
    pwm_index++;
  }

}

void gearDown() {

  if (pwm_index > 0) {
    pwm_index--;
  }

}

void eStop() {

  Brake();
  active = false;
  

}

// Function to parse and use joystick data string "lx,ly,lt,rt"
void processJoystickData(String data) {
  // Serial.print("Received data: ");
  // Serial.println(data);

  char valueArray[12];

  data.toCharArray(valueArray, sizeof(valueArray));

  // Serial.println(valueArray);

  lt = ((int)valueArray[0]) - SUBTRACTCONST;
  rt = ((int)valueArray[2]) - SUBTRACTCONST;
  a = ((int)valueArray[4]) - SUBTRACTCONST;
  b = ((int)valueArray[6]) - SUBTRACTCONST;
  lb = ((int)valueArray[8]) - SUBTRACTCONST;
  rb = ((int)valueArray[10]) - SUBTRACTCONST;


  
  


    // Use the variables as needed in your code here
  }
