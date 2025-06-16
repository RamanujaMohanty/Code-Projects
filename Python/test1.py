def user_length(username):
        if (len(username) < 5):
                print(f"{username} is too short")
        else:
                print(f"Welcome, {username}")

username1 = input("Enter username: ")
user_length(username1)

x = 0
while x < 5:
        print(f"{x}. {username1}")
        x = x + 1
print(f"{x}. Finally, I'm done")
print("--------------------------------------------------------")
def greet_person(name):
        print(f"Hello, {name}!")

name_one = "Ronald"
greet_person(name_one)
print("--------------------------------------------------------")
for n in range(19):
        if n % 2 == 0:
                print(n)
print("--------------------------------")
for a in range(18+1):
        print(a ** 2)
print("--------------------------------")
for b in range(0,18+1,2):
        print(b*2)
print("--------------------------------")
for d in range(10):
        print(d+d)
print("--------------------------------------------------------")
x = int(input("Enter x: "))
print(x)
