#include <LiquidCrystal.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

#define LDR_PIN A1
#define TMP36_PIN A0
#define POTENTIOMETER_PIN A2

int ledGreen = 13;
int ledYellow = 12;
int ledRed = 11;

int temperatura;

int fotoceldaPin = 9;
int fotoceldaVal = 0;


void setup(){
  //define os pinos
  pinMode(fotoceldaPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
 // pinMode(piezo, OUTPUT);
  
  //inicializando lcd
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Inicializando");
  delay (1000);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.clear();
  
  //apresenta nome e o grupo do trabalho
  lcd.setCursor(0, 0);
  lcd.print("GLOBAL SOLUTION");
  delay(1000);
  lcd.setCursor(3, 1);
  lcd.print("Grupo Atticus");
  delay(2000);
  lcd.clear();
}


void loop() 
{
  //recebe as leituras dos valores de luminosidade, umidade e temperatura
  fotoceldaVal = analogRead(fotoceldaPin);
  int luminosidade = analogRead(LDR_PIN);
  float temperatura = getTemperature();
  int umidade = getHumidity();
  
  //Ambiente claro 
  if (fotoceldaVal >= 600)
  	{ 
      digitalWrite (ledGreen, LOW);
      digitalWrite (ledRed, HIGH);
      digitalWrite (ledYellow, LOW);
    
	  lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Amb. muito claro"); 
      lcd.setCursor(0,1); 
      lcd.print("Lum: ");
      lcd.print(fotoceldaVal);
    }
  
  //Ambiente meia luz
  else if (fotoceldaVal >= 400 && fotoceldaVal < 600)
  	{ 
      digitalWrite (ledGreen, LOW);
      digitalWrite (ledRed, LOW);
      digitalWrite (ledYellow, HIGH);
    
      lcd.clear();
      lcd.setCursor(0,0);  
      lcd.print("Amb. meia luz"); 
      lcd.setCursor(0,1);
      lcd.print("Lum: ");
      lcd.print(fotoceldaVal);
    }
  
  //Ambiente escuro
  else if (fotoceldaVal < 400)
  	{ 
      digitalWrite (ledGreen, HIGH);
      digitalWrite (ledRed, LOW);
      digitalWrite (ledYellow, LOW);
    
      lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("Amb. Escuro"); 
      lcd.setCursor(0,1);
      lcd.print("Lum: ");
  	  lcd.print(fotoceldaVal);
	}  
  delay(5000);

  //Temperatuar baixa
  if (temperatura < 10)
  {
    digitalWrite (ledGreen, LOW);
    digitalWrite (ledRed, LOW);
    digitalWrite (ledYellow, HIGH);
    
    lcd.clear();
  
  	lcd.setCursor(0,0);
  	lcd.print("Temp. Baixa");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
  	lcd.print(temperatura);
  	lcd.print(" C");
  }
  
  //Temperatura ok
  else if (temperatura >= 10 && temperatura < 15)
  {
    digitalWrite (ledGreen, HIGH);
    digitalWrite (ledRed, LOW);
    digitalWrite (ledYellow, LOW);
    
    lcd.clear();
  
  	lcd.setCursor(0,0);
  	lcd.print("Temp. Ok");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
  	lcd.print(temperatura);
  	lcd.print(" C");
  }
  
  //Temperatura alta
  else if (temperatura > 15)
  {
    digitalWrite (ledGreen, LOW);
    digitalWrite (ledRed, LOW);
    digitalWrite (ledYellow, HIGH);
    
    lcd.clear();
  
  	lcd.setCursor(0,0);
  	lcd.print("Temp. Alta");
    lcd.setCursor(0,1);
    lcd.print("Temp: ");
  	lcd.print(temperatura);
  	lcd.print(" C");
  }
  delay(5000);

  
  //Umidade baixa
  if (umidade < 50)
  {
    digitalWrite (ledGreen, LOW);
    digitalWrite (ledRed, HIGH);
    digitalWrite (ledYellow, LOW);
    
    lcd.clear();
  
  	lcd.setCursor(0,0);
  	lcd.print("Umidade Baixa");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
  	lcd.print(umidade);
  	lcd.print("%");
  }
  
  //Umidade ok
  else if(umidade >= 50 && umidade < 70)
  {
    lcd.clear();
  
  	lcd.setCursor(0,0);
  	lcd.print("Umidade Ok");
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
  	lcd.print(umidade);
  	lcd.print("%");
  }
  
  //Umidade alta
  else if (umidade > 70)
  {
    digitalWrite (ledGreen, LOW);
    digitalWrite (ledRed, HIGH);
    digitalWrite (ledYellow, LOW);
    
    lcd.clear();
  
  	lcd.setCursor(0,0);
  	lcd.print("Umidade Alta"); 
    lcd.setCursor(0,1);
    lcd.print("Umidade: ");
  	lcd.print(umidade);
  	lcd.print("%");
  } 
  delay(5000);
}

//Leitura da temperatura
float getTemperature() 
{
  int sensorValue = analogRead(TMP36_PIN);
  float voltage = sensorValue * 5.0 / 1023.0;
  float temperature = (voltage - 0.5);
  
  temperature *= 100;
  
  return temperature;
}

//Leitura da umidade
float getHumidity() 
{
  int sensorValue = analogRead(POTENTIOMETER_PIN);
  int humidity = map(sensorValue, 0, 1023, 0, 100);
  return humidity;
}