object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Games Magic'
  ClientHeight = 463
  ClientWidth = 390
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'Comic Sans MS'
  Font.Style = []
  Position = poDesktopCenter
  TextHeight = 18
  object Label1: TLabel
    Left = 24
    Top = 56
    Width = 89
    Height = 18
    Caption = 'Click Button'
  end
  object shpCircle: TShape
    Left = 144
    Top = 377
    Width = 40
    Height = 40
    Brush.Color = clYellow
    Shape = stEllipse
  end
  object btnUp: TBitBtn
    Left = 24
    Top = 88
    Width = 75
    Height = 25
    Caption = 'UP'
    TabOrder = 0
    OnClick = btnUpClick
  end
  object btnDown: TBitBtn
    Left = 24
    Top = 128
    Width = 75
    Height = 25
    Caption = 'DOWN'
    Enabled = False
    TabOrder = 1
    OnClick = btnDownClick
  end
  object BitBtn3: TBitBtn
    Left = 24
    Top = 392
    Width = 75
    Height = 25
    Kind = bkClose
    NumGlyphs = 2
    TabOrder = 2
  end
end
