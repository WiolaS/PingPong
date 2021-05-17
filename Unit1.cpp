//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int horizontalMovementValue = -15;
int initialValueOfHorizontalMovement = -15;
int verticalMovementValue = -10;
int initialValueOfVerticalMovement = -10;
int numberOfLeftPlayerWins = 0;
int numberOfRightPlayerWins = 0;
int numberOfRounds = 0;
int numberOfBounces = 0;
int startingTime = 5;

void showLabels (TLabel *Label1, TLabel *punctation, TLabel *Bounces, TButton *Button1, TButton *Button2)
{
   punctation->Caption = IntToStr(numberOfLeftPlayerWins) + ":" + IntToStr(numberOfRightPlayerWins);
   Bounces->Caption = "Ilosc odbic: " + IntToStr(numberOfBounces);

   Label1->Visible = true;
   Button1->Visible = true;
   Button2->Visible = true;
   punctation->Visible = true;
   Bounces->Visible = true;
}

void bounceTheBallWithTheLeftPaddle (TTimer *TimerBall, TImage *ball, TImage *paddle1, TLabel *Label1, TLabel *punctation, TLabel *Bounces, TButton *Button1, TButton *Button2)
{
  // loss of the ball by the left player
  if(ball->Left < paddle1->Left)
  {
     sndPlaySound("sound/applause.wav", SND_ASYNC);
     TimerBall->Enabled = false;
     ball->Visible = false;
     numberOfRightPlayerWins++;
     showLabels (Label1, punctation, Bounces, Button1, Button2);

   //bounce the ball from the center of the paddle (+- 1/4 of the ball height)
   } else if (ball->Left <= paddle1->Left + paddle1->Width &&
              ball->Top >= paddle1->Top + paddle1->Height / 2 - ball->Height *3/4 &&
              ball->Top <= paddle1->Top + paddle1->Height / 2 - ball->Height /4)
   {
     if (horizontalMovementValue < 0)
     {
        sndPlaySound("sound/pingpong.wav", SND_ASYNC);
        horizontalMovementValue = -initialValueOfHorizontalMovement * 2;
        verticalMovementValue = 0;
        numberOfBounces++;
     }

   //standard bounce the ball from the paddle
   } else  if (ball->Left <= paddle1->Left + paddle1->Width &&
     ball->Top < paddle1->Top + paddle1->Height - ball->Height / 2 &&
     ball->Top > paddle1->Top - ball->Height / 2)
   {
     if (horizontalMovementValue < 0)
     {
       if (ball->Top < paddle1->Top + paddle1->Height / 2 - ball->Height / 2)
       {
         sndPlaySound("sound/pingpong.wav", SND_ASYNC);
         horizontalMovementValue = -initialValueOfHorizontalMovement;
         verticalMovementValue = -initialValueOfVerticalMovement;
         numberOfBounces++;
       }
       else
       {
         sndPlaySound("sound/pingpong.wav", SND_ASYNC);
         horizontalMovementValue = -initialValueOfHorizontalMovement;
         verticalMovementValue = initialValueOfVerticalMovement;
         numberOfBounces++;
       }
     }
   //bounce a ball at the ends of a paddle
   } else if (ball->Left <= paddle1->Left + paddle1->Width &&
     ball->Top <= paddle1->Top + paddle1->Height - 1 &&
     ball->Top >= paddle1->Top - ball->Height + 1)
   {
     if (horizontalMovementValue < 0)
     {
       if (ball->Top < paddle1->Top + paddle1->Height / 2 - ball->Height / 2)
       {
         sndPlaySound("sound/pingpong.wav", SND_ASYNC);
         horizontalMovementValue = -initialValueOfHorizontalMovement * 2;
         verticalMovementValue = -initialValueOfHorizontalMovement;
         numberOfBounces++;
       }
       else
       {
        sndPlaySound("sound/pingpong.wav", SND_ASYNC);
        horizontalMovementValue = -initialValueOfHorizontalMovement * 2;
        verticalMovementValue = initialValueOfHorizontalMovement;
        numberOfBounces++;
       }
     }
   }
}

