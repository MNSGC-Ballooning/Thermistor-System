#define HONEYWELL_TEMP A2 // Defining the analog pin

/////////////// Define constants //////////////////////

float adcMax = 8196; // The maximum adc value given to the thermistor
float A = 0.001125308852122;
float B = 0.000234711863267;
float C = 0.000000085663516; // A, B, and C are constants used for a 10k resistor and 10k thermistor for the steinhart-hart equation
float R1 = 10000; // 10k Ω resistor

/////////////// Intermediate variables ////////////////

float Tinv;
float adcVal;
float logR;
float T; // these three variables are used for the calculation from adc value to temperature

////////// Final Temperature Reading /////////////
float currentTempC; // The current temperature in Celcius
float currentTempF; // The current temperature in Fahrenheit

////////////******* MAIN CODE *******///////////////
void setup() {
  analogReadResolution(13);
  Serial.begin(9600); // Begin the serial monitor
}

void loop() {
  currentTempC = readTemp()-273.15; // converting to celcius
  currentTempF = currentTempC*9/5+32; // converting to fahrenheit
  Serial.print("The current temperature is "); // printing the data in a nice fashion
  Serial.print(currentTempC);
  Serial.println(" degrees Celcius");
  Serial.print("The current temperature is ");
  Serial.print(currentTempF);
  Serial.println(" degrees Fahrenheit");
  delay(1000);
}
/////////////******** END OF LOOP *******///////////


/////////// The function readTemp used in the main code //////////
float readTemp(){ // function returns the temperature in Kelvin
  adcVal = analogRead(HONEYWELL_TEMP);
  logR = log(((adcMax/adcVal)-1)*R1);
  Tinv = A+B*logR+C*logR*logR*logR;
  T = 1/Tinv;
  return T;
}
