const int max_button_cnt = 4;
const int password_cnt = 5;

int button_state[max_button_cnt];
int button_prev_state[max_button_cnt];
int password[password_cnt] = { 2, 1,3,2, 0};

int button_pin[max_button_cnt] = {4, 5, 6, 7};
int rele(12);
int led(13);

int val = 0;
int button_push_counter = 0;

void setup()
{
  pinMode(rele, OUTPUT);

  //int pinCount = 4;
  
  for (int thisPin = 0; thisPin < max_button_cnt; thisPin++)  
  {
    pinMode(button_pin[thisPin], INPUT_PULLUP);
  }

 digitalWrite(rele, LOW);
 reset(); 
 Serial.begin(9600);  
}

void loop()
{
  read();  
}


bool check_button(int index)
{    
  if (password[button_push_counter++] != index) return false;  

  digitalWrite(led, HIGH);    
  delay(20);
  digitalWrite(led, LOW);
  return true;  
}

void read()
{
  for (int i = 0; i < max_button_cnt; i++)
  {
    button_state[i] = digitalRead(button_pin[i]);
    if (button_state[i] == LOW && button_state[i] != button_prev_state[i])
    {
        delay(200);
        // it was just pressed
        if (check_button(i))
        {
          Serial.print(i);
          if(button_push_counter == password_cnt)
          {
            win();
            reset();
          }
        }
        else
        {
        if (i==password[0]){
          button_push_counter=1;
          return;
        }
          Serial.print(" wrong button pressed: "); 
          Serial.println(i);
          reset();
        }       
    }
    button_prev_state[i] = button_state[i];
  }
}

void win()
{
    Serial.print('\n');
    Serial.println("Correct combination!!!");
    digitalWrite(rele, HIGH);
    while(true);
    delay(2000);
    digitalWrite(rele, LOW);
    //val = 0;  
}

void reset()
{ 
  memset(button_prev_state, 0x00, password_cnt);
  button_push_counter = 0;  
}
