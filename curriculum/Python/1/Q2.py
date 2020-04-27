
Score = int(input("请输入您的成绩："))
if Score in range(90,101):
    print("您的成绩等级为：A")
elif Score in range (80,90):
    print("您的成绩等级为：B")
elif Score in range (70,80):
    print("您的成绩等级为：C")
elif Score in range (0,70):
    print("您的成绩等级为：D")
else:
    print("请输入有效成绩！")