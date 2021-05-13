//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int x = -16;
int y = -9;

int horizontalMovementValue = -15;
int initialValueOfHorizontalMovement = -15;
int verticalMovementValue = -10;
int initialValueOfVerticalMovement = -10;



//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
   bMiddleLine->Height = background->Height;
   bMiddleLine->Left = background->Width/2;

   paddle1->Top = background->Height / 2 - paddle1->Height / 2;
   paddle2->Top = background->Height / 2 - paddle1->Height / 2;
   paddle2->Left = background->Width - 75;

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


  // loss of the ball by the first player - warunek trójargumentowy
  if(ball->Left < paddle1->Left)
  {
     //TimerBall->Enabled = false;
     //ball->Visible = false;

   //bounce the ball from the center of the paddle
   } else if (ball->Left <= paddle1->Left + paddle1->Width &&
              //ball->Top + ball->Height /2 == paddle1->Top + paddle1->Height / 2)
     ball->Top + ball->Height * 5 / 6 >= paddle1->Top + paddle1->Height / 2 &&
     ball->Top - ball->Height / 6 <= paddle1->Top + paddle1->Height / 2)
   {
     if (horizontalMovementValue < 0)
     {
        horizontalMovementValue = -initialValueOfHorizontalMovement * 2;
        verticalMovementValue = 0;
     }

   } else  if (ball->Left <= paddle1->Left + paddle1->Width &&
     ball->Top + ball->Height / 2 < paddle1->Top + paddle1->Height &&
     ball->Top + ball->Height / 2 > paddle1->Top)
   {
     if (horizontalMovementValue < 0)
     {
       if (ball->Top - ball->Height / 2 < paddle1->Top - paddle1->Height / 2)
       {
         horizontalMovementValue = -initialValueOfHorizontalMovement;
         verticalMovementValue = -initialValueOfVerticalMovement;
       }
       else
       {
         horizontalMovementValue = -initialValueOfHorizontalMovement;
         verticalMovementValue = initialValueOfVerticalMovement;
       }
     }

   } else if (ball->Left <= paddle1->Left + paddle1->Width &&
     ball->Top + 1 < paddle1->Top + paddle1->Height &&
     ball->Top + ball->Height - 1 > paddle1->Top)
   {
     if (horizontalMovementValue < 0)
     {
       if (ball->Top - ball->Height / 2 < paddle1->Top - paddle1->Height / 2)
       {
         horizontalMovementValue = -initialValueOfHorizontalMovement * 2;
         verticalMovementValue = -initialValueOfHorizontalMovement;
       }
       else
       {
        horizontalMovementValue = -initialValueOfHorizontalMovement * 2;
        verticalMovementValue = initialValueOfHorizontalMovement;
       }
     }
   }




  /*} else if (ball->Left <= paddle1->Left + paddle1->Width &&
    (ball->Top - ball->Height / 2 == paddle1->Top + paddle1->Height ||
     ball->Top - ball->Height / 2 == paddle1->Top))
  {
     if (x > 0)
     {
        x = -x;
        y +=5;
      }

   } else if (ball->Left <= paddle1->Left + paddle1->Width &&
     ball->Top - ball->Height / 2 == paddle1->Top + paddle1->Height / 2)
   {
     if (x > 0)
     {
        x = -x;
        y = 0;
      }
    } else //if (ball->Left <= paddle1->Left + paddle1->Width &&
    // ball->Top - ball->Height / 2 < paddle1->Top + paddle1->Height &&
     //ball->Top - ball->Height / 2 > paddle1->Top)
   {
     if (x > 0)
     {
        x = -x;
      }
   } */
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedTimeTimerTimer(TObject *Sender)
{
   if(TimerBall->Interval > 1) TimerBall->Interval -= 1;
}
//---------------------------------------------------------------------------



