# gui.py
from qtpy import QtWidgets, QtCore, QtGui
from model import BinaryImage
from formats import save_rle, load_rle
import numpy as np




class PixelView(QtWidgets.QWidget):
    """
    Виджет для отрисовки бинарного изображения с возможностью масштабирования по целым кратным.
    """
    def __init__(self, model: BinaryImage, pixel_size=1, editable=False):
        super().__init__()
        self.model = model
        self.pixel_size = pixel_size # сколько пикселей на 1 "квадрат" в реальном отображении
        self.editable = editable
        self.setMouseTracking(True)
        self._mouse_pressed = False
        self.brush = 1 # 1 = draw black(1), 0 = erase(0)
        model.changed.connect(self.update)
        self.setMinimumSize(200, 200)


    def sizeHint(self):
        return QtCore.QSize(self.model.width * self.pixel_size, self.model.height * self.pixel_size)


    def paintEvent(self, event):
        painter = QtGui.QPainter(self)
        w, h = self.model.width, self.model.height
        ps = self.pixel_size
        for y in range(h):
            for x in range(w):
                v = self.model.pixels[y, x]
                color = QtGui.QColor(0, 0, 0) if v == 1 else QtGui.QColor(255, 255, 255)
                painter.fillRect(x*ps, y*ps, ps, ps, color)
        # grid
        painter.setPen(QtGui.QPen(QtGui.QColor(200,200,200), 0))
        for x in range(w+1):
            painter.drawLine(x*ps, 0, x*ps, h*ps)
        for y in range(h+1):
            painter.drawLine(0, y*ps, w*ps, y*ps)


    def mousePressEvent(self, ev):
        if not self.editable:
            return
        self._mouse_pressed = True
        x = int(ev.x() / self.pixel_size)
        y = int(ev.y() / self.pixel_size)
        self.model.set_pixel(x, y, self.brush)

    def mouseMoveEvent(self, ev):
        if not self.editable or not self._mouse_pressed:
            return
        x = int(ev.x() / self.pixel_size)
        y = int(ev.y() / self.pixel_size)
        self.model.set_pixel(x, y, self.brush)


    def mouseReleaseEvent(self, ev):
        self._mouse_pressed = False    


class MainWindow(QtWidgets.QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('Binary Image Editor')
        self.model = BinaryImage(64, 64)


        # central widget
        central = QtWidgets.QWidget()
        self.setCentralWidget(central)
        layout = QtWidgets.QHBoxLayout(central)

        left_vbox = QtWidgets.QVBoxLayout()
        right_vbox = QtWidgets.QVBoxLayout()


        # Left: real-size view (editable)
        self.real_view = PixelView(self.model, pixel_size=8, editable=True)
        left_vbox.addWidget(QtWidgets.QLabel('Редактирование (увеличено)'))
        left_vbox.addWidget(self.real_view)


        # Right: overview at 1:1 (smaller pixel size)
        self.overview = PixelView(self.model, pixel_size=1, editable=False)
        right_vbox.addWidget(QtWidgets.QLabel('Обзор (1:1)'))
        right_vbox.addWidget(self.overview)


        layout.addLayout(left_vbox)
        layout.addLayout(right_vbox)


        # Toolbar
        toolbar = QtWidgets.QToolBar()
        self.addToolBar(toolbar)

        brush_act = QtWidgets.QAction('Кисть', self)
        brush_act.triggered.connect(lambda: self.set_brush(1))
        eraser_act = QtWidgets.QAction('Ластик', self)
        eraser_act.triggered.connect(lambda: self.set_brush(0))
        fill_act = QtWidgets.QAction('Заливка', self)
        fill_act.triggered.connect(self.fill_dialog)
        invert_act = QtWidgets.QAction('Инвертировать', self)
        invert_act.triggered.connect(self.model.invert)


        save_act = QtWidgets.QAction('Сохранить .rle', self)
        save_act.triggered.connect(self.save_rle)
        load_act = QtWidgets.QAction('Загрузить .rle', self)
        load_act.triggered.connect(self.load_rle)
        export_act = QtWidgets.QAction('Экспорт PNG', self)
        export_act.triggered.connect(self.export_png)

        toolbar.addAction(brush_act)
        toolbar.addAction(eraser_act)
        toolbar.addAction(fill_act)
        toolbar.addAction(invert_act)
        toolbar.addSeparator()
        toolbar.addAction(save_act)
        toolbar.addAction(load_act)
        toolbar.addAction(export_act)


        # status
        self.status = self.statusBar()
        self.set_brush(1)

    def set_brush(self, val):
        self.real_view.brush = val
        self.status.showMessage(f'Текущий инструмент: {"Кисть" if val==1 else "Ластик"}')


    def fill_dialog(self):
        # простая реализация: просим координаты
        x, ok = QtWidgets.QInputDialog.getInt(self, 'Z', 'X:')
        if not ok:
            return
        y, ok = QtWidgets.QInputDialog.getInt(self, 'Z', 'Y:')
        if not ok:
            return
        # выбираем что заливать
        choice = QtWidgets.QMessageBox.question(self, 'Заливка', 'Залить черным? (Да — черный, Нет — белый)')
        val = 1 if choice == QtWidgets.QMessageBox.StandardButton.Yes else 0
        self.model.flood_fill(x, y, val)