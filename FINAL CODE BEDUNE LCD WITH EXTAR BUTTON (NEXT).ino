
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
const int nextButton = 12;


enum Button
{
    nullBtn = -1, A, B, C, D
};

bool buttonsPressed[4] = {false, false, false, false};
Button order[4] = {nullBtn, nullBtn, nullBtn, nullBtn};
int orderIndex = 1;

void reset()
{
    digitalWrite(resetLed, HIGH);
    orderIndex = 1;
    for(int i = 0; i < 4; i++)
    {
        buttonsPressed[i] = false;
        digitalWrite(led1 + i, LOW);
        order[i] = nullBtn;
    }
    delay(12.5);
}

void buttonPressed(int buttonIndex)
{
    buttonsPressed[buttonIndex] = true;
    digitalWrite(led1 + buttonIndex, HIGH);
    switch(buttonIndex)
    {
        case 0:
            order[0] = A;
            break;
        case 1:
            order[0] = B;
            break;
        case 2:
            order[0] = C;
            break;
        case 3:
            order[0] = D;
            break;
        default:
            break;
    }
    for(int i = 0; i < 4; i++)
        if(i != buttonIndex)
        {
            buttonsPressed[i] = false;
            digitalWrite(led1 + i, LOW);
        }
}

void checkOrder()
{
    if(digitalRead(button1) == LOW)
        buttonPressed(0);

    if(digitalRead(button2) == LOW)
        buttonPressed(1);

    if(digitalRead(button3) == LOW)
        buttonPressed(2);

    if(digitalRead(button4) == LOW)
        buttonPressed(3);
}

void setOrder()
{
    for(auto & i : order)
    {
        if(i == nullBtn)
        {
            if(digitalRead(button1) == LOW)
                i = A;
            else if(digitalRead(button2) == LOW)
                i = B;
            else if(digitalRead(button3) == LOW)
                i = C;
            else if(digitalRead(button4) == LOW)
                i = D;
            break;
        }
    }
}

void showOrder()
{
    if(digitalRead(nextButton) == LOW && orderIndex < 4 && order[orderIndex] != nullBtn)
    {
        for(int i = 0; i < 4; i++)
            digitalWrite(led1 + i, LOW);

        if(order[orderIndex] != nullBtn)
            digitalWrite(led1 + order[orderIndex], HIGH);

        orderIndex++;
    }
}

void setup()
{
    pinMode(button1, INPUT_PULLUP);
    pinMode(button2, INPUT_PULLUP);
    pinMode(button3, INPUT_PULLUP);
    pinMode(button4, INPUT_PULLUP);
    pinMode(resetButton, INPUT_PULLUP);
    pinMode(nextButton, INPUT_PULLUP);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    pinMode(resetLed, OUTPUT);
}

void loop()
{
    // reset
    if(digitalRead(resetButton) == LOW)
        return reset();

    digitalWrite(resetLed, LOW);

    // the first player that hits the button
    if(!buttonsPressed[0] && !buttonsPressed[1] && !buttonsPressed[2] && !buttonsPressed[3])
        checkOrder();


    // the order
    setOrder();
    showOrder();
}
