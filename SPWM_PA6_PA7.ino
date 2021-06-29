double arrayy[72];
double alpha=0, sineval=0.0;
int St=0;
unsigned long prev=0;

void setup() 
{
  RCC_BASE->APB2ENR |= (1<<2); // Enable clock to Port A
  GPIOA_BASE->CRL |= ((1<<24)|(1<<25)|(1<<27)|(1<<28)|(1<<29)|(1<<31));
  GPIOA_BASE->CRL &= ~((1<<26)|(1<<30));
  GPIOB_BASE->CRL |= (1<<23);
  GPIOB_BASE->CRL &= ~((1<<22)|(1<<21)|(1<<20));
  GPIOB_BASE->ODR &= ~(1<<5);
  TIMER3_BASE->CR1 = (1|(1<<5)|(1<<6));
  TIMER3_BASE->CR2 = 0;
  TIMER3_BASE->SMCR = 0;
  TIMER3_BASE->DIER = 0;
  TIMER3_BASE->EGR = 0;
  TIMER3_BASE->CCMR1 |=((1<<11)|(1<<13)|(1<<14)|(1<<3)|(1<<5)|(1<<6)|(1<<12));
  TIMER3_BASE->CCMR1 &= ~(1<<4); 
  TIMER3_BASE->CCMR2 = 0;
  TIMER3_BASE->CCER = (1|(1<<4));
  TIMER3_BASE->PSC = 71;
  TIMER3_BASE->ARR = 200;
  TIMER3_BASE->DCR = 0;
  TIMER3_BASE->CNT = 0;
  TIMER3_BASE->CCR1 = 100;
  TIMER3_BASE->CCR2 = 100;
  for(int i=0;i<72;i++)
  {
    arrayy[i]= sin(alpha*PI/180);
    alpha +=5;
  }
Serial.begin(115200);
}

void loop() 
{
  SandH(278);
  if (St==72)
   St =0;
   
   sineval = (int)((arrayy[St]*100)+100);
  TIMER3_BASE->CCR1 =sineval;
  TIMER3_BASE->CCR2 = sineval;
 }

void SandH (int t)
{
  if (micros()-prev >= t)
  {
    St +=1;
    prev = micros();
  }
}
