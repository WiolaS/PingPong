//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TShape *background;
        TShape *bLeftLine;
        TShape *bTopLine;
        TShape *bRightLine;
        TShape *bBottomLine;
        TShape *bMiddleLine;
        TImage *paddle1;
        TImage *paddle2;
        TTimer *up1;
        TTimer *down1;
        TTimer *up2;
        TTimer *down2;
        TTimer *TimerBall;
        TTimer *SpeedTimeTimer;
        TImage *ball;
        TLabel *Label1;
        TButton *Button1;
        TLabel *punctation;
        TLabel *Bounces;
        TButton *Button2;
        TTimer *Countdown;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall up1Timer(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall up2Timer(TObject *Sender);
        void __fastcall down2Timer(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall down1Timer(TObject *Sender);
        void __fastcall TimerBallTimer(TObject *Sender);
        void __fastcall SpeedTimeTimerTimer(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall CountdownTimer(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
