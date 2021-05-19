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
int startingTime = 3;
int spareSpace = 0;

void showLabels ()
{
   Form1->punctation->Caption = "|" + IntToStr(numberOfLeftPlayerWins) + ":" + IntToStr(numberOfRightPlayerWins) + "|";
   Form1->Bounces->Caption = "~> Ilosc odbic: " + IntToStr(numberOfBounces);

   Form1->Label1->Visible = true;
   Form1->Button1->Visible = true;
   Form1->Button2->Visible = true;
   Form1->punctation->Visible = true;
   Form1->Bounces->Visible = true;
}

void bounceTheBallWithTheLeftPaddle (TImage *ball, TImage *paddle1)
{
  if (horizontalMovementValue >= -15) spareSpace = 5;
  else if (horizontalMovementValue >= -30) spareSpace = 20;

  // loss of the ball by the left player
  if(ball->Left < paddle1->Left)
  {
     sndPlaySound("sound/applause.wav", SND_ASYNC);
     Form1->TimerBall->Enabled = false;
     ball->Visible = false;
     numberOfRightPlayerWins++;
     Form1->Label1->Caption = "~> Punkt dla prawego gracza >";
     showLabels ();

   //bounce the ball from the center of the paddle (+- 1/4 of the ball height)
   } else if (ball->Left <= paddle1->Left + paddle1->Width + spareSpace &&
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
   } else  if (ball->Left <= paddle1->Left + paddle1->Width + spareSpace &&
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
   } else if (ball->Left <= paddle1->Left + paddle1->Width + spareSpace &&
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

void bounceTheBallWithTheRightPaddle (TImage *ball, TImage *paddle2)
{
  if (horizontalMovementValue >= -15) spareSpace = 5;
  else if (horizontalMovementValue >= -30) spareSpace = 20;

  // loss of the ball by the right player
  if(ball->Left > paddle2->Left + paddle2->Width)
  {
     sndPlaySound("sound/applause.wav", SND_ASYNC);
     Form1->TimerBall->Enabled = false;
     ball->Visible = false;
     numberOfLeftPlayerWins++;
     Form1->Label1->Caption = "<~ Punkt dla lewego gracza";
     showLabels ();

   //bounce the ball from the center of the paddle (+- 1/4 of the ball height)
   } else if (ball->Left >= paddle2->Left - ball->Width - spareSpace &&
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
   } else  if (ball->Left >= paddle2->Left - ball->Width - spareSpace &&
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
   } else if (ball->Left >= paddle2->Left - ball->Width - spareSpace &&
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
        sndPlaySound("sound/pingpong.wav", SND_ASYNC);
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
   ball->Top = (background->Height + bTopLine->Height *2) /2 - ball->Height /2;
   horizontalMovementValue = -15;
   verticalMovementValue = -10;

   Label1->Caption = "~> Zagrajmy w Ping Ponga! <~";

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
   if (ball->Top <= background->Top)
   {
     verticalMovementValue = -verticalMovementValue;
     sndPlaySound("sound/pingpong.wav", SND_ASYNC);
   }

   // bounce the ball off the bottom wall
   if(ball->Top + ball->Height >= background->Height + bBottomLine->Height)
   {
     verticalMovementValue = -verticalMovementValue;
     sndPlaySound("sound/pingpong.wav", SND_ASYNC);
   }  

   // Test bounce the ball off the left wall
  if(ball->Left <= background->Left) horizontalMovementValue = -horizontalMovementValue;

   // Test bounce the ball off the right wall
  if(ball->Left + ball->Width >= background->Width - bRightLine->Width) horizontalMovementValue = -horizontalMovementValue;

  bounceTheBallWithTheLeftPaddle (ball, paddle1);
  bounceTheBallWithTheRightPaddle (ball, paddle2);

}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedTimeTimerTimer(TObject *Sender)
{
   if(TimerBall->Interval > 1) TimerBall->Interval -= 1;
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
  startingTime = 3;
  sndPlaySound("sound/gong.wav", SND_ASYNC);
  Countdown->Enabled = true;
  CountdownTimer(Sender);

  numberOfLeftPlayerWins = 0;
  numberOfRightPlayerWins = 0;
  numberOfRounds = 0;
  numberOfBounces = 0;
  Label1->Visible = false;
  Button1->Visible = false;

}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button2Click(TObject *Sender)
{
  startingTime = 3;
  sndPlaySound("sound/gong.wav", SND_ASYNC);
  Countdown->Enabled = true;
  CountdownTimer(Sender);

  numberOfBounces = 0;
  Label1->Visible = false;
  Button1->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CountdownTimer(TObject *Sender)
{
    punctation->Visible = true;
    Label1->Visible = false;
    Bounces->Visible = false;
    Button2->Visible = false;
    Button1->Visible = false;
    punctation->Caption = "~" + IntToStr(startingTime) + "~";

   if(startingTime < 1)
   {
     punctation->Caption = "START!";
     Application->ProcessMessages(); Sleep(1000);
     Countdown->Enabled = false;

     TimerBall->Interval = 40;
     TimerBall->Enabled = true;
     FormCreate(Sender);
     TimerBallTimer(Sender);
   }
   startingTime--;
}
//---------------------------------------------------------------------------







