const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;
const int resetButton = 6;
const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
const int led4 = 10;
const int resetLed = 11;

bool buttonsPressed[4] = {false, false, false, false};

void setup() {
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  pinMode(button4, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(resetLed, OUTPUT);
}

void loop()
{

    if(digitalRead(resetButton) == LOW)
    {
        digitalWrite(resetLed, HIGH);
        for(int i = 0; i < 4; i++)
        {
            buttonsPressed[i] = false;
            digitalWrite(led1 + i, LOW);
        }
        delay(12.5);
    }
    else
    {
        digitalWrite(resetLed, LOW);

        if(!buttonsPressed[0] && !buttonsPressed[1] && !buttonsPressed[2] && !buttonsPressed[3])
        {
            if(digitalRead(button1) == LOW)
            {
                buttonsPressed[0] = true;
                digitalWrite(led1, HIGH);
                for(int i = 1; i < 4; i++)
                {
                    buttonsPressed[i] = false;
                    digitalWrite(led1 + i, LOW);
                }
            }
            else if(digitalRead(button2) == LOW)
            {
                buttonsPressed[1] = true;
                digitalWrite(led2, HIGH);
                for(int i = 0; i < 4; i++)
                {
                    if(i != 1)
                    {
                        buttonsPressed[i] = false;
                        digitalWrite(led1 + i, LOW);
                    }
                }
            }
            else if(digitalRead(button3) == LOW)
            {
                buttonsPressed[2] = true;
                digitalWrite(led3, HIGH);
                for(int i = 0; i < 4; i++)
                {
                    if(i != 2)
                    {
                        buttonsPressed[i] = false;
                        digitalWrite(led1 + i, LOW);
                    }
                }
            }
            else if(digitalRead(button4) == LOW)
            {
                buttonsPressed[3] = true;
                digitalWrite(led4, HIGH);
                for(int i = 0; i < 4; i++)
                {
                    if(i != 3)
                    {
                        buttonsPressed[i] = false;
                        digitalWrite(led1 + i, LOW);
                    }
                }
            }
        }
    }
}