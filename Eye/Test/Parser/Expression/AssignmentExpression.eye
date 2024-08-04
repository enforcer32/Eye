number = 20;
num2 = number;
num2 += 10;
number -= 30;
number /= 40;
number = num2 * 50;
num2 = number %= 55;
//BUG-> num2 = number % 55;
