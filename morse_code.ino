#define BUZZER 9
#define BAUD_RATE 115200

#define UNIT_LENGTH_MILLIS 50



void setup() {
  pinMode(BUZZER, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  Serial.println("Enter data to be converted: ");

  // do nothing until data is received
  while (Serial.available() == 0){};

  String data = Serial.readString();

  for(int i = 0; i < data.length(); i++)
  {

    Serial.println(data[i]);

    // if the character is space, silence for 7 units of silence representing space between words and then continue
    // to avoid adding the extra space between characters in the next block of code
    if (data[i] == ' ')
    {
      silence(7);
      continue;
    }


    // play character at data[i]
    // if (i != data.length - 1 && data[i] != " " && data[++i] != " ")
    //    play 3 unit of silence indicating space between parts characters
  }
  
}




void silence(int time)
{
  delay(time * UNIT_LENGTH_MILLIS);
}

void play(int time)
{
  digitalWrite(BUZZER, HIGH);
  delay(time * UNIT_LENGTH_MILLIS);
  digitalWrite(BUZZER, LOW);
}



class Morse
{
  public:
    char character;
    int code[5];

    Morse(char ch, int temp_code[5]) {
      character = ch;

      for (int i = 0; i < 5; i++)
      {
        code[i] = temp_code[i];
      }
    }
};

Morse alphabetRepresentation[36] = 
{
  Morse ('a', {1, 0, 3}),
}