import ctypes
from ctypes import c_int, c_char_p, c_char, create_string_buffer
import tkinter as tk
from tkinter import messagebox
import os, sys

# Load DLL
dietdll = ctypes.CDLL(r'miniproj\dietplanner.dll')

# Function prototypes
dietdll.loadSampleRecipes.restype = None

# Calorie calculator prototype
dietdll.calculateCalories.argtypes = [
    ctypes.c_float, ctypes.c_float, c_int, c_char, c_char_p, ctypes.c_char_p
]
dietdll.calculateCalories.restype = ctypes.c_float

# Recipe suggestion prototype
dietdll.suggestRecipes.argtypes = [
    c_char_p, (ctypes.c_char * 50) * 20, c_int, ctypes.c_char_p
]
dietdll.suggestRecipes.restype = None

# Capture C stdout
def capture_c_output(func, *args):
    r, w = os.pipe()
    os.dup2(w, 1)
    func(*args)
    os.close(w)
    os.dup2(sys.__stdout__.fileno(), 1)
    output = os.read(r, 10000).decode()
    os.close(r)
    return output

# Main action function
def get_plan():
    try:
        weight = float(weight_entry.get())
        height = float(height_entry.get())
        age = int(age_entry.get())
        sex = sex_entry.get().upper()
        goal = goal_entry.get()
        ingredients_input = ingredients_entry.get()
        allergy_input = allergy_entry.get()

        if sex not in ('M', 'F'):
            messagebox.showerror("Input Error", "Sex must be 'M' or 'F'")
            return

        # Prepare dietary type string
        diet_type = ""
        if halal_var.get(): diet_type += "halal_"
        if veg_var.get(): diet_type += "vegetarian_"
        if vegan_var.get(): diet_type += "vegan_"
        if jain_var.get(): diet_type += "jain_"
        diet_type += goal

        outDietType = create_string_buffer(50)

        # Call calorie calculator
        calories = dietdll.calculateCalories(
            weight, height, age, sex.encode(), goal.encode(), outDietType
        )

        finalDietType = outDietType.value.decode()

        # Prepare ingredients array
        ingredients_list = [i.strip() for i in ingredients_input.split(",") if i.strip()]
        ingredient_array = ((ctypes.c_char * 50) * 20)()
        for idx, item in enumerate(ingredients_list):
            ingredient_array[idx].value = item.encode()

        # Build resultBuffer
        resultBuffer = create_string_buffer(5000)

        # Load sample recipes
        dietdll.loadSampleRecipes()

        # Call recipe suggestion
        capture_c_output(
            dietdll.suggestRecipes,
            finalDietType.encode(),
            ingredient_array, len(ingredients_list),
            resultBuffer
        )

        # Display results
        result_text.delete(1.0, tk.END)
        result_text.insert(tk.END, f"Calories: {calories:.2f} kcal\n\n")
        result_text.insert(tk.END, "Recipe Suggestions:\n")
        result_text.insert(tk.END, resultBuffer.value.decode())

    except Exception as e:
        messagebox.showerror("Error", str(e))

# GUI setup
root = tk.Tk()
root.title("Diet Planner")

# Input fields
fields = ["Weight (kg)", "Height (m)", "Age", "Sex (M/F)", "Goal (bulk/cut/maintain)",
           "Ingredients (comma-separated)", "Allergies (comma-separated)"]

entries = []
for field in fields:
    tk.Label(root, text=field).pack()
    entry = tk.Entry(root, width=40)
    entry.pack()
    entries.append(entry)

weight_entry, height_entry, age_entry, sex_entry, goal_entry, ingredients_entry, allergy_entry = entries

# Dietary restrictions checkboxes
halal_var = tk.IntVar()
veg_var = tk.IntVar()
vegan_var = tk.IntVar()
jain_var = tk.IntVar()

frame = tk.Frame(root)
frame.pack(pady=5)

for label, var in [("Halal", halal_var), ("Vegetarian", veg_var), ("Vegan", vegan_var), ("Jain", jain_var)]:
    tk.Checkbutton(frame, text=label, variable=var).pack(side=tk.LEFT, padx=5)

# Action button
tk.Button(root, text="Get Plan", command=get_plan, bg="#5cb85c", fg="white").pack(pady=10)

# Result box
result_text = tk.Text(root, height=15, width=60)
result_text.pack(padx=10, pady=10)

root.mainloop()
