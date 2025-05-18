import ctypes
import tkinter as tk
from tkinter import messagebox

# Load your DLL
calcdll = ctypes.CDLL(r'c:\Users\L K Subair\Documents\C_PROGRAMS\miniproj\caloriecalc.dll')

# Set function argument + return types
calcdll.calculateCalories.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_int, ctypes.c_char, ctypes.c_char_p, ctypes.c_char_p]
calcdll.calculateCalories.restype = ctypes.c_float

def calculate():
    try:
        weight = float(entry_weight.get())
        height = float(entry_height.get())
        age = int(entry_age.get())
        sex = entry_sex.get().encode()  # as bytes
        goal = entry_goal.get().encode()  # as bytes
        dietType = ctypes.create_string_buffer(50)

        # Call C function
        calories = calcdll.calculateCalories(weight, height, age, sex[0], goal, dietType)

        # Show result
        result_label.config(text=f"Calories: {calories:.2f}\nDiet Type: {dietType.value.decode()}")
    except Exception as e:
        messagebox.showerror("Error", f"Invalid input: {e}")

# GUI Setup
root = tk.Tk()
root.title("Calorie Calculator")

# Labels + Entries
tk.Label(root, text="Weight (kg):").grid(row=0, column=0)
entry_weight = tk.Entry(root)
entry_weight.grid(row=0, column=1)

tk.Label(root, text="Height (m):").grid(row=1, column=0)
entry_height = tk.Entry(root)
entry_height.grid(row=1, column=1)

tk.Label(root, text="Age:").grid(row=2, column=0)
entry_age = tk.Entry(root)
entry_age.grid(row=2, column=1)

tk.Label(root, text="Sex (M/F):").grid(row=3, column=0)
entry_sex = tk.Entry(root)
entry_sex.grid(row=3, column=1)

tk.Label(root, text="Goal (bulk/cut/maintain):").grid(row=4, column=0)
entry_goal = tk.Entry(root)
entry_goal.grid(row=4, column=1)

# Calculate Button
tk.Button(root, text="Calculate", command=calculate).grid(row=5, column=0, columnspan=2)

# Result Display
result_label = tk.Label(root, text="")
result_label.grid(row=6, column=0, columnspan=2)

root.mainloop()
