def strip(string,side="both",blanks=["\t","\n"," "]):
    l=0
    r=0
    for c in string[::-1]:
        if c in blanks:
            r+=1
        else:
            break
    r=len(string)-r
    for c in string:
        if c in blanks:
            l+=1
        else:
            break
    if side=="left":
        r=len(string)
    if side=="right":
        l=0
    return string[l:r]

print(strip(" abc ")) # 返回值为"abc"
print(strip(" abc ", "both")) # 返回值为"abc"
print(strip(" abc ", "left")) # 返回值为"abc "
print(strip(" abc ", side="right")) # 返回值为" abc"
print(strip("aaadefccc ", blanks=["a", "c"," "])) # 返回值为"def"