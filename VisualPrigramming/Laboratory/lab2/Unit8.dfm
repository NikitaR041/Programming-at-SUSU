object Form8: TForm8
  Left = 0
  Top = 0
  Caption = #1042#1099#1073#1086#1088' '#1094#1074#1077#1090#1072
  ClientHeight = 441
  ClientWidth = 880
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 272
    Top = 242
    Width = 49
    Height = 15
    Caption = #1050#1088#1072#1089#1085#1099#1081
  end
  object Label2: TLabel
    Left = 272
    Top = 290
    Width = 49
    Height = 15
    Caption = #1047#1077#1083#1077#1085#1099#1081
  end
  object Label3: TLabel
    Left = 272
    Top = 338
    Width = 36
    Height = 15
    Caption = #1057#1080#1085#1080#1081
  end
  object Label4: TLabel
    Left = 40
    Top = 66
    Width = 821
    Height = 96
    Caption = #1044#1077#1084#1086#1085#1089#1090#1088#1072#1094#1080#1103' '#1094#1074#1077#1090#1072
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -85
    Font.Name = 'Times New Roman '
    Font.Style = []
    ParentFont = False
  end
  object RedSB: TScrollBar
    Left = 408
    Top = 232
    Width = 249
    Height = 25
    Max = 255
    PageSize = 0
    TabOrder = 0
    OnChange = RedSBChange
  end
  object GreenSB: TScrollBar
    Left = 408
    Top = 280
    Width = 249
    Height = 25
    PageSize = 0
    TabOrder = 1
    OnChange = RedSBChange
  end
  object BlueSB: TScrollBar
    Left = 408
    Top = 328
    Width = 249
    Height = 25
    PageSize = 0
    TabOrder = 2
    OnChange = RedSBChange
  end
end
