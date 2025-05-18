import tkinter as tk
from tkinter import messagebox
import ctypes

# Load your DLL
calcdll = ctypes.CDLL('c:\\Users\\L K Subair\\Documents\\C_PROGRAMS\\miniproj\\caloriecalc.dll')
calcdll.calculateCalories.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_int, ctypes.c_char, ctypes.c_char_p, ctypes.c_char_p]
calcdll.calculateCalories.restype = ctypes.c_float

# GUI Window
window = tk.Tk()
window.title("Diet Planner")
window.geometry("400x600")

# User Info Entries
tk.Label(window, text="Height (m)").pack()
height_entry = tk.Entry(window)
height_entry.pack()

tk.Label(window, text="Weight (kg)").pack()
weight_entry = tk.Entry(window)
weight_entry.pack()

tk.Label(window, text="Age").pack()
age_entry = tk.Entry(window)
age_entry.pack()

# Sex Selection
sex_var = tk.StringVar(value="M")
tk.Label(window, text="Sex").pack()
tk.Radiobutton(window, text="Male", variable=sex_var, value="M").pack()
tk.Radiobutton(window, text="Female", variable=sex_var, value="F").pack()

# Fitness Goal
goal_var = tk.StringVar(value="bulk")
tk.Label(window, text="Fitness Goal").pack()
tk.Radiobutton(window, text="Bulk", variable=goal_var, value="bulk").pack()
tk.Radiobutton(window, text="Cut", variable=goal_var, value="cut").pack()
tk.Radiobutton(window, text="Maintain", variable=goal_var, value="maintain").pack()

# Ingredients List
ingredient_list = []

def add_ingredient():
    item = ingredient_entry.get()
    if item:
        ingredient_list.append(item)
        ingredients_listbox.insert(tk.END, item)
        ingredient_entry.delete(0, tk.END)

tk.Label(window, text="Available Ingredients").pack()
ingredient_entry = tk.Entry(window)
ingredient_entry.pack()
tk.Button(window, text="Add Ingredient", command=add_ingredient).pack()
ingredients_listbox = tk.Listbox(window)
ingredients_listbox.pack()

# Output Labels
calories_label = tk.Label(window, text="Calories: ")
calories_label.pack()
diettype_label = tk.Label(window, text="Diet Type: ")
diettype_label.pack()

# Calculate Calories Function
def calculate():
    try:
        weight = float(weight_entry.get())
        height = float(height_entry.get())
        age = int(age_entry.get())
        sex = sex_var.get().encode('utf-8')
        goal = goal_var.get().encode('utf-8')
        dietType = ctypes.create_string_buffer(50)
        
        calories = calcdll.calculateCalories(weight, height, age, sex, goal, dietType)
        calories_label.config(text=f"Calories: {calories:.2f}")
        diettype_label.config(text=f"Diet Type: {dietType.value.decode()}")
    except Exception as e:
        messagebox.showerror("Error", f"Invalid input or error: {e}")

# Calculate Button
tk.Button(window, text="Calculate Calories", command=calculate).pack(pady=10)

# Exit Button
tk.Button(window, text="Exit", command=window.quit).pack(pady=10)

# Run the GUI loop
window.mainloop()
