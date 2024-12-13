#define BUZZER 9
#define BAUD_RATE 115200

#define UNIT_LENGTH_MILLIS 70


class Morse {
public:
  char character;

  // 6 because numbers have 5 significant characters each
  // adding one filler character reveals the upper bound to be 6
  int code[6];

  Morse(char ch, int temp_code[6]) {
    character = ch;

    for (int i = 0; i < 6; i++) {
      code[i] = temp_code[i];
    }
  }
};

// 9 is filler
Morse alphabetRepresentation[36] = {
  Morse('a', (int[]){ 1, 3, 9, 9, 9, 9 }),
  Morse('b', (int[]){ 3, 1, 1, 1, 9, 9 }),
  Morse('c', (int[]){ 3, 1, 3, 1, 9, 9 }),
  Morse('d', (int[]){ 3, 1, 1, 9, 9, 9 }),
  Morse('e', (int[]){ 1, 9, 9, 9, 9, 9 }),
  Morse('f', (int[]){ 1, 1, 3, 1, 9, 9 }),
  Morse('g', (int[]){ 3, 3, 1, 9, 9, 9 }),
  Morse('h', (int[]){ 1, 1, 1, 1, 9, 9 }),
  Morse('i', (int[]){ 1, 1, 9, 9, 9, 9 }),
  Morse('j', (int[]){ 1, 3, 3, 3, 9, 9 }),
  Morse('k', (int[]){ 3, 1, 3, 9, 9, 9 }),
  Morse('l', (int[]){ 1, 3, 1, 1, 9, 9 }),
  Morse('m', (int[]){ 3, 3, 9, 9, 9, 9 }),
  Morse('n', (int[]){ 3, 1, 9, 9, 9, 9 }),
  Morse('o', (int[]){ 3, 3, 3, 9, 9, 9 }),
  Morse('p', (int[]){ 1, 3, 3, 1, 9, 9 }),
  Morse('q', (int[]){ 3, 3, 1, 3, 9, 9 }),
  Morse('r', (int[]){ 1, 3, 1, 9, 9, 9 }),
  Morse('s', (int[]){ 1, 1, 1, 9, 9, 9 }),
  Morse('t', (int[]){ 3, 9, 9, 9, 9, 9 }),
  Morse('u', (int[]){ 1, 1, 3, 9, 9, 9 }),
  Morse('v', (int[]){ 1, 1, 1, 3, 9, 9 }),
  Morse('w', (int[]){ 1, 3, 3, 9, 9, 9 }),
  Morse('x', (int[]){ 3, 1, 1, 3, 9, 9 }),
  Morse('y', (int[]){ 3, 1, 3, 3, 9, 9 }),
  Morse('z', (int[]){ 3, 3, 1, 1, 9, 9 }),
  Morse('1', (int[]){ 1, 3, 3, 3, 3, 9 }),
  Morse('2', (int[]){ 1, 1, 3, 3, 3, 9 }),
  Morse('3', (int[]){ 1, 1, 1, 3, 3, 9 }),
  Morse('4', (int[]){ 1, 1, 1, 1, 3, 9 }),
  Morse('5', (int[]){ 1, 1, 1, 1, 1, 9 }),
  Morse('6', (int[]){ 3, 1, 1, 1, 1, 9 }),
  Morse('7', (int[]){ 3, 3, 1, 1, 1, 9 }),
  Morse('8', (int[]){ 3, 3, 3, 1, 1, 9 }),
  Morse('9', (int[]){ 3, 3, 3, 3, 1, 9 }),
  Morse('0', (int[]){ 3, 3, 3, 3, 3, 9 }),
};


void pause(int time) {

  digitalWrite(BUZZER, LOW);
  delay(time * UNIT_LENGTH_MILLIS);
}

void play(int time) {
  digitalWrite(BUZZER, HIGH);
  delay(time * UNIT_LENGTH_MILLIS);
  digitalWrite(BUZZER, LOW);
}


//================================STARTS================================

void setup() {
  pinMode(BUZZER, OUTPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  Serial.println("Enter data to be converted: ");

  // do nothing until data is received
  while (Serial.available() == 0) {};

  String data = Serial.readString();
  data.toLowerCase();

  for (int i = 0; i < data.length(); i++) {
    char character = data[i];

    Serial.print(character);

    // if the character is space, silence for 7 units of silence representing space between words and then continue
    // to avoid adding the extra space between characters in the next block of code
    if (character == ' ') {
      pause(7);
      continue;
    }


    // play character
    for (int j = 0; j < 36; j++)
    {
      // if the character is successfully found
      // that is if it is an alphabet or number
      if(character == alphabetRepresentation[j].character)
      {
        for(int k = 0; k < 6; k++)
        {
          // if 9 is reached in the morse representation quit and go to the next character
          if(alphabetRepresentation[j].code[k] == 9)
          {
            break;
          }

          // play the corresponding part of the character with a single pause after
          // denoting seperation between parts of the smae character
          play(alphabetRepresentation[j].code[k]);
          pause(1);
        }
      }
    }


    // after playing the character, pause for 3 units of time denoting space between characters in a word
    // except if we're at the end or currently at space or the next character is a space
    if(i != data.length() - 1 && data[i] != " " && data[i + 1] != " ")
    {
      pause(3);
    }

  }

  // new line after the last word
  Serial.println();
}




