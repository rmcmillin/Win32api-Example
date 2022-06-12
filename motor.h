//fake motor control library

#define RPM_MIN		0
#define RPM_MAX		2000
#define DISTANCE_MIN	0
#define DISTANCE_MAX	300

typedef enum MotorState {
	MOTOR_OFF,
	MOTOR_ON
}motorState_t;

static const char *motorStateStrings[] = {
	"MOTOR OFF", "MOTOR ON"
};

static const int motorStateColour[] = { //BGR???
	0x0000ff, 0x00ff00
};

void motor_run(HWND hwnd);

motorState_t motor_getState();
unsigned int motor_getRPM();
unsigned int motor_getRPMSetPoint();
unsigned int motor_getManifoldDistance();
unsigned int motor_getManifoldDistanceSetPoint();

int motor_setState(HWND hwnd, motorState_t state);
int motor_setRPM(HWND hwnd, unsigned int rpm);
int motor_setRPMSetPoint(HWND hwnd, unsigned int setPoint);
int motor_setManifoldDistance(HWND hwnd, unsigned int distance);
int motor_setManifoldDistanceSetPoint(HWND hwnd, unsigned int setPoint);

//dialog for button
BOOL CALLBACK mControlDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);