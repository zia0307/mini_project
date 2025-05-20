import ctypes
from ctypes import *
import tkinter as tk
from tkinter import messagebox

dietdll = ctypes.CDLL(r'miniproj\dietplanner.dll')

dietdll.loadSampleRecipes.restype = None
dietdll.calculateCalories.argtypes = [c_float, c_float, c_int, c_char, c_char_p, POINTER(c_char)]
dietdll.calculateCalories.restype = c_float

dietdll.suggestRecipes.argtypes = [
    c_char_p,
    c_char * 50 * 50,  # ingredients
    c_int,
    c_char * 50 * 50,  # allergies
    c_int,
    c_char * 20 * 20,  # restrictions
    c_int,
    c_char * 5000      # result buffer
]
dietdll.suggestRecipes.restype = None

dietdll.suggestRecipes.argtypes = [
    c_char_p,
    (c_char * 50) * 20, c_int,
    (c_char * 50) * 5, c_int,
    (c_char * 20) * 5, c_int,
    c_char * 5000
]
dietdll.suggestRecipes.restype = None

dietdll.loadSampleRecipes()

dietTypeBuffer = create_string_buffer(50)
calories = dietdll.calculateCalories(
    70.0, 1.75, 25, b'M', b'bulk', dietTypeBuffer
)
print(f"Calories: {calories}, Diet Type: {dietTypeBuffer.value.decode()}")

'''ingredients = (c_char * 50 * 50)()
allergies = (c_char * 50 * 50)()
restrictions = (c_char * 20 * 20)()

#fill ingredient array
ingredient_list = [b"chicken", b"lettuce"]
for i, ing in enumerate(ingredient_list):
    ingredients[i].value = ing

ingredient_count = len(ingredient_list)

# Similarly fill allergies and restrictions if any
allergy_list = []
restriction_list = [b"halal"]

for i, al in enumerate(allergy_list):
    allergies[i].value = al

for i, res in enumerate(restriction_list):
    restrictions[i].value = res

allergy_count = len(allergy_list)
restriction_count = len(restriction_list)'''


def runPlanner():
    try:
        w = float(weight_entry.get())
        h = float(height_entry.get())
        a = int(age_entry.get())
        s = sex_var.get().encode()
        g = goal_var.get().encode()

        outDietType = create_string_buffer(50)
        calories = dietdll.calculateCalories(w, h, a, s[0], g, outDietType)

        result = f"Calories: {calories:.2f} kcal\nDiet Type: {outDietType.value.decode()}\n\nRecipes:\n"

        ingList = [e.strip() for e in ingredients_entry.get().split(",") if e.strip()]
        allergList = [e.strip() for e in allergies_entry.get().split(",") if e.strip()]
        restrictions = []
        if halal_var.get(): restrictions.append("Halal")
        if vegetarian_var.get(): restrictions.append("Vegetarian")
        if vegan_var.get(): restrictions.append("Vegan")
        if jain_var.get(): restrictions.append("Jain")

        ingArr = ((c_char * 50) * 20)()
        for i, item in enumerate(ingList):
            ingArr[i].value = item.encode()

        allgArr = ((c_char * 50) * 5)()
        for i, item in enumerate(allergList):
            allgArr[i].value = item.encode()

        restrArr = ((c_char * 20) * 5)()
        for i, item in enumerate(restrictions):
            restrArr[i].value = item.encode()

        resultBuffer = (c_char * 5000)()
        dietdll.suggestRecipes(outDietType, ingArr, len(ingList), allgArr, len(allergList), restrArr, len(restrictions), resultBuffer)

        result += resultBuffer.value.decode() or "No matching recipes."


        result_text.delete(1.0, tk.END)
        result_text.insert(tk.END, result)

    except Exception as e:
        messagebox.showerror("Error", str(e))

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

'''resultBuffer = create_string_buffer(5000)

dietlib.suggestRecipes(
    dietTypeBuffer.value,
    ingredients,
    ingredient_count,
    allergies,
    allergy_count,
    restrictions,
    restriction_count,
    resultBuffer
)

print("Suggestions:\n", resultBuffer.value.decode())'''
