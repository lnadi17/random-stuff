int in = A0;
int out = A1;
int buttonPin = 3;
int last = 1;

void setup() {
	Serial.begin(9600);
	pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
	if (!digitalRead(buttonPin) && last != 0) {
		double inVal = analogRead(in) / (double)1023 * 5;
		double outVal = analogRead(out) / (double)1023 * 5;
		Serial.print("input: ");
		Serial.print(inVal);
		Serial.print("\toutput: ");
		Serial.println(outVal);
		last = 0;
	}
	if (last == 0 && digitalRead(buttonPin)) {
		last = 1;
	}
}