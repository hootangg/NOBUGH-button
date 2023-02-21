#include <LiquidCrystal_I2C.h>

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


enum Button
{
    nullBtn, A, B, C, D
};

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

bool buttonsPressed[4] = {false, false, false, false};
Button order[4] = {nullBtn, nullBtn, nullBtn, nullBtn};


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
    // LCD
    lcd.begin();
    lcd.clear();
    lcd.print("Order:");//Hootan Khoda lanatet kone!
}

void loop()
{
    // reset
    if(digitalRead(resetButton) == LOW)
    {
        digitalWrite(resetLed, HIGH);
        for(int i = 0; i < 4; i++)
        {
            buttonsPressed[i] = false;
            digitalWrite(led1 + i, LOW);
            order[i] = nullBtn;
            // print on LCD: READY
            lcd.clear();
            lcd.print("READY");
        }
        delay(12.5);
    }
    else
    {
        digitalWrite(resetLed, LOW);

        // the first player that hits the button
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


        // the order
        for(int i = 0; i < 4; i++)
        {
            if(order[i] == nullBtn)
            {
                if(digitalRead(button1) == LOW)
                    order[i] = A;
                else if(digitalRead(button2) == LOW)
                    order[i] = B;
                else if(digitalRead(button3) == LOW)
                    order[i] = C;
                else if(digitalRead(button4) == LOW)
                    order[i] = D;
            }
            break;
        }

        // show the orders on the LCD
        lcd.clear();
        lcd.print("order:");
        for(int i = 0; i < 4; i++)
        {
            switch(order[i])
            {
                case A:
                    lcd.print("player1");
                    break;
                case B:
                    lcd.print("player2");
                    break;
                case C:
                    lcd.print("player3");
                    break;
                case D:
                    lcd.print("player4");
                    break;
                case nullBtn:
                    break;
            }

            if(i < 3 && order[i + 1] != nullBtn)
                lcd.print("-");
        }
    }
}