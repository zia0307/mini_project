import ctypes

# Load your DLL
calcdll = ctypes.CDLL('c:\\Users\\L K Subair\\Documents\\C_PROGRAMS\\miniproj\\caloriecalc.dll')

# Declare the function prototype
# assuming your function signature was something like:
# float calculateCalories(float weight, float height, int age, char sex, char goal[20], char *dietType)
calcdll.calculateCalories.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_int, ctypes.c_char, ctypes.c_char_p, ctypes.c_char_p]
calcdll.calculateCalories.restype = ctypes.c_float

# Prepare your variables
weight = 70.0
height = 1.75
age = 24
sex = b'M'  # bytes
goal = b'bulk'
dietType = ctypes.create_string_buffer(50)

# Call the function
calories = calcdll.calculateCalories(weight, height, age, sex, goal, dietType)

# Print result
print("Calories:", calories)
print("Diet Type:", dietType.value.decode())
