unit Game_u;

interface

uses
  Winapi.Windows, Winapi.Messages, System.SysUtils, System.Variants, System.Classes, Vcl.Graphics,
  Vcl.Controls, Vcl.Forms, Vcl.Dialogs, Vcl.ExtCtrls, Vcl.StdCtrls, Vcl.Buttons;

type
  TForm1 = class(TForm)
    btnUp: TBitBtn;
    btnDown: TBitBtn;
    BitBtn3: TBitBtn;
    Label1: TLabel;
    shpCircle: TShape;
    procedure btnUpClick(Sender: TObject);
    procedure btnDownClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

procedure TForm1.btnDownClick(Sender: TObject);
begin
  shpCircle.Top := 377;
  btnUp.Enabled := true;
  btnDown.Enabled := false;
end;

procedure TForm1.btnUpClick(Sender: TObject);
begin
  shpCircle.Top := 73;
  btnUp.Enabled := false;
  btnDown.Enabled := true;
end;

end.