void bounceTheBallWithTheRightPaddle (TTimer *TimerBall, TImage *ball, TImage *paddle2, TLabel *Label1, TLabel *punctation, TLabel *Bounces, TButton *Button1, TButton *Button2)
{
  // loss of the ball by the right player
  if(ball->Left > paddle2->Left + paddle2->Width)
  {
      sndPlaySound("sound/applause.wav", SND_ASYNC);
     TimerBall->Enabled = false;
     ball->Visible = false;
     numberOfLeftPlayerWins++;
     showLabels (Label1, punctation, Bounces, Button1, Button2);

   //bounce the ball from the center of the paddle (+- 1/4 of the ball height)
   } else if (ball->Left >= paddle2->Left - ball->Width &&
              ball->Top >= paddle2->Top + paddle2->Height / 2 - ball->Height *3/4 &&
              ball->Top <= paddle2->Top + paddle2->Height / 2 - ball->Height /4)
   {
     if (horizontalMovementValue > 0)
     {
        sndPlaySound("sound/pingpong.wav", SND_ASYNC);
        horizontalMovementValue = initialValueOfHorizontalMovement * 2;
        verticalMovementValue = 0;
        numberOfBounces++;

     }

   //standard bounce the ball from the paddle
   } else  if (ball->Left >= paddle2->Left - ball->Width &&
     ball->Top < paddle2->Top + paddle2->Height - ball->Height / 2 &&
     ball->Top > paddle2->Top - ball->Height / 2)
   {
     if (horizontalMovementValue > 0)
     {
       if (ball->Top < paddle2->Top + paddle2->Height / 2 - ball->Height / 2)
       {
         sndPlaySound("sound/pingpong.wav", SND_ASYNC);
         horizontalMovementValue = initialValueOfHorizontalMovement;
         verticalMovementValue = -initialValueOfVerticalMovement;
         numberOfBounces++;
       }
       else
       {
         sndPlaySound("sound/pingpong.wav", SND_ASYNC);
         horizontalMovementValue = initialValueOfHorizontalMovement;
         verticalMovementValue = initialValueOfVerticalMovement;
         numberOfBounces++;
       }
     }
   //bounce a ball at the ends of a paddle
   } else if (ball->Left >= paddle2->Left - ball->Width &&
     ball->Top <= paddle2->Top + paddle2->Height - 1 &&
     ball->Top >= paddle2->Top - ball->Height + 1)
   {
     if (horizontalMovementValue > 0)
     {
       if (ball->Top < paddle2->Top + paddle2->Height / 2 - ball->Height / 2)
       {
         sndPlaySound("sound/pingpong.wav", SND_ASYNC);
         horizontalMovementValue = initialValueOfHorizontalMovement * 2;
         verticalMovementValue = -initialValueOfHorizontalMovement;
         numberOfBounces++;
       }
       else
       {
        sndPlaySound("sound/pingpong.wavzz", SND_ASYNC);
        horizontalMovementValue = initialValueOfHorizontalMovement * 2;
        verticalMovementValue = initialValueOfHorizontalMovement;
        numberOfBounces++;
       }
     }
   }
}




