object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'GameCheckers'
  ClientHeight = 802
  ClientWidth = 944
  Color = clBisque
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clInfoBk
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Position = poScreenCenter
  Visible = True
  OnCreate = FormCreate
  OnResize = FormResize
  TextHeight = 15
  object DrawGrid1: TDrawGrid
    Left = 112
    Top = 80
    Width = 651
    Height = 651
    ColCount = 8
    DefaultColWidth = 80
    DefaultRowHeight = 80
    FixedCols = 0
    RowCount = 8
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 0
    OnDrawCell = DrawGrid1DrawCell
    OnMouseDown = DrawGrid1MouseDown
  end
end
