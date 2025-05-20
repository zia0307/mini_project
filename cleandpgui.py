import ctypes
from ctypes import *
import tkinter as tk
from tkinter import messagebox

# Load the DLL
dietdll = ctypes.CDLL(r'C:\Users\L K Subair\Documents\C_PROGRAMS\miniproj\dietplanner.dll')

# Set argument and return types
dietdll.loadSampleRecipes.restype = None
dietdll.calculateCalories.argtypes = [c_float, c_float, c_int, c_char, c_char_p, POINTER(c_char)]
dietdll.calculateCalories.restype = c_float

dietdll.suggestRecipes.argtypes = [
    c_char_p,
    (c_char * 50) * 20, c_int,          # ingredients
    (c_char * 50) * 5, c_int,           # allergies
    (c_char * 20) * 5, c_int,           # restrictions
    c_char * 5000                       # result buffer
]
dietdll.suggestRecipes.restype = None

# Load sample data
dietdll.loadSampleRecipes()

#Recipe data extracted
unique_ingredients = [
    "oats", "milk", "banana", "chicken", "lettuce", "olive oil", "lemon",
    "protein powder", "veggie patty", "bun", "tomato", "bell peppers", "onion",
    "fajita seasoning", "paneer", "yogurt", "spices", "mangoes", "honey","cucumber","salad dressing"
]

unique_tags = ["vegetarian", "halal", "vegan","jain"]

# GUI function for calculation and recipe suggestion
def runPlanner():
    try:
        # Input retrieval
        w = float(weight_entry.get())
        h = float(height_entry.get())
        a = int(age_entry.get())
        s = sex_var.get().encode()
        g = goal_var.get().encode()

        # Get calorie and diet type
        outDietType = create_string_buffer(50)
        calories = dietdll.calculateCalories(w, h, a, s[0], g, outDietType)

        result = f"Calories: {calories:.2f} kcal\nDiet Type: {outDietType.value.decode()}\n\nRecipes:\n"

        # Parse ingredients, allergies, and restrictions
        ingList = [e.strip().lower() for e in ingredients_entry.get().split(",") if e.strip()]
        allergList = [e.strip().lower() for e in allergies_entry.get().split(",") if e.strip()]
        restrictions = []
        if halal_var.get(): restrictions.append("halal")
        if vegetarian_var.get(): restrictions.append("vegetarian")
        if vegan_var.get(): restrictions.append("vegan")
        if jain_var.get(): restrictions.append("jain")


        # Fill C-style arrays
        ingArr = ((c_char * 50) * 20)()
        for i, item in enumerate(ingList):
            ingArr[i].value = item.encode()

        allgArr = ((c_char * 50) * 5)()
        for i, item in enumerate(allergList):
            allgArr[i].value = item.encode()

        restrArr = ((c_char * 20) * 5)()
        for i, item in enumerate(restrictions):
            restrArr[i].value = item.encode()

        # Call DLL function to get recipe suggestions
        resultBuffer = (c_char * 5000)()
        dietdll.suggestRecipes(
            outDietType, 
            ingArr, len(ingList), 
            allgArr, len(allergList), 
            restrArr, len(restrictions), 
            resultBuffer
        )

        result += resultBuffer.value.decode() or "No matching recipes."

        result_text.delete(1.0, tk.END)
        result_text.insert(tk.END, result)

    except Exception as e:
        messagebox.showerror("Error", str(e))

# GUI layout
root = tk.Tk()
root.title("Diet Planner")

tk.Label(root, text="Weight (kg):").pack()
weight_entry = tk.Entry(root)
weight_entry.pack()

tk.Label(root, text="Height (m):").pack()
height_entry = tk.Entry(root)
height_entry.pack()

tk.Label(root, text="Age:").pack()
age_entry = tk.Entry(root)
age_entry.pack()

sex_var = tk.StringVar(value="M")
tk.Label(root, text="Sex:").pack()
tk.OptionMenu(root, sex_var, "M", "F").pack()

goal_var = tk.StringVar(value="bulk")
tk.Label(root, text="Goal:").pack()
tk.OptionMenu(root, goal_var, "bulk", "cut", "maintain").pack()

tk.Label(root, text="Ingredients (comma separated):").pack()
ingredients_entry = tk.Entry(root)
ingredients_entry.pack()

tk.Label(root, text="Allergies (comma separated):").pack()
allergies_entry = tk.Entry(root)
allergies_entry.pack()

halal_var = tk.IntVar()
vegetarian_var = tk.IntVar()
vegan_var = tk.IntVar()
jain_var = tk.IntVar()

tk.Checkbutton(root, text="Halal", variable=halal_var).pack()
tk.Checkbutton(root, text="Vegetarian", variable=vegetarian_var).pack()
tk.Checkbutton(root, text="Vegan", variable=vegan_var).pack()
tk.Checkbutton(root, text="Jain", variable=jain_var).pack()

tk.Button(root, text="Calculate & Suggest Recipes", command=runPlanner).pack(pady=10)

result_text = tk.Text(root, height=15, width=50)
result_text.pack(padx=10, pady=10)

root.mainloop()
