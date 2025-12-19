import sys
import tkinter as tk
from ui.login_window import LoginWindow

sys.stdout.reconfigure(encoding='utf-8')

def main():
    root = tk.Tk()
    LoginWindow(root)
    root.mainloop()

if __name__ == "__main__":
    main()
