/*
 * A program to undestand the HOPE RFM9X LoRa TX power settings.
 * Documentation: RFM95W-V2.0.pdf
 *
 * Made by clavisound, Aug-Sep 2019
 */

#include <stdio.h>

int paboost = 0; // 0-1
int opower = 0; // 0-15
int mpower = 0; // 0-7
int padac = 0; // 0-4 // TODO: not used

void print_values(){
	float dBm;
	int opowerGuess, opowerGuessB;

	if ( paboost == 0 ) {
		// The documentation is wrong. p. 79 and p. 89 states:
		// Pmax = 10.8 * 0.6 * MaxPower [dBm] (this is ok)
		// Pout = Pmax - (15 - OutputPower) [dBm] instead of 
		// Pout = Pmax - (15 + OutputPower) [dBm] instead of 
		dBm = (10.8 + 0.6 * mpower) - 15 + opower;
		
		// calculation for arduino.
		opowerGuess = (dBm / -0.6 - 7.8) * -1;

		// solve with opower
		// dBm = 10.8 - 15 + opower; =>
		// dBm = -4.2 + opower; =>
		// opower = 4.2 + dBm;
		opowerGuessB = 4.2 + dBm;
	}

	if ( paboost == 1 ) { 
		// The documentation is wrong. p. 79 and p. 89 states:
		// Pout = 17 - (15 - OutputPower) [dBm] instead of 
		// Pout = 17 - (15 + OutputPower) [dBm] instead of 
		dBm = 17 - 15 + opower;
	}

	printf("\npa: %d", paboost);
	printf(" opower: %d", opower);
	printf(" mpower: %d", mpower);
	printf(" dBm: %.2f", dBm);
	// print only for paboost=0
	if ( paboost == 0 ) {
	       	printf(" Guess: %d", opowerGuess);
	       	printf(" GuessB: %d", opowerGuessB);
       	}
}

void loop_opower(){
	for ( opower = 0 ; opower <= 15 ; opower++ ) {
		print_values();
	}
}

void loop_settings_boost(){
	for ( ; opower <= 15; opower++ ) {
		print_values();
	}
	printf("\n");
}


void loop_settings(){
	mpower = 0;
	loop_opower();
	printf("\n");

	mpower = 2;
	loop_opower();
	printf("\n");
	
	mpower = 7;
	loop_opower();
	printf("\n");

	opower = 0;
	for ( mpower = 0; mpower <= 7; mpower++ ) {
		print_values();
	}
	printf("\n");
}

int main(){
	loop_settings();

	paboost = 1;
	opower = 0;
	mpower = 7;
	loop_settings_boost();
}


