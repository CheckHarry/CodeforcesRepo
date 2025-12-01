



def digit(s):
    ans = 0
    while s:
        ans += (s % 10)
        s = (s - s % 10) / 10
    return ans



print(999999999 * 999999999 , digit(999999999 * 999999999))

print(18 * 9)