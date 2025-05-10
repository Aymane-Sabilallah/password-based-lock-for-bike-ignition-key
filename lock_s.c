#include<reg51.h>
#include<string.h>

//Micro
#define lcdport P2

//LCD
sbit rs = P3^4;
sbit rw = P3^5;
sbit en = P3^6;

//Motor Pins
sbit m1 = P3^0;
sbit m2 = P3^1;

//KeyRows
sbit r1 = P1^0;
sbit r2 = P1^1;
sbit r3 = P1^2;
sbit r4 = P1^3;

//KeyCol
sbit c1 = P1^4;
sbit c2 = P1^5;
sbit c3 = P1^6;


// buzzPin
sbit buzzer = P1^7;


// Pass
char uid[] = "54321";
char id[5];



// Bike ignition and lock flags
bit bike_on_flag = 0;
bit bike_locked_flag = 0;


int wrong_attempts = 0;

// Function
void lcdint();
void lcddis(char *);
void delay(int);
void lcdcmd(char);
void lcddata(char);
char lcdkey();
char scan_key();
void ignite_on();
void ignite_off();
void sounder();


void main() {
	
	int n;
	char key;

	
	P2 = 0x00;
	P1 = 0x00;
	buzzer = 0;

	lcdint();

	if (bike_on_flag == 1) {
		lcddis("Odometer");
		while (1);
	}

	
	if (bike_locked_flag == 1) {
		lcddis("Bike Locked");
		while (1);
	}

	
	// Initial prompt
	lcddis("Ignition Locked");
	delay(100);
	lcdcmd(0x01);
	lcdcmd(0x02);

	
retry_password:
	lcddis("Enter Password:");
	lcdcmd(0xc0);

	n = 0;
	while (n < 5) {
		key = scan_key();
		id[n] = key;
		delay(70);
		n++;
	}

	lcdcmd(0x01);
	lcdcmd(0x02);

	
	
	if (strcmp(uid, id) == 0) {
		lcddis("Bike ON");
		delay(200);
		ignite_on();
		bike_on_flag = 1;
		delay(200);

		lcdcmd(0x01);
		lcdcmd(0x02);
		lcddis("Enjoy The Ride");
		delay(500);

		lcdcmd(0x01);             // Clear display
		lcdcmd(0x80);             // Move to line 1
		lcddis("Speed : 000 km/h");

		lcdcmd(0xC0);             // Move to line 2
		lcddis("Trip A: 0762 Km");
		while (1);
	}
	
	
	else {
		wrong_attempts++;
		lcddis("Access Denied");
		if(wrong_attempts == 1){
			lcdcmd(0xC0);
		lcddis("Only 2 attempt left");
		}
		else if(wrong_attempts == 2){
			lcdcmd(0xC0);
		lcddis("Only 1 attempt left");
		}
		
		sounder();
		delay(150);
		lcdcmd(0x01);
		lcdcmd(0x02);

			if (wrong_attempts >= 3) {
				int i;
				lcdcmd(0x01);
				lcddis("Warning!");
				delay(200);

				for (i = 3; i > 0; i--) {
						lcdcmd(0x01);
						lcdcmd(0x80);
						lcddis("Locking in ");
						lcddata(i + '0');  // Convert int to char
						lcddata('.');
						lcddata('.');
						lcddata('.');
						delay(100);
				}

				lcdcmd(0x01);
				lcddis("Bike Locked");
				bike_locked_flag = 1;

				while (1);  // Lock the system permanently
		}


		lcddis("Try Again");
		delay(200);
		lcdcmd(0x01);
		lcdcmd(0x02);
		goto retry_password;
	}
}

// LCDFun
void lcdint() {
	
	lcdcmd(0x38);
	delay(2);
	
	lcdcmd(0x01);
	delay(2);
	
	lcdcmd(0x80);
	delay(2);
	
	lcdcmd(0x0e);
	delay(2);
}

void delay(int x) {
	int i, j;
	for (i = 0; i < x; i++)
		for (j = 0; j < 1275; j++);
}

void lcdcmd(char A) {
	lcdport = A;
	rs = 0;
	rw = 0;
	en = 1;
	delay(1);
	en = 0;
}

void lcddis(char *p) {
	while (*p != '\0') {
		lcddata(*p);
		delay(10);
		p++;
	}
}

void lcddata(char value) {
	lcdport = value;
	rs = 1;
	rw = 0;
	en = 1;
	delay(1);
	en = 0;
}

// Buzzer
void sounder() {
	int i;
	for (i = 0; i < 5; i++) {
		buzzer = 1;
		delay(200);
		buzzer = 0;
		delay(200);
	}
}

// Ignition control
void ignite_on() {
	m1 = 1;
	m2 = 0;
}


void ignite_off() {
	m1 = 0;
	m2 = 0;
	delay(20);
	m1 = 0;
	m2 = 1;
	delay(500);
	m1 = 0;
	m2 = 0;
}

// Keypad
char scan_key() {
	char b = 'a';
	while (b == 'a') {
		b = lcdkey();
	}
	return b;
}

char lcdkey() {
	c1 = c2 = c3 = 1;
	r1 = r2 = r3 = r4 = 0;

	r1 = 0; r2 = r3 = r4 = 1;
	if (c1 == 0) { lcddata('*'); delay(2); return '1'; }
	if (c2 == 0) { lcddata('*'); delay(2); return '2'; }
	if (c3 == 0) { lcddata('*'); delay(2); return '3'; }

	r2 = 0; 
	r1 = r3 = r4 = 1;
	
	if (c1 == 0) { lcddata('*'); delay(2); return '4'; }
	if (c2 == 0) { lcddata('*'); delay(2); return '5'; }
	if (c3 == 0) { lcddata('*'); delay(2); return '6'; }

	r3 = 0;
	r1 = r2 = r4 = 1;
	if (c1 == 0) { lcddata('*'); delay(2); return '7'; }
	if (c2 == 0) { lcddata('*'); delay(2); return '8'; }
	if (c3 == 0) { lcddata('*'); delay(2); return '9'; }

	r4 = 0; 
	r1 = r2 = r3 = 1;
	if (c1 == 0) { lcddata('*'); delay(2); return '*'; }
	if (c2 == 0) { lcddata('*'); delay(2); return '0'; }
	if (c3 == 0) { lcddata('*'); delay(2); return '#'; }

	return 'a';
}