//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   bMiddleLine->Height = background->Height;
   bMiddleLine->Left = (background->Width + bLeftLine->Width *2) /2 - bMiddleLine->Width /2;
   ball->Left = (background->Width + bLeftLine->Width *2) /2 - ball->Width /2;
   ball->Visible = true;
   punctation->Left = (background->Width + bLeftLine->Width *2) /2 - punctation->Width /2;
   Button2->Left = (background->Width + bLeftLine->Width *2) /2 - Button2->Width /2;
   Bounces->Left = (background->Width + bLeftLine->Width *2) /2 - Bounces->Width /2;

   paddle1->Top = background->Height / 2 - paddle1->Height / 2;
   paddle1->Left = 70;
   paddle2->Top = background->Height / 2 - paddle1->Height / 2;
   paddle2->Left = background->Width - 70 + bRightLine->Width;

   Label1->Left = (background->Width + bLeftLine->Width *2) /2 - Label1->Width /2;
   Button1->Left = (background->Width + bLeftLine->Width *2) /2 - Button1->Width /2 ;

   punctation->Visible = false;
   Button2->Visible = false;
   Bounces->Visible = false;
   Countdown->Enabled = false;
   SpeedTimeTimer->Enabled = true;

   Label1->Caption = "Zagrajmy w Ping Ponga!";


}
//---------------------------------------------------------------------------
void __fastcall TForm1::up1Timer(TObject *Sender)
{
   if(paddle1->Top >= 20)paddle1->Top -=5;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::down1Timer(TObject *Sender)
{
   if(paddle1->Top + paddle1->Height <= background->Height) paddle1->Top += 5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::up2Timer(TObject *Sender)
{
   if(paddle2->Top >= 20) paddle2->Top -=5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::down2Timer(TObject *Sender)
{
  if(paddle2->Top + paddle2->Height <= background->Height) paddle2->Top +=5;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if(Key == 0x41) up1->Enabled = true;
   if(Key == 0x5A) down1->Enabled = true;
   if(Key == VK_UP) up2->Enabled = true;
   if(Key == VK_DOWN) down2->Enabled = true;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
   if(Key == 0x41) up1->Enabled = false;
   if(Key == 0x5A) down1->Enabled = false;
   if(Key == VK_UP) up2->Enabled = false;
   if(Key == VK_DOWN) down2->Enabled = false;
}
//---------------------------------------------------------------------------



void __fastcall TForm1::TimerBallTimer(TObject *Sender)
{
   ball->Left += horizontalMovementValue;
   ball->Top += verticalMovementValue;


   // bounce the ball off the top wall
   if (ball->Top <= background->Top) verticalMovementValue = -verticalMovementValue;

   // bounce the ball off the bottom wall
   if(ball->Top + ball->Height >= background->Height + bBottomLine->Height) verticalMovementValue = -verticalMovementValue;

   // Test bounce the ball off the left wall
  if(ball->Left <= background->Left) horizontalMovementValue = -horizontalMovementValue;

   // Test bounce the ball off the right wall
  if(ball->Left + ball->Width >= background->Width - bRightLine->Width) horizontalMovementValue = -horizontalMovementValue;

  bounceTheBallWithTheLeftPaddle (TimerBall, ball, paddle1, Label1, punctation, Bounces, Button1, Button2);
  bounceTheBallWithTheRightPaddle (TimerBall, ball, paddle2, Label1, punctation, Bounces, Button1, Button2);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedTimeTimerTimer(TObject *Sender)
{
   if(TimerBall->Interval > 1) TimerBall->Interval -= 1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
  startingTime = 5;
  sndPlaySound("sound/gong.wav", SND_ASYNC);
  Countdown->Enabled = true;
  CountdownTimer(Sender);
  //Application->ProcessMessages(); Sleep(5000);
  //FormCreate(Sender);

  numberOfLeftPlayerWins = 0;
  numberOfRightPlayerWins = 0;
  numberOfRounds = 0;
  numberOfBounces = 0;
  //Label1->Visible = false;
  Button1->Visible = false;

  TimerBall->Enabled = true;
  TimerBallTimer(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
  startingTime = 5;
  sndPlaySound("sound/gong.wav", SND_ASYNC);
  Countdown->Enabled = true;
  CountdownTimer(Sender);
  //Application->ProcessMessages(); Sleep(5000);
  //FormCreate(Sender);

  numberOfBounces = 0;
  //Label1->Visible = false;
  Button1->Visible = false;
  TimerBall->Enabled = true;
  TimerBallTimer(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CountdownTimer(TObject *Sender)
{
    startingTime--;
    Label1->Caption = IntToStr(startingTime);
    //Application->ProcessMessages(); Sleep(1000);

   if(startingTime <= 1)
   {
     Label1->Caption = "START!";
     Countdown->Enabled = false;
   }
}
//---------------------------------------------------------------------------

