一、安装与编译
要求：
g++ ≥ 4.8（支持 C++11）
Linux / macOS / WSL（Windows 子系统）

# 克隆或下载源码
git clone https://github.com/yourname/rpn_calc.git
cd rpn_calc

# 编译
g++ -std=c++11 -o rpn_calc rpn_calc.cpp

# 可选：安装到系统路径
sudo mv rpn_calc /usr/local/bin/

二、运行方式
交互模式
./rpn_calc
提示符 rpn> 下直接输入表达式，以回车求值；输入 quit 或 Ctrl-D 退出。
一次式计算（适合脚本）
./rpn_calc "5 5 +"
# 输出：结果: 10
管道 / Here-String
echo "1 2 + 3 + 7 7 * +" | ./rpn_calc
# 输出：结果: 55

三、支持的操作符
类别	符号	含义	示例	备注
基础	+ - * /	加减乘除	4 2 / → 2	整数或浮点
高级	sqrt	平方根	16 sqrt → 4	负数会报错
^	幂运算	2 3 ^ → 8	右操作数为指数
fib	斐波那契	10 fib → 55	第 n 项（0-based）
栈操作	clear	清空栈	clear	
show	显示当前栈	show	顶在右
history	打印历史输入	history	带序号
辅助	help	打印本表	help	
neg	取反	-3 neg → 3	一元操作

四、错误与异常
提示	含义	解决建议
栈空	操作数不足	补充数值
除零错误	除数为零	检查输入
负数开方	sqrt 参数 < 0	先 neg 或取绝对值
数值溢出	结果超出 double 可表示范围	缩小数值
未知操作符	未定义符号	对照上表
表达式不完整	计算结束后栈内仍有多于一个元素	检查是否漏写操作符
五、快速上手示例
# 复利近似计算：本金 1000，年利率 5%，10 年
echo "1000 1 0.05 10 ^ *" | ./rpn_calc
# 结果: 1628.89

# 勾股定理：3² + 4² 再开方
echo "3 2 ^ 4 2 ^ + sqrt" | ./rpn_calc
# 结果: 5

# 斐波那契数列前 12 项（脚本循环）
for i in {0..11}; do echo "$i fib" | ./rpn_calc; done
