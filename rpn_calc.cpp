#include <iostream>   // 标准输入输出
#include <sstream>    // 字符串流，分割用户输入
#include <stack>      // STL 栈
#include <vector>     // 临时展示栈内容
#include <string>     // 字符串处理
#include <cmath>      // 数学函数
#include <cctype>     // 后续扩展字符判断预

//声明一个类，封装所有计算逻辑
class RPNCalculator {
// st是存放数字的栈
 std::stack<double> st;
public:
 // 将数字压栈
  void push(double value) { st.push(value); }
  /*弹出一个数字并返回，如果栈空则抛出异常*/ 
    double pop() {
        if (st.empty()) throw std::runtime_error("栈空");
        double v = st.top();
        st.pop();
        return v;
    }
    
    // 公有清空接口，供异常后调用
    void clear() { while (!st.empty()) st.pop(); }
     // 根据操作符进行计算或栈操作 
    // 增强版 calculate，支持单目、双目、除零/溢出检测
    void calculate(const std::string& op) {
        // ---------- 栈管理 ----------
         //clear--循环pop直到栈空
          /*show--把当前栈元素倒出来打印再压回去，不改顺序*/
        if (op == "clear") { clear(); return; }
        if (op == "show")  { show();  return; }
        // ---------- 单目运算 ----------
        if (op == "sqrt" || op == "sin" || op == "cos" || op == "neg") {
            double a = pop();
            if (op == "sqrt") {
                if (a < 0) throw std::runtime_error("负数不能开方");
                push(std::sqrt(a));
            } else if (op == "sin") push(std::sin(a));
            else if (op == "cos") push(std::cos(a));
            else if (op == "neg") push(-a);
            return;
        }
    
        // ---------- 双目运算 ----------
        double b = pop();   // 右操作数
        double a = pop();   // 左操作数
         /*开始四则运算和除零操作如果有未知操作符抛异常*/
        if (op == "+")      push(a + b);
        else if (op == "-") push(a - b);
        else if (op == "*") push(a * b);
        else if (op == "/") {
            if (b == 0) throw std::runtime_error("除零错误");
            double r = a / b;
            if (std::isinf(r)) throw std::runtime_error("数值溢出");
            push(r);
        }
        else if (op == "pow") push(std::pow(a, b));
        else throw std::runtime_error("未知操作符");
    }
    
      /* 返回最终唯一结果，栈必须只剩一个元素,如果栈空或者还剩多个数抛异常 */
    double result() const {
        if (st.empty()) throw std::runtime_error("无结果");
        if (st.size() != 1) throw std::runtime_error("表达式不完整");
        return st.top();
    }

private:
    //  打印栈快照，不改原栈
    void show() const {
        if (st.empty()) { std::cout << "栈: <空>\n"; return; }
        std::vector<double> tmp;
        std::stack<double> cp = st;          // 拷贝一份
        while (!cp.empty()) { tmp.push_back(cp.top()); cp.pop(); }
        std::cout << "栈: ";
        for (auto it = tmp.rbegin(); it != tmp.rend(); ++it)
            std::cout << *it << ' ';
        std::cout << '\n';
    }
};

// 万能数字识别，负数、小数、科学计数法都能过
bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    std::size_t idx = 0;
    try {
        std::stod(s, &idx);
        return idx == s.size();
    } catch (...) { return false; }
}

/* 主循环：读一行 → 分词 → 执行 → 输出结果 */
int main() {
    RPNCalculator calc;
    std::cout << "C++ RPN 计算器\n"
                 "支持 + - * / sqrt sin cos neg pow clear show\n"
                 "输入 'q' 退出\n";

    std::string line;
    while (std::cout << "> " && std::getline(std::cin, line)) {
        if (line == "q") break;          // 用户主动退出
        //按空格分隔单词 
        std::istringstream iss(line);
        std::string token;
        try {
            while (iss >> token) {
                if (isNumber(token))     // 用健壮识别代替 isdigit
                    calc.push(std::stod(token));
                else  // 操作符 → 计算
                    calc.calculate(token);
            }
            //如果正常结束就打印栈顶唯一结果
            //如果任意一步出错就报错
            std::cout << "结果: " << calc.result() << '\n';
        } catch (const std::exception& e) {
            std::cout << "错误: " << e.what() << '\n';
            calc.clear();                // 异常后清栈，防止垃圾数据
        }
    }
    return 0;
}
