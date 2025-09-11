object Form10: TForm10
  Left = 0
  Top = 0
  Caption = #1059#1087#1088#1072#1074#1083#1077#1085#1080#1077' '#1096#1088#1080#1092#1090#1086#1084', '#1088#1072#1079#1084#1077#1088#1086#1084' '#1080' '#1094#1074#1077#1090#1086#1084' '
  ClientHeight = 441
  ClientWidth = 624
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Label1: TLabel
    Left = 72
    Top = 56
    Width = 487
    Height = 113
    Caption = #1042#1089#1077#1084' '#1087#1088#1080#1074#1077#1090
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -85
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
  end
  object FontRG: TRadioGroup
    Left = 8
    Top = 208
    Width = 185
    Height = 121
    Caption = #1064#1088#1080#1092#1090
    Items.Strings = (
      'Arial '
      'Courier '
      'Times New Roman ')
    TabOrder = 0
    OnClick = FontRGClick
  end
  object SizeRG: TRadioGroup
    Left = 216
    Top = 208
    Width = 193
    Height = 121
    Caption = #1056#1072#1079#1084#1077#1088
    Columns = 2
    Items.Strings = (
      '8'
      '10'
      '12'
      '16'
      '20'
      '24'
      '32'
      '64')
    TabOrder = 1
    OnClick = SizeRGClick
  end
  object ColorRG: TRadioGroup
    Left = 423
    Top = 208
    Width = 185
    Height = 121
    Caption = #1062#1074#1077#1090
    Columns = 2
    Items.Strings = (
      #1063#1077#1088#1085#1099#1081' '
      #1041#1077#1083#1099#1081' '
      #1050#1088#1072#1089#1085#1099#1081' '
      #1047#1077#1083#1077#1085#1099#1081' '
      #1057#1080#1085#1080#1081' '
      #1046#1077#1083#1090#1099#1081)
    TabOrder = 2
    OnClick = ColorRGClick
  end
end
