// PID constants
#define KP 1.0
#define KI 0.1
#define KD 0.05
#define MAX_PWM 255

// Global variables
double error = 0.0;
double lastError = 0.0;
double integral = 0.0;
double derivative = 0.0;
double setpoint = 50.0; // Desired setpoint
double output = 0.0;

// PID calculation function
void calculatePID(double measured_value) {
    error = setpoint - measured_value;
    integral += error;
    derivative = error - lastError;
    output = (KP * error) + (KI * integral) + (KD * derivative);
    
    if (output > MAX_PWM) {
        output = MAX_PWM;
        integral -= error;
    } else if (output < 0.0) {
        output = 0.0;
        integral -= error;
    }
    
    lastError = error;
}

